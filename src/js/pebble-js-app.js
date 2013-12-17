(function() {
"use strict";

var APP_CONFIGURATION_URL = "http://apps.exceede.com/pebble/bitcoin-watchface.html";

Pebble.addEventListener("ready",
    function(e) {
        console.log("Initialized");

    }
);

Pebble.addEventListener("showConfiguration",
    function onShowConfiguration(e)
    {
        var settings = [];
        try
        {
            JSON.parse(localStorage.getItem("settings"));
        }
        catch(ex) { console.error("Brokent settings: " + ex.message); }
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
