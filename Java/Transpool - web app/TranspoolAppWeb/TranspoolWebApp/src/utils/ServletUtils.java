package utils;

import SystemLogic.ModelLogic;
import TranspoolMaps.TransPoolMapManager;
import chat.ChatManager;
import users.UserManager;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;

import static constants.Constants.INT_PARAMETER_ERROR;

public class ServletUtils {

    private static final String USER_MANAGER_ATTRIBUTE_NAME = "userManager";
    private static final String MODEL_LOGIC_ATTRIBUTE_NAME = "ModelLogic";
    private static final String TRANS_POOL_MAP_MANAGER_ATTRIBUTE_NAME = "transPoolMap";
    private static final String CHAT_MANAGER_ATTRIBUTE_NAME = "chatManager";

    /*
    Note how the synchronization is done only on the question and\or creation of the relevant managers and once they exists -
    the actual fetch of them is remained un-synchronized for performance POV
     */
    private static final Object userManagerLock = new Object();
    private static final Object chatManagerLock = new Object();
    private static final Object transPoolMapLock = new Object();

    public static TransPoolMapManager getTransPoolMapManager(ServletContext servletContext)
    {
        synchronized (transPoolMapLock) {
            if (servletContext.getAttribute(TRANS_POOL_MAP_MANAGER_ATTRIBUTE_NAME) == null) {
                servletContext.setAttribute(TRANS_POOL_MAP_MANAGER_ATTRIBUTE_NAME, new TransPoolMapManager());
            }
        }
        return (TransPoolMapManager) servletContext.getAttribute(TRANS_POOL_MAP_MANAGER_ATTRIBUTE_NAME);
    }
    public static UserManager getUserManager(ServletContext servletContext) {

        synchronized (userManagerLock) {
            if (servletContext.getAttribute(USER_MANAGER_ATTRIBUTE_NAME) == null) {
                servletContext.setAttribute(USER_MANAGER_ATTRIBUTE_NAME, new UserManager());
            }
        }
        return (UserManager) servletContext.getAttribute(USER_MANAGER_ATTRIBUTE_NAME);
    }

    public static ChatManager getChatManager(ServletContext servletContext) {
        synchronized (chatManagerLock) {
            if (servletContext.getAttribute(CHAT_MANAGER_ATTRIBUTE_NAME) == null) {
                servletContext.setAttribute(CHAT_MANAGER_ATTRIBUTE_NAME, new ChatManager());
            }
        }
        return (ChatManager) servletContext.getAttribute(CHAT_MANAGER_ATTRIBUTE_NAME);
    }

    public static ModelLogic getModelLogic(ServletContext servletContext) {

        synchronized (userManagerLock) {
            if (servletContext.getAttribute(MODEL_LOGIC_ATTRIBUTE_NAME) == null) {
                servletContext.setAttribute(MODEL_LOGIC_ATTRIBUTE_NAME, new ModelLogic());
            }
        }
        return (ModelLogic) servletContext.getAttribute(MODEL_LOGIC_ATTRIBUTE_NAME);
    }

    public static int getIntParameter(HttpServletRequest request, String name) {
        String value = request.getParameter(name);
        if (value != null) {
            try {
                return Integer.parseInt(value);
            } catch (NumberFormatException numberFormatException) {
            }
        }
        return INT_PARAMETER_ERROR;
    }
}
