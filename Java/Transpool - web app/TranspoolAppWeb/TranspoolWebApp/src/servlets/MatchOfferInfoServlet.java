package servlets;

import SystemLogic.ModelLogic;
import SystemLogic.SingleValidMatchedOffers;
import SystemLogic.ValidMatchedOffers;
import TranspoolMaps.SingleTransPoolMap;
import com.google.gson.Gson;
import utils.SessionUtils;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

public class MatchOfferInfoServlet extends HttpServlet {

    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        //returning JSON objects, not HTML
        response.setContentType("application/json");
        try (PrintWriter out = response.getWriter()) {
            Gson gson = new Gson();
            String index  = request.getParameter("matchOfferNumber");
            ValidMatchedOffers validMatchedOffers = SessionUtils.getMatchOffersData(request);
            SingleTransPoolMap singleMap = SessionUtils.getMapData(request);
            ModelLogic modelLogic = singleMap.getModelLogic();
            SingleValidMatchedOffers singleValidMatchedOffers = validMatchedOffers.FindSingleOfferById(Integer.parseInt(index));
            if(singleValidMatchedOffers != null)
            {

                String infoText = modelLogic.CreateOfferInformationAlertMsg(singleValidMatchedOffers);
                String json = gson.toJson(infoText);
                out.println(json);
                out.flush();
            }
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
