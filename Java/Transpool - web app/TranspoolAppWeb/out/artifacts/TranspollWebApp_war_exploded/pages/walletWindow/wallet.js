var MONEY_SHOW_URL = buildUrlWithContextPath("showMoney");
var MONEY_CHARGE_URL = buildUrlWithContextPath("chargeMoney");
var WALLET_TABLE_URL = buildUrlWithContextPath("WalletTable");

$(function() { // onload...do
    //add a function to the submit event
    $("#chargingMoneyForm").submit(function() {
        $.ajax({
            data: $(this).serialize(),
            url: MONEY_CHARGE_URL,
            timeout: 2000,
            error: function() {
                console.error("Failed to submit");
            },
            success: function(r) {
                console.log("Charged money");
            }
        });

        $("#moneyAmount").val("");
        // by default - we'll always return false so it doesn't redirect the user.
        return false;
    });
});

function ajaxWalletMoneyAmount() {
    $.ajax({
        url: MONEY_SHOW_URL,
        success: function(money) {
            $('#moneyAmountNumber').text(money + " " + "NIS")
        }
    });
}

function ajaxWalletTableContent() {
    $.ajax({
        url: WALLET_TABLE_URL,
        success: function(walletActions) {
            console.log("success getting json");
            refreshWalletActionList(walletActions);
        }
    });
}

function refreshWalletActionList(walletActions) {
    //clear all current users
    if(  $('#walletTable tbody').length > 0)
        $('#walletTable tbody').empty();

    // rebuild the list of users: scan all users and add them to the list of users
    $.each(walletActions || [], function(index, walletAction) {
        console.log("Adding action #" + index + ": " + walletAction);
        idx = index;
        var SingleWalletAction = createSingleWalletAction(walletAction , idx);
        $('#walletTable tbody').append(SingleWalletAction);
    });
}

function createSingleWalletAction (walletAction,idx){
    var actionMoneyType = walletAction.actionMoneyType;
    var localDateTimeString = walletAction.actionDateTime;
    var actionAmount = walletAction.actionAmount;
    var moneyBefore = walletAction.moneyBefore;
    var moneyAfter = walletAction.moneyAfter;

    var markup = "<tr><td>" + actionMoneyType + "</td><td>" + localDateTimeString
        + "</td><td>" + actionAmount + "</td><td>" +
        moneyBefore + "</td><td>" + moneyAfter +"<tr>";
    return markup;
}
