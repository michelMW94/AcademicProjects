package servlets;

import CustomClasses.TripRequest;
import SystemLogic.ModelLogic;
import SystemLogic.ValidMatchedOffers;
import TranspoolMaps.SingleTransPoolMap;
import com.google.gson.Gson;
import constants.Constants;
import utils.SessionUtils;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

public class FindMatchOffersServlet extends HttpServlet {
    protected void processRequest(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

        response.setContentType("application/json");

        try (PrintWriter out = response.getWriter()) {

            Gson gson = new Gson();
            SingleTransPoolMap singleMap = SessionUtils.getMapData(request);
            String index  = request.getParameter("requestNumber");
            request.getSession(true).setAttribute(Constants.REQUEST_MATCH, Integer.parseInt(index));
            ModelLogic modelLogic = singleMap.getModelLogic();
            TripRequest tripRequest = modelLogic.getTripRequests().getTripRequests().get(Integer.parseInt(index));
            ValidMatchedOffers validMatchedOffers = modelLogic.FindRideMatches(modelLogic.transPool.getPlannedTrips().getTransPoolTrip().size(),tripRequest);
            request.getSession(true).setAttribute(Constants.MATCH_OFFERS, validMatchedOffers);
            String json = gson.toJson(validMatchedOffers.getValidOffers());
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
