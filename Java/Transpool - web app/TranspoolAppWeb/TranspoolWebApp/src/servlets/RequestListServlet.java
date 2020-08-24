package servlets;


import CustomClasses.TripRequest;
import TranspoolMaps.SingleTransPoolMap;
import TranspoolMaps.TransPoolMapManager;
import com.google.gson.Gson;
import utils.ServletUtils;
import utils.SessionUtils;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;
import java.util.stream.Collectors;

public class RequestListServlet extends HttpServlet {

    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        //returning JSON objects, not HTML
        response.setContentType("application/json");
        try (PrintWriter out = response.getWriter()) {
            Gson gson = new Gson();
            TransPoolMapManager transPoolMapManager = ServletUtils.getTransPoolMapManager(getServletContext());
            SingleTransPoolMap singlemap = SessionUtils.getMapData(request);
            String Mapname = singlemap.getMapName();
            SingleTransPoolMap TranspoolMap = transPoolMapManager.FindMap(Mapname);
            String UserName = SessionUtils.getUsername(request);
            List<TripRequest> tripRequests = TranspoolMap.getModelLogic().getTripRequests().getTripRequests();
            if(SessionUtils.getUserType(request).equals("Passenger"))
            {
                tripRequests = tripRequests.stream().filter(tripRequest -> tripRequest.getFirstName()
                        .equals(UserName))
                        .collect(Collectors.toList());
            }
            String json = gson.toJson(tripRequests);
            out.println(json);
            out.flush();
        }
    }

    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>
}
