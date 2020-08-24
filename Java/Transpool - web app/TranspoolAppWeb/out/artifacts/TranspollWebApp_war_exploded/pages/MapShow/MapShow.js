var USER_NAME_URL = buildUrlWithContextPath("userNameServlet");
var REQUESTS_LIST_URL = buildUrlWithContextPath("requestslistServlet");
var SUGGESTIONS_LIST_URL = buildUrlWithContextPath("SuggestionlistServlet");
var FIND_MATCHES_URL = buildUrlWithContextPath("FindMatchOffers");
var MATCH_OFFER_INFO_URL = buildUrlWithContextPath("MatchOfferInfo");
var MATCH_MAKER_URL = buildUrlWithContextPath("MakeAMatch");
var FORM_MAKER_URL = buildUrlWithContextPath("FormErorListServlet");


var refreshRate = 2000; //milli seconds

$(function() {

    $.ajax({
        data: " ",
        url: "MapData",
        timeout: 2000,
        error: function (e) {
            console.error("Failed to submit");
        },
        success: function (map) {
            var svgNS = "http://www.w3.org/2000/svg";
            SaveMapObject(map);
            CreateSvgBorder(map);
            createPoints(svgNS,map.modelLogic.transPool.mapDescriptor.mapBoundries.length, map.modelLogic.transPool.mapDescriptor.mapBoundries.width);
            createStation(map,svgNS);
            createPaths(map,svgNS);
            userNameAjaxcall();

           
        }

    });


});

function userNameAjaxcall() {
    $.ajax({
        data: " ",
        url: USER_NAME_URL,
        timeout: 2000,
        error: function (e) {
            console.error("Failed to submit");
        },
        success: function (user) {
            $('#userNamecontent').text("Hello "+ user.userTypeValue + " "+ user.userNameValue);
            window.UserType = user.userTypeValue;

            if(!user.userTypeValue.localeCompare("Driver"))
            {
                $('#RequestsSectionTitle').text("All Requests");
                $('#OffersSectionTitle').text("Your Offers");
                UploadSuggestionFrom();

            }
            else{
                if(!user.userTypeValue.localeCompare("Passenger"))
                {
                    $('#RequestsSectionTitle').text("Your Requests");
                    $('#OffersSectionTitle').text("All Offers");
                    UploadRequestFrom();
                }
            }
            setInterval(ajaxRequestsTable, refreshRate);
            setInterval(ajaxSuggestionTable, refreshRate);

        }

    });
}

$(function() {

    $(document).on('click', '.MakeMatchBtn', function () {
        $.ajax({
            data: "matchOfferNumber=" + $(this).attr('id'),
            url: MATCH_MAKER_URL,
            timeout: 2000,
            error: function (e) {
                console.error("Failed to submit");
            },
            success: function (requests) {
                $("#matchModal").modal('hide');

            }
        });


    });
});
$(function() {

    $(document).on('click', '.MatchSuggestionsInfoBtn', function () {
        $.ajax({
            data: "matchOfferNumber=" + $(this).attr('id'),
            url: MATCH_OFFER_INFO_URL,
            timeout: 2000,
            error: function (e) {
                console.error("Failed to submit");
            },
            success: function (info) {
                $("#infoText").text(info);
                $("#matchOfferInfoModal").modal();
            }
        });


    });
});

$(function() {

    $(document).on('click', '.MatchBtn', function () {
        $.ajax({
            data: "requestNumber=" + $(this).attr('id'),
            url: FIND_MATCHES_URL,
            timeout: 2000,
            error: function (e) {
                console.error("Failed to submit");
            },
            success: function (matchedOffers) {
                console.log("matched yes");
                $('#MatchTable thead').empty();
                if($('#MatchTable tbody').length > 0) {
                    $('#MatchTable tbody').empty();
                }
                $('#MatchTable thead').append(CreateMatchSuggestionMarkUpTable());
                matchedOffers.forEach(MatchSuggestfunc);
                function MatchSuggestfunc(value, index, array) {
                    $('#MatchTable tbody').append(CreateMatchSuggestDetails(value));
                }
                $("#matchModal").modal();

            }
        });


    });
});

function CreateMatchSuggestionMarkUpTable()
{
    var markup = "<tr><td>" + "Offer's Number" +"</td><td>" + "Offer Type" + "</td><td>" + "Ride Cost"
        + "</td><td>" + "estimated Time" + "</td><td>" + "Avg Fuel" + "</td><td>" + "Info"
        + "</td><td>" + "Match" +  "</td></tr>";
    return markup;
}
function CreateMatchSuggestDetails(value) {
    var Details = "<tr><td>" +  value.OfferNumber + "</td><td>" + value.offerType + "</td><td>" +
        value.offerCost + "</td><td>" + value.estimatedTimeString + "</td><td>"
        + value.passengerAvgFuelUtilization
        + "</td><td>" +  '<button class="MatchSuggestionsInfoBtn"' + " id=" + value.OfferNumber
        + '>' +"Info" + "</button>"
        + "</td><td>" +  '<button class="MakeMatchBtn"' + " id=" + value.OfferNumber
        + '>' +"Match" + "</button>"
        + "</td></tr>";
    return Details;
}


function SaveMapObject(data){
    window.Map = data;
};



function UploadRequestFrom() {

    var Stops =  window.Map.modelLogic.transPool.mapDescriptor.stops.stop;
    var CurrenStoplabel = $("<label>").text('Choose your current stop:        ');
    var DestinationStoplabel = $("<label>").text('Choose your Destination stop:    ');
    var Departuretime = $("<label style='font-weight: bold'>").text('Departure time:   ');
    var DayLabel = $("<label>").text('Day:   ');
    var HourLabel = $("<label>").text('Hour:   ');
    var MinutesLabel = $("<label>").text('Minutes:  ');

    $("#DynamicForm").attr('method', 'POST');
    $("#DynamicForm").attr('action', 'RequestUpdateServlet');
    $("#DynamicForm").append( '<h2 style="font-family: Brush Script MT, Brush Script Std, cursive; color: whitesmoke; font-size: 30px "> Add Trip Request</h2>');
    $("#DynamicForm").append(CurrenStoplabel);
    $("#DynamicForm").append('<select name="CurrenStop" id="CurrenStop""></select>'+ '<br>');
    $("#DynamicForm").append(DestinationStoplabel);
    $("#DynamicForm").append('<select name="DestinationStop" id="DestinationStop"></select>' + '<br>');
    $("#DynamicForm").append(Departuretime);
    $("#DynamicForm").append('<br>');
    $("#DynamicForm").append(DayLabel);
    $("#DynamicForm").append('<select name="Day" id="Day"></select>'+ '<br>');
    $("#DynamicForm").append(HourLabel);
    $("#DynamicForm").append('<select name="Hour" id="Hour"></select>'+ '<br>');
    $("#DynamicForm").append(MinutesLabel);
    $("#DynamicForm").append('<select name="Minutes" id="Minutes"></select>'+ '<br>');
    $("#DynamicForm").append('<br>');
    $("#DynamicForm").append('<input type="submit" value="ADD" />');


    Stops.forEach(stopsfunc);
    function stopsfunc(value, index, array) {
        $("#CurrenStop").append('<option value=' + value.name +'>' +  value.name + '</option>');
        $("#DestinationStop").append('<option value=' + value.name +'>' +  value.name + '</option>');
    }

    var i;
    for (i=1 ; i< 100 ; i++)
    {
        $("#Day").append('<option value=' + i +'>' +  i + '</option>');
    }
    for (i=0 ; i< 23 ; i++)
    {
        $("#Hour").append('<option value=' + i +'>' +  i + '</option>');
    }
    for (i=0 ; i< 59 ; i++)
    {
        $("#Minutes").append('<option value=' + i +'>' +  i + '</option>');

    }
}

function UploadSuggestionFrom() {

    var Stops =  window.Map.modelLogic.transPool.mapDescriptor.stops.stop;

    var Capacity = $("<label>").text('Choose your Capacity:  ');
    var recurrences = $("<label>").text('Choose your Travel Scheduling:  ');
    var ppk = $("<label>").text('Choose price per kilometer:  ');
    var Route = $("<label>").text('Choose your Route: Example: A,B,C,D  ');
    var Departuretime = $("<label style='font-weight: bold'>").text('Departure time:');
    var DayLabel = $("<label>").text('Day :');
    var HourLabel = $("<label>").text('Hour :');
    var MinutesLabel = $("<label>").text('Minutes :');

    $("#DynamicForm").attr('method', 'POST');
    $("#DynamicForm").attr('action', 'SuggestionUpdateServlet');
    $("#DynamicForm").append( '<h2 style="font-family: Brush Script MT, Brush Script Std, cursive; color: whitesmoke; font-size: 30px "> Add Trip Offer</h2>');
    $("#DynamicForm").append(Capacity);
    $("#DynamicForm").append('<select name="Capacity" id="Capacity"></select>'+ '<br>');
    $("#DynamicForm").append(ppk);
    $("#DynamicForm").append('<select name="PPK" id="PPK"></select>'+ '<br>');
    $("#DynamicForm").append(Route);
    $("#DynamicForm").append('<input type ="text" name="Route" >'+ '<br>');
    $("#DynamicForm").append(recurrences);
    $("#DynamicForm").append('<select name="recurrences" id="recurrences"></select>'+ '<br>');
    $("#DynamicForm").append(Departuretime);
    $("#DynamicForm").append('<br>');
    $("#DynamicForm").append(DayLabel);
    $("#DynamicForm").append('<select name="Day" id="Day"></select>'+ '<br>');
    $("#DynamicForm").append(HourLabel);
    $("#DynamicForm").append('<select name="Hour" id="Hour"></select>'+ '<br>');
    $("#DynamicForm").append(MinutesLabel);
    $("#DynamicForm").append('<select name="Minutes" id="Minutes"></select>'+ '<br>');
    $("#DynamicForm").append('<br>');
    $("#DynamicForm").append('<input type="submit" value="ADD" />');


    Stops.forEach(stopsfunc);
    function stopsfunc(value, index, array) {
        $("#CurrenStop").append('<option value=' + value.name +'>' +  value.name + '</option>');
        $("#DestinationStop").append('<option value=' + value.name +'>' +  value.name + '</option>');
    }

    var i;
    for (i=1 ; i< 100 ; i++)
    {
        $("#Day").append('<option value=' + i +'>' +  i + '</option>');
    }
    for (i=0 ; i< 23 ; i++)
    {
        $("#Hour").append('<option value=' + i +'>' +  i + '</option>');
        $("#PPK").append('<option value=' + i +'>' +  i + '</option>');
    }
    for (i=0 ; i< 59 ; i++)
    {
        $("#Minutes").append('<option value=' + i +'>' +  i + '</option>');

    }
    for (i=1 ; i< 7 ; i++)
    {
        $("#Capacity").append('<option value=' + i +'>' +  i + '</option>');

    }

        $("#recurrences").append('<option value="OneTime">' +  "OneTime" + '</option>');
    $("#recurrences").append('<option value="Daily">' +  "Daily" + '</option>');
    $("#recurrences").append('<option value="BiDaily">' +  "BiDaily" + '</option>');
    $("#recurrences").append('<option value="Weekly">' +  "Weekly" + '</option>');
    $("#recurrences").append('<option value="Monthly">' +  "Monthly" + '</option>');
}




function CreateSvgBorder(map) {
    var Mapwidth = 41 *(map.modelLogic.transPool.mapDescriptor.mapBoundries.width);
    var MapHight = 31 *(map.modelLogic.transPool.mapDescriptor.mapBoundries.length)

    document.getElementById('mySVG').setAttribute("height", "1000");
    document.getElementById('mySVG').setAttribute("width", "1000");
    if(document.getElementById('maplimits') != null) {
        document.getElementById('maplimits').setAttribute("height", MapHight);
        document.getElementById('maplimits').setAttribute("width", Mapwidth);
    }
    else
    {
        var rect = document.createElementNS("http://www.w3.org/2000/svg",'rect');
        rect.setAttribute('id',"maplimits");
        rect.setAttribute('style',"fill:lightblue;stroke-width:1;stroke:rgb(0,0,0)");
        rect.setAttribute('width',Mapwidth);
        rect.setAttribute('height',MapHight);
        document.getElementById("mySVG").appendChild((rect));

    }
}

function createPoints(svgNS,length,width)
{
    var cirx = 30, ciry=20;
    var i;
    var j;
    for(j=0; j<length;j++) {
        for (i = 0; i < width; i++) {
            var myCircle = document.createElementNS(svgNS, "circle"); //to create a circle. for rectangle use "rectangle"
            myCircle.setAttributeNS(null, "id", "mycircle");
            myCircle.setAttributeNS(null, "cx", cirx);
            myCircle.setAttributeNS(null, "cy", ciry);
            myCircle.setAttributeNS(null, "r", 2);
            myCircle.setAttributeNS(null, "fill", "black");
            myCircle.setAttributeNS(null, "stroke", "none");
            document.getElementById("mySVG").appendChild(myCircle);
            cirx = cirx + 40;
        }
        cirx = 30;
        ciry = ciry + 30;
    }

}

function createStation(map,svgNS)
{
    var stoplist = map.modelLogic.transPool.mapDescriptor.stops.stop;
    stoplist.forEach(stopsfunc);

    function stopsfunc(value, index, array) {
        var myCircle = document.createElementNS(svgNS, "circle"); //to create a circle. for rectangle use "rectangle"
        myCircle.setAttributeNS(null, "id", value.name);
        myCircle.setAttributeNS(null, "cx", 30 + value.x*40);
        myCircle.setAttributeNS(null, "cy", 20 + value.y*30);
        myCircle.setAttributeNS(null, "r", 7);
        myCircle.setAttributeNS(null, "fill", "red");
        myCircle.setAttributeNS(null, "stroke", "none");
        myCircle.setAttributeNS(null, "title", "Station - " + value.name);
        document.getElementById("mySVG").appendChild(myCircle);
        CreateStationName(value,svgNS);
    }


}


function CreateStationName(value,svgNS) {
    var myText = document.createElementNS(svgNS, "text"); //to create a circle. for rectangle use "rectangle"
    myText.setAttributeNS(null, "x", 40 + value.x*40);
    myText.setAttributeNS(null, "y", 20 + value.y*30);
    myText.setAttributeNS(null, "fill", "blue");
    myText.setAttributeNS(null, "font-size", "15px");
    myText.textContent = value.name;
    document.getElementById("mySVG").appendChild( myText);

}
function createPaths(map,svgNS) {
    var pathlist = map.modelLogic.transPool.mapDescriptor.paths.path;
    pathlist.forEach(pathfunc);
    function pathfunc(value, index, array) {

        var coordxFrom = FindStopCordX(map,value.from);
        var coordyFrom = FindStopCordY(map,value.from);
        var coordxTo = FindStopCordX(map,value.to);
        var coordyTo = FindStopCordY(map,value.to);

        var myLine = document.createElementNS(svgNS, "line"); //to create a circle. for rectangle use "rectangle"
        myLine.setAttributeNS(null, "id", value.name);
        myLine.setAttributeNS(null, "x1", 30 + coordxFrom * 40);
        myLine.setAttributeNS(null, "y1", 20 + coordyFrom * 30);
        myLine.setAttributeNS(null, "x2", 30 + coordxTo *40);
        myLine.setAttributeNS(null, "y2", 20 + coordyTo *30);
        myLine.setAttributeNS(null, "style", "stroke:blue;stroke-width:1");
        document.getElementById("mySVG").appendChild(myLine);
    }

}

function FindStopCordX(map,StopName) {
    var stoplist = map.modelLogic.transPool.mapDescriptor.stops.stop;
    var i;
    var ret;
    for(i =0 ; i<stoplist.length; i++) {
        if(StopName == stoplist[i].name)
        {
            ret = stoplist[i].x;
        }
    }

    return ret;


}

function FindStopCordY(map,StopName) {
    var stoplist = map.modelLogic.transPool.mapDescriptor.stops.stop;
    var i;
    var ret;

    for(i =0 ; i<stoplist.length; i++) {
        if(StopName == stoplist[i].name)
        {
            ret = stoplist[i].y;
        }
    }
    return ret;
}

function refreshRequestsTable(Requests)
{
    $('#DynamicRequestTable thead').empty();
    if ($('#DynamicRequestTable tbody').length > 0) {
        $('#DynamicRequestTable tbody').empty();
    }
    $('#DynamicRequestTable thead').append(CreateRequestsMarkUpTable());

    Requests.forEach(requestfunc);

    function requestfunc(value, index, array) {
        $('#DynamicRequestTable tbody').append(CreateRequestsDetails(value));
    }

}

function ajaxRequestsTable() {
    $.ajax({
        url: REQUESTS_LIST_URL,
        success: function(Requests) {
            window.Requests = Requests;
            refreshRequestsTable(Requests);
        }
    });
}

function ajaxSuggestionTable() {
    $.ajax({
        url: SUGGESTIONS_LIST_URL,
        success: function(Offers) {
            console.log(Offers);
            window.Suggestion = Offers;
            refreshSuggestionTable(Offers);
        }
    });
}

function refreshSuggestionTable(Offers)
{
    $('#DynamicSuggestionTable thead').empty();
    if($('#DynamicSuggestionTable tbody').length > 0) {
        $('#DynamicSuggestionTable tbody').empty();
    }
    $('#DynamicSuggestionTable thead').append(CreateSuggestionMarkUpTable());

    Offers.forEach(Suggestfunc);
    function Suggestfunc(value, index, array) {
        $('#DynamicSuggestionTable tbody').append(CreateSuggestionDetails(value));
    }

}

function CreateSuggestionDetails(value) {
    var Details =   "<tr><td>" +  value.OrderNumber +"</td><td>" +  value.owner +  "</td><td>" + value.capacity + "</td><td>" +
        value.ppk + "</td><td>" + value.route.path + "</td><td>" + value.scheduling.recurrences + "</td><td>"
        + value.scheduling.dayStart + "</td><td>" + value.scheduling.hourStart + "</td><td>" + value.scheduling.hourStart + "</td><td>"
        + '<button class="mybtnSuggestion"' + " id=" + value.OrderNumber + '>' +"View" + "</button>" + "</td></tr>";
    return Details;
}
function CreateSuggestionMarkUpTable()
{
    var markup = "<tr><td>" + "Order Number" +"</td><td>" + "Driver's Name" + "</td><td>" + "Capacity"
        + "</td><td>" + "ppk" + "</td><td>" +
        "Route" + "</td><td>" +  "recurrences" + "</td><td>"
        + "Day" + "</td><td>" + "Hours" + "</td><td>" + "Minutes" + "</td><td>" + "View" + "</td></tr>";

    return markup;
}

function CreateRequestsDetails(value) {
    var Details = "<tr><td>" +  value.OrderNumber + "</td><td>" + value.FirstName + "</td><td>" +
        value.CurrentLocation + "</td><td>" + value.Destination + "</td><td>"
        + value.Day + "</td><td>" + value.Hour + "</td><td>" + value.Minutes + "</td><td>"
        + '<button class="mybtnRequests"' + " id=" + value.OrderNumber + '>' +"View" + "</button>";
    if(!window.UserType.localeCompare("Passenger"))
    {
        if(!(value.m_MatchTrip === null))
            Details = Details + "</td><td>" +  '<button class="MatchBtn"' + " id=" + value.OrderNumber + '>' +"Match" + "</button>" + "</td></tr>";
        else
            Details = Details + "</td><td>" +  '<button class="MatchInfoBtn"' + " id=" + value.OrderNumber + '>' +"Match Info" + "</button>" + "</td></tr>";
    }
    else
    {
        Details = Details +  "</td></tr>";
    }

    return Details;
}
function CreateRequestsMarkUpTable()
{
    var markup = "<tr><td>" + "Order Number" + "</td><td>" + "Passenger's Name" + "</td><td>" +
        "CurrentLocation" + "</td><td>" + "Destination" + "</td><td>"
        + "Day" + "</td><td>" + "Hours" + "</td><td>" + "Minutes" + "</td><td>" + "View";
    if(! window.UserType.localeCompare("Passenger"))
    {
        markup = markup +  "</td><td>"+  "Match" + "</td></tr>";
    }
    else
    {
        markup = markup +  "</td></tr>";
    }
    return markup;
}
function SideBarSelect(appName) {
    var i;
    var x = document.getElementsByClassName("asideData");
    for (i = 0; i < x.length; i++) {
        x[i].style.display = "none";
    }
    document.getElementById(appName).style.display = "block";
}

function FootBarSelect(appName) {
    var i;
    var x = document.getElementsByClassName("footData");
    for (i = 0; i < x.length; i++) {
        x[i].style.display = "none";
    }
    document.getElementById(appName).style.display = "block";
}


function  triggerFormAjaxErrorContent(){
    setTimeout(ajaxFormErrorContent,refreshRate);
}



function RefreshMap() {
    var svgNS = "http://www.w3.org/2000/svg";
    var node = document.getElementById('mySVG');
    node.innerHTML = "";

    CreateSvgBorder(window.Map);
    createPoints(svgNS,window.Map.modelLogic.transPool.mapDescriptor.mapBoundries.length, window.Map.modelLogic.transPool.mapDescriptor.mapBoundries.width);
    createStation(window.Map,svgNS);
    createPaths(window.Map,svgNS);

}

function  DrawPath(Suggestion) {
    var path = Suggestion.route.path;
    var i;
    for(var i = 0 ; i<path.length -1;i = i+2)
    {
        var FirstStop = path[i];
        var SecondStop = path[i + 2];
        var coordxFrom = FindStopCordX(window.Map,FirstStop);
        var coordyFrom = FindStopCordY(window.Map,FirstStop);
        var coordxTo = FindStopCordX(window.Map,SecondStop);
        var coordyTo = FindStopCordY(window.Map,SecondStop);
        var myLine = document.createElementNS("http://www.w3.org/2000/svg", "line"); //to create a circle. for rectangle use "rectangle"
        myLine.setAttributeNS(null, "x1", 30 + coordxFrom * 40);
        myLine.setAttributeNS(null, "y1", 20 + coordyFrom * 30);
        myLine.setAttributeNS(null, "x2", 30 + coordxTo *40);
        myLine.setAttributeNS(null, "y2", 20 + coordyTo *30);
        myLine.setAttributeNS(null, "style", "stroke:green;stroke-width:3");
        document.getElementById("mySVG").appendChild(myLine);

    }

}
function DrawCurrentStop(Stop)
{
    var coordxFrom = FindStopCordX(window.Map,Stop);
    var coordyFrom = FindStopCordY(window.Map,Stop);
    var myCircle = document.createElementNS("http://www.w3.org/2000/svg", "circle"); //to create a circle. for rectangle use "rectangle"
    myCircle.setAttributeNS(null, "id", Stop.name);
    myCircle.setAttributeNS(null, "cx", 30 + coordxFrom*40);
    myCircle.setAttributeNS(null, "cy", 20 + coordyFrom*30);
    myCircle.setAttributeNS(null, "r", 8);
    myCircle.setAttributeNS(null, "fill", "Green");
    myCircle.setAttributeNS(null, "stroke", "none");
    myCircle.setAttributeNS(null, "title", "Station - " + Stop.name);
    document.getElementById("mySVG").appendChild(myCircle);
}

function DrawDestinationStop(Stop)
{
    var coordxTo = FindStopCordX(window.Map,Stop);
    var coordyTo = FindStopCordY(window.Map,Stop);
    var myCircle = document.createElementNS("http://www.w3.org/2000/svg", "circle"); //to create a circle. for rectangle use "rectangle"
    myCircle.setAttributeNS(null, "id", Stop.name);
    myCircle.setAttributeNS(null, "cx", 30 + coordxTo*40);
    myCircle.setAttributeNS(null, "cy", 20 + coordyTo*30);
    myCircle.setAttributeNS(null, "r", 8);
    myCircle.setAttributeNS(null, "fill", "Green");
    myCircle.setAttributeNS(null, "stroke", "none");
    myCircle.setAttributeNS(null, "title", "Station - " + Stop.name);
    document.getElementById("mySVG").appendChild(myCircle);
}

function ajaxFormErrorContent() {
    $.ajax({
        data: " ",
        url: FORM_MAKER_URL,
        timeout: 2000,
        success: function (res) {
            console.log("************" + res);
            if(res.toString() === "upload succeeded")
            {
                $('#uploadErrors').css("color", "green");
            }
            else
            {
                $('#uploadErrors').css("color", "red");
            }

            $('#uploadErrors').text(res);
            triggerFormAjaxErrorContent();
        },
        error: function(error) {
            console.error("Failed to submit");
            triggerFormAjaxErrorContent();
        }
    });
}

$(function() {

    //The chat content is refreshed only once (using a timeout) but
    //on each call it triggers another execution of itself later (1 second later)
    setInterval(ajaxUsersList, refreshRate);
    setInterval(ajaxChatContentList, refreshRate);
    triggerFormAjaxErrorContent();

    $(document).on('click', '.mybtnRequests', function () {
        RefreshMap();
        var i = 0;
        for(i=0 ; i<window.Requests.length; i++) {

            if(window.Requests[i].OrderNumber == $(this).attr('id')) {

                DrawCurrentStop(window.Requests[i].CurrentLocation);
                DrawDestinationStop(window.Requests[i].Destination);
            }
        }
    });

    $(document).on('click', '.mybtnSuggestion', function () {
        RefreshMap();
        var i = 0;
        for(i=0 ; i<window.Suggestion.length; i++) {

            if(window.Suggestion[i].OrderNumber == $(this).attr('id')) {

                DrawPath(window.Suggestion[i]);
            }
        }
    });

});