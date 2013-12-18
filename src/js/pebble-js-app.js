(function() {
"use strict";

var APP_CONFIGURATION_URL = "http://apps.exceede.com/pebble/bitcoin-watchface.html";
var TICKER_URL = "https://api.bitcoinaverage.com/ticker/";

function getSettings()
{
    var settings = [];
    try
    {
        JSON.parse(localStorage.getItem("settings"));
    }
    catch(ex) { console.error("Brokent settings: " + ex.message); }
    return settings;
}

function getSymbol(symbol)
{
    var xhr = new XMLHttpRequest();

    xhr.open('GET', TICKER_URL + symbol.toUpperCase(), true);
    xhr.onload = function(e)
    {
        if(4 === xhr.readyState && 200 === req.status)
        {
            try
            {
                var response = JSON.parse(xhr.responseText);
                Pebble.sendAppMessage(
                {
                    "symbol": symbol,
                    "price": response.last,
                    "ask": response.ask,
                    "bid": response.bid
                },
                function(e) { console.log('AppMessage delivered. TxId: ' + e.transactionId); });
            }
            catch(ex)
            {
                Pebble.sendAppMessage(ex.message);
            }
        }
    };
}

Pebble.addEventListener("ready",
    function(e) {
        console.log("Initialized");
        var settings = getSettings();
        if(!settings.length)
        {
            Pebble.sendAppMessage("Please configure the bitcoin watcher app");
            return;
        }
        getSymbol(settings[0]);
    }
);

Pebble.addEventListener("showConfiguration",
    function onShowConfiguration(e)
    {
        var settings = getSettings();
        var url = APP_CONFIGURATION_URL + "#" + encodeURIComponent(JSON.stringify(settings));
        console.log("Opening configuration: " + url);
        Pebble.openURL(url);
    }
);

Pebble.addEventListener("webviewclosed",
    function onConfigurationComplete(e)
    {
        console.log("Configuration Window closed: " + e.response);
        try
        {
            var settings = JSON.parse(decodeURIComponent(e.response));
            localStorage.putItem(settings, JSON.stringify(settings));
        }
        catch(ex) { console.error(ex); }
    }
);

}());
