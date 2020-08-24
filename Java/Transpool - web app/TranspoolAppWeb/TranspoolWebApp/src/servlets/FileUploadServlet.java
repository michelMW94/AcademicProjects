package servlets;

//taken from: http://www.servletworld.com/servlet-tutorials/servlet3/multipartconfig-file-upload-example.html
// and http://docs.oracle.com/javaee/6/tutorial/doc/glraq.html
import SystemEngine.TransPool;
import SystemLogic.ModelLogic;
import TranspoolMaps.SingleTransPoolMap;
import TranspoolMaps.TransPoolMapManager;

import com.google.gson.Gson;
import constants.Constants;
import utils.ServletUtils;
import utils.SessionUtils;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Paths;
import java.util.Collection;

import java.util.List;
import java.util.Scanner;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;


@MultipartConfig(fileSizeThreshold = 1024 * 1024, maxFileSize = 1024 * 1024 * 5, maxRequestSize = 1024 * 1024 * 5 * 5)
public class FileUploadServlet extends HttpServlet {


    private void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws Exception {

        response.setContentType("application/json");

        ModelLogic modelLogic = ServletUtils.getModelLogic(getServletContext());
        TransPoolMapManager transPoolMapManager = ServletUtils.getTransPoolMapManager(getServletContext());

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        Collection<Part> parts = request.getParts();
        StringBuilder fileContent = new StringBuilder();
        String fileName = "";
        String transPoolMapName = "";
        int countForFileName = 0;
        for (Part part : parts) {

             if(countForFileName == 0)
                transPoolMapName = extractMapName(part);
            else if(countForFileName == 1)
            {
                fileName = extractFileName(part);
                fileContent.append(readFromInputStream(part.getInputStream()));
            }
            countForFileName++;
        }

        InputStream stream = new ByteArrayInputStream( fileContent.toString().getBytes(StandardCharsets.UTF_8));
        TransPool transPool = modelLogic.fromXmlFileToObject(stream);

        if(fileCheck())
        {
            modelLogic.setTransPool(transPool);
            String username = SessionUtils.getUsername(request);
            int numStations = transPool.getMapDescriptor().getStops().getStop().size();
            int numRoutes = transPool.getMapDescriptor().getPaths().getPath().size();

            synchronized (getServletContext()) {
                if(transPoolMapManager.isFileMapExists(fileName) == false && transPoolMapManager.isMapNameExists(transPoolMapName) == false)
                {
                    if(transPoolMapManager.isTransPoolUsersMapExists(username))
                    {
                        transPoolMapManager.updateUserMap(username,  transPoolMapName, numStations, numRoutes, 0, 0, fileName, modelLogic);
                        request.getSession(true).setAttribute(Constants.USERS_MAP_UPLOAD_ERROR, "new upload succeeded");

                    }
                    else
                    {
                        transPoolMapManager.addTransPoolMap(username,  transPoolMapName, numStations, numRoutes, 0, 0, fileName, modelLogic);
                        request.getSession(true).setAttribute(Constants.USERS_MAP_UPLOAD_ERROR, "upload succeeded");
                    }
                }
                else if(transPoolMapManager.isFileMapExists(fileName) == true)
                {
                    request.getSession(true).setAttribute(Constants.USERS_MAP_UPLOAD_ERROR, fileName + " was already upload");
                }
                else
                {
                    request.getSession(true).setAttribute(Constants.USERS_MAP_UPLOAD_ERROR, "The map name of " + transPoolMapName + " was already selected");
                }
            }
        }
        else
        {
            request.getSession(true).setAttribute(Constants.USERS_MAP_UPLOAD_ERROR, modelLogic.getJaxbErrorsInString());
        }

    }


    private String extractFileName(Part part) {
        String contentDisp = part.getHeader("content-disposition");
        String[] items = contentDisp.split(";");
        for (String s : items) {
            if (s.trim().startsWith("filename")) {
                return s.substring(s.indexOf("=") + 2, s.length()-1);
            }
        }
        return "";
    }
    private String extractMapName(Part part) {
        String contentDisp = part.getHeader("content-disposition");
        String[] items = contentDisp.split(";");
        for (String s : items) {
            if (s.trim().startsWith("name")) {
                return s.substring(s.indexOf("=") + 2, s.length()-1);
            }
        }
        return "";
    }
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            processRequest(request,response);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }


    private boolean fileCheck()
    {
        if(ServletUtils.getModelLogic(getServletContext()).getErrorList().size() == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    private String readFromInputStream(InputStream inputStream) {
        return new Scanner(inputStream).useDelimiter("\\Z").next();
    }


}