package utils;

import SystemLogic.ValidMatchedOffers;
import TranspoolMaps.SingleTransPoolMap;
import constants.Constants;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

public class SessionUtils {

    public static String getUsername (HttpServletRequest request) {
        HttpSession session = request.getSession(false);
        Object sessionAttribute = session != null ? session.getAttribute(Constants.USERNAME) : null;
        return sessionAttribute != null ? sessionAttribute.toString() : null;
    }

    public static String getUserType (HttpServletRequest request) {
        HttpSession session = request.getSession(false);
        Object sessionAttribute = session != null ? session.getAttribute(Constants.USER_TYPE) : null;
        return sessionAttribute != null ? sessionAttribute.toString() : null;
    }

    public static String getMapUploadError(HttpServletRequest request) {
        HttpSession session = request.getSession(false);
        Object sessionAttribute = session != null ? session.getAttribute(Constants.USERS_MAP_UPLOAD_ERROR) : null;
        return sessionAttribute != null ? sessionAttribute.toString() : null;
    }

    public static String getFormUploadError(HttpServletRequest request) {
        HttpSession session = request.getSession(false);
        Object sessionAttribute = session != null ? session.getAttribute(Constants.FORM_UPLOAD_ERROR) : null;
        return sessionAttribute != null ? sessionAttribute.toString() : null;
    }

    public static SingleTransPoolMap getMapData (HttpServletRequest request) {
        HttpSession session = request.getSession(false);
        Object sessionAttribute = session != null ? session.getAttribute(Constants.MAPDATA) : null;
        return sessionAttribute != null ? (SingleTransPoolMap)sessionAttribute : null;
    }

    public static ValidMatchedOffers getMatchOffersData (HttpServletRequest request) {
        HttpSession session = request.getSession(false);
        Object sessionAttribute = session != null ? session.getAttribute(Constants.MATCH_OFFERS) : null;
        return sessionAttribute != null ? (ValidMatchedOffers) sessionAttribute : null;
    }
    public static Integer getRequestForMatch (HttpServletRequest request) {
        HttpSession session = request.getSession(false);
        Object sessionAttribute = session != null ? session.getAttribute(Constants.REQUEST_MATCH) : null;
        return sessionAttribute != null ? (Integer)sessionAttribute : null;
    }

    public static void clearSession (HttpServletRequest request) {
        request.getSession().invalidate();
    }
}