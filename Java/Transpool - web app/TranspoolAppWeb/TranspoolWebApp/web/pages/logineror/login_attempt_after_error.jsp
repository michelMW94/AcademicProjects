<%--
    Document   : index
    Created on : Jan 24, 2012, 6:01:31 AM
    Author     : blecherl
    This is the login JSP for the online chat application
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <%@page import="utils.*" %>
    <%@ page import="constants.Constants" %>
    <head>
        <link rel="stylesheet" href="LoginStlye.css">
        <link href="https://fonts.googleapis.com/css?family=Ubuntu" rel="stylesheet">
        <meta name="viewport" content="width=device-width, initial-scale=1" />
        <link rel="stylesheet" href="path/to/font-awesome/css/font-awesome.min.css">
        <title>Sign in</title>
    </head>
    <body>
    <div class="main">
            <% String usernameFromSession = SessionUtils.getUsername(request);%>
            <% String usernameFromParameter = request.getParameter(Constants.USERNAME) != null ? request.getParameter(Constants.USERNAME) : "";%>
            <% if (usernameFromSession == null) {%>
        <p class="sign" align="center">Sign in</p>
        <form class="form1" method="GET" action="login">
            <input class="un" type="text" name="username" align="center" placeholder="Username" >
            <br/>
            <input class = "radiobtn" type="radio" name="userType"  value="Driver"/> Driver<br><br>
            <input class = "radiobtn" type="radio" name="userType"  value="Passenger"/> Passenger<br><br><br>
            <% Object errorMessage = request.getAttribute(Constants.USER_NAME_ERROR);%>
            <% if (errorMessage != null) {%>
            <span class="bg-danger"  style="color:red"><%=errorMessage%></span>
            <% } %>
            <br/>
            <input class="submit" type="submit"  align="center"  value="Sign in" />
        </form>


            <% }%>
        </div>
    </body>
</html>