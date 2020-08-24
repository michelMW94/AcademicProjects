var refreshRate = 1000; //milli seconds
var MAP_LIST_URL = buildUrlWithContextPath("mapList");
var USER_NAME_URL = buildUrlWithContextPath("userNameServlet");


function createSingleMapEntry (Map,idx){
    var username = Map.userName;
    var mapname = Map.mapName;
    var numstation = Map.numStation;
    var numroutes = Map.numRoutes;
    var numoffers = Map.numOffers;
    var numrequests = Map.numRequests;
    var numMatchedRequest = Map. numMatchedRequest;
    var requestsFormat = numMatchedRequest + "/" + numrequests;

    var markup = "<tr><td>" + username + "</td><td>" + mapname
        + "</td><td>" + numstation + "</td><td>" +
        numroutes + "</td><td>" + numoffers + "</td><td>"
        + requestsFormat + "</td><td>" +
        "<form method= 'GET'" +  " action= 'MapShow'>" +
        "<input type='hidden'" + "name='mapnum'" + " value=" + idx + ">" +
        "<input type='submit' value='Show'  /></form></td>" +"<tr>";



    return markup;
}

function ajaxErrorContent() {
    $.ajax({
        data: " ",
        url: "ErrorList",
        timeout: 2000,
        success: function (res) {
            console.log("getting upload list");
            if(res.toString() === "upload succeeded")
            {
                $('#uploadResultContent').css("color", "green");
            }
            else if(res.toString() === "new upload succeeded")
            {
                $('#uploadResultContent').css("color", "orange");
                var tBody = document.getElementById("queryTable").getElementsByTagName("TBODY");;

            }
            else
            {
                $('#uploadResultContent').css("color", "red");
            }
            $('#uploadResultContent').text(res);
            triggerAjaxErrorContent();
        },
        error: function(error) {
            console.error("Failed to submit");
            triggerAjaxErrorContent();
        }
    });
}

$(function() { // onload...do
    $("#UploadMap").submit(function() {

        var mName = $("#tMapName").val();
        if(mName != "")
        {

        }
        var file1 = this[0].files[0];
        var formData = new FormData();
        formData.append(mName, "");
        formData.append("fake-key-1", file1);

        $.ajax({
            method:'POST',
            data: formData,
            url: this.action,
            processData: false, // Don't process the files
            contentType: false, // Set content type to false as jQuery will tell the server its a query string request
            timeout: 2000,
            error: function(e) {
                console.error("Failed to submit");
                $("#result").text("Failed to get result from server " + e);
            },
            success: function(r) {
               console.log("Success upload file");
            }
        });

        $("#tMapName").val("");
        // return value of the submit operation
        // by default - we'll always return false so it doesn't redirect the user.
        return false;
    })
})


function  triggerAjaxErrorContent(){
    setTimeout(ajaxErrorContent,refreshRate);
}

$(function() {
    $.ajax({
        data: " ",
        url: USER_NAME_URL ,
        timeout: 1000,
        error: function (e) {
            console.error("Failed to submit");
        },
        success: function (user) {
            $('#userNamecontent').text("Hello "+ user.userTypeValue + " "+ user.userNameValue);
        }

    });
})


function refreshMapsContentList(maps) {
    //clear all current users
    if(  $('#queryTable tbody').length > 0)
        $('#queryTable tbody').empty();

    // rebuild the list of users: scan all users and add them to the list of users
    $.each(maps || [], function(index, map) {
        console.log("Adding map #" + index + ": " + map);
        idx = index;
        var SingleMap = createSingleMapEntry(map , idx);
        $('#queryTable tbody').append(SingleMap);
    });
}


function ajaxMapContentList() {
    $.ajax({
        url: MAP_LIST_URL,
        success: function(maps) {
            console.log("success getting json");
            refreshMapsContentList(maps);
        }
    });
}

function bar2Select(appName) {
    var i;
    var x = document.getElementsByClassName("asideData");
    for (i = 0; i < x.length; i++) {
        x[i].style.display = "none";
    }
    document.getElementById(appName).style.display = "block";
}

$(function() {

    //The chat content is refreshed only once (using a timeout) but
    //on each call it triggers another execution of itself later (1 second later)
    setInterval(ajaxMapContentList, refreshRate);
    setInterval(ajaxUsersList, refreshRate);
    setInterval(ajaxChatContentList, refreshRate);
    setInterval(ajaxWalletMoneyAmount, refreshRate);
    setInterval(ajaxWalletTableContent, refreshRate);
    triggerAjaxErrorContent();
});