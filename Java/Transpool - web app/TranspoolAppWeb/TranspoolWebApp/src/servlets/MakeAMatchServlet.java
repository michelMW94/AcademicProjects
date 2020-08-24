package servlets;

import CustomClasses.TripRequest;
import CustomClasses.TripRequests;
import SystemLogic.ModelLogic;
import SystemLogic.SingleValidMatchedOffers;
import SystemLogic.ValidMatchedOffers;
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

public class MakeAMatchServlet extends HttpServlet {

    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        //returning JSON objects, not HTML
        response.setContentType("application/json");
        try (PrintWriter out = response.getWriter()) {
            Gson gson = new Gson();
            String index  = request.getParameter("matchOfferNumber");
            ValidMatchedOffers validMatchedOffers = SessionUtils.getMatchOffersData(request);
            String UserName = SessionUtils.getUsername(request);
            TransPoolMapManager mapManager = ServletUtils.getTransPoolMapManager(getServletContext());
            SingleTransPoolMap singlemap = SessionUtils.getMapData(request);
            assert singlemap != null;
            String mapName = singlemap.getMapName();
            SingleTransPoolMap singleTransPoolMap = mapManager.FindMap(mapName);
            ModelLogic modelLogic = singleTransPoolMap.getModelLogic();
            TripRequests tripRequests = modelLogic.getTripRequests();
            TripRequest tripRequest = tripRequests.FindRequestByName(UserName);
            assert validMatchedOffers != null;
            SingleValidMatchedOffers singleValidMatchedOffers = validMatchedOffers.FindSingleOfferById(Integer.parseInt(index));
            if(singleValidMatchedOffers != null)
            {
                tripRequest.setMatchTrip(singleValidMatchedOffers);
                singleTransPoolMap.setNumMatchedRequest(singleTransPoolMap.getNumMatchedRequest() + 1);
                //modelLogic.updateCapacityAfterMatch(singleValidMatchedOffers,tripRequest);

            }
            String json  = gson.toJson(tripRequest);
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