var ws;

Pebble.addEventListener("ready",
    function(e) {
        console.log('ready');
    }
);

Pebble.addEventListener("appmessage",
    function(e) {
        console.log(e.payload.control);
        if (ws == null) {
            var host = localStorage.getItem('host');
            ws = new WebSocket('ws://' + host + '/ws');
            ws.onopen = function() {
                ws.send(e.payload.control.toString());
                console.log('send');
            }
        } else {
            ws.send(e.payload.control.toString());
            console.log('send');
        }
    }
)

Pebble.addEventListener("showConfiguration", function() {
  console.log("showing configuration");
  var options = {host: localStorage.getItem('host')};
  var encodedOptions = encodeURIComponent(JSON.stringify(options));
  Pebble.openURL('http://dkpyn.com/sandbox/pebble/config.html#' + encodedOptions);
});

Pebble.addEventListener("webviewclosed", function(e) {
  console.log("configuration closed");
  options = JSON.parse(decodeURIComponent(e.response));
  localStorage.setItem('host', options.host);
  console.log("Options = " + JSON.stringify(options));
});;
