package servlets;

import SystemLogic.ModelLogic;
import TranspoolMaps.SingleTransPoolMap;
import TranspoolMaps.TransPoolMapManager;
import constants.Constants;
import utils.ServletUtils;
import utils.SessionUtils;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;


public class SuggestionUpdateServlet extends HttpServlet {

    protected void processRequest(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

        response.setContentType("application/json");

        try (PrintWriter out = response.getWriter()) {


            Integer Capacity = Integer.parseInt(request.getParameter("Capacity"));
            Integer PPK = Integer.parseInt(request.getParameter("PPK"));
            String Route = request.getParameter("Route");
            String Recurrences = request.getParameter("recurrences");
            Integer Day = Integer.parseInt(request.getParameter("Day"));
            Integer Hour = Integer.parseInt(request.getParameter("Hour"));
            Integer Minutes = Integer.parseInt(request.getParameter("Minutes"));
            String UserName = SessionUtils.getUsername(request);

            TransPoolMapManager mapManager = ServletUtils.getTransPoolMapManager(getServletContext());
            SingleTransPoolMap singlemap = SessionUtils.getMapData(request);
            String Mapname = singlemap.getMapName();
            SingleTransPoolMap TranspoolMap = mapManager.FindMap(Mapname);

            ModelLogic modelLogic = TranspoolMap.getModelLogic();
            String errorList = modelLogic.NewOfferInputCheck(Route,Day,Hour,Minutes,PPK,Capacity);
            if(errorList.isEmpty())
            {
                modelLogic.CreateNewTranspoolTrip(UserName, Route, Day, Hour, Minutes, PPK, Capacity, "Daily");
                TranspoolMap.setNumOffers(TranspoolMap.getNumOffers() + 1);
                request.getSession(true).setAttribute(Constants.FORM_UPLOAD_ERROR, "upload succeeded");
            }
            else {
                request.getSession(true).setAttribute(Constants.FORM_UPLOAD_ERROR, errorList);
            }



            response.sendRedirect("MapShow.html");

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






