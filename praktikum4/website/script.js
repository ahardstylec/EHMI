// Get the canvas element for example purposes
function onLoad() {



// Elements from DOM for JavaScript
    myTraceCheckBox = document.getElementById('chkShowTrace');
    myTraceArea = document.getElementById("txtTraceArea");
    myDebugArea = document.getElementById("txtDebugArea");


// Dynamisches erweitern der Objekt-Klasse um die "toggleVisibility" Methode
    Object.prototype.toggleVisibility = function () {
        if (this.style.visibility == "hidden") {
            this.style.visibility = "visible";
        }
        else {
            this.style.visibility = "hidden";
        }
    }

// Helper Functions for Numeric Conversion (Degree -> Radian)
    Number.prototype.toRadians = function () {
        return this * (Math.PI / 180);
    }

// Helper Functions for Numeric Conversion (Radian -> Degree)
    Number.prototype.toDegrees = function () {
        return this * (180 / Math.PI);
    }


// Debug&Trace Messages
    myTraceTemp = "";
    myTraceMessageCnt = 0;

// Display Trace Messages in TextArea
    displayTraceMessage = function displayTraceMessage(message) {
        if (myTraceArea.style.visibility != "visible") {
            return;
        }

        // the following code is just to optimize refreshing of the trace,
        // which is the most expensive function here!
        if (myTraceMessageCnt % 50 == 0) {
            myTraceArea.value = myTraceTemp + "\n";
            myTraceArea.scrollTop = txtTraceArea.scrollHeight;
            myTraceTemp = ""; // Reset Temp
        }
        else {
            myTraceTemp += message + "\n";
        }

        myTraceMessageCnt++;
    }

// Display Debug Messages in TextArea
    displayDebugMessage = function displayDebugMessage(message) {
        if (txtDebugArea.style.visibility != "visible") {
            return;
        }

        txtDebugArea.value = message + "\n";
        txtDebugArea.scrollTop = txtDebugArea.scrollHeight;
    }


// WebSocket Connection URL + Port
    wsUri = "ws://127.0.0.1:18000";
    websocket = null;

// Init WebSockets
    initWebsocket = function initWebsocket() {
        try {
            // Browser Check
            if (typeof MozWebSocket == 'function') {
                WebSocket = MozWebSocket;
            }
            if (websocket && websocket.readyState == 1) {
                websocket.close();
            }

            // New WebSocket Object
            websocket = new WebSocket(wsUri);

            // Event Handler when connection is openend
            websocket.onopen = function (evt) {
                displayTraceMessage("CONNECTED");
            };

            // Event Handler when connection is closed
            websocket.onclose = function (evt) {
                displayTraceMessage("DISCONNECTED");
            };

            // Event Handler for Errors
            websocket.onerror = function (evt) {
                displayTraceMessage('ERROR: ' + evt.data);
            };

            // Event Handler
            websocket.onmessage = function (evt) {
                console.debug("message received");
                var myDataType = "";

                if (evt.data instanceof ArrayBuffer) {
                    myDataType = "ArrayBuffer";
                }
                else if (evt.data instanceof Blob) {
                    myDataType = "Blob";
                }
                else {
                    myDataType = "text";
                }

                if (myTraceCheckBox.checked) {
                    displayTraceMessage(myDataType + ": " + evt.data);
                }

                // Process the received Data
                ProcessCANMessage(evt.data);
            };


        }
        catch (exception) {
            displayTraceMessage('ERROR: ' + exception);
        }
    }


// Stops/Closes the WebSocket and connection
    stopWebsocket = function stopWebsocket() {
        if (websocket) {
            websocket.close();
        }
    }


// Returns the State of the current WebSocket Object
    checkSocket = function checkSocket() {
        if (websocket != null) {
            var stateStr = "";
            switch (websocket.readyState) {
                case 0:
                    stateStr = "CONNECTING";
                    break;
                case 1:
                    stateStr = "OPEN";
                    break;
                case 2:
                    stateStr = "CLOSING";
                    break;
                case 3:
                    stateStr = "CLOSED";
                    break;
                default:
                    stateStr = "UNKNOW";
                    break;
            }

            alert("Websocket state = " + websocket.readyState + " ( " + stateStr + " )");
        }
        else {
            displayTraceMessage("Websocket is null");
        }
    }


// Example Canvas for Speed
    myCESpeed = document.getElementById("myCanvasCarDataSpeed");
    myCECSpeed = myCESpeed.getContext("2d"); // Get Canvas Context for Speed
    myCECSpeed.fillStyle = "#000000";
    myCECSpeed.lineWidth = 1;

// Example Canvas for RPM
    myCERPM = document.getElementById("myCanvasCarDataRPM");
    myCECRPM = myCERPM.getContext("2d"); // Get Canvas Context for RPM
    myCECRPM.fillStyle = "#000000";
    myCECRPM.lineWidth = 1;

// Counts the received overall Messages
    myMessageCnt = 0;
// For Specific Message Types
    myMessageCntSpeed = 0;
    myMessageCntRPM = 0;


// Here we process the received data
// Can be optimized by seperating all of this into seperate functions
    ProcessCANMessage = function ProcessCANMessage(data) {
        // The sent data comes in JSON-Format
        var myJSON = JSON.parse(data);

        // List of IDs we are interested in. (just for performance)
        if (myJSON.ID != 256 && myJSON.ID != 261 && myJSON.ID != 867) {
            return;
        }

        // Debug
        var myDebugMsg = data + '\r\n' + "obj: " + myJSON + '\r\n' + "ID: " + myJSON.ID + '\r\n' + "Data: " + myJSON.Data + '\r\n';

        // Count relevant Messages
        myMessageCnt++;

        // SPEED => ID 256
        if (myJSON.ID == 256) {
            // In C++ we would use bit masks and bit shifting to parse the 64bit value
            // var mySpeedValue = (myRAWSignal & 0xFFFF00000000) >> 32;

            // But JavaSript can't handle 64Bit (8Byte) integer values!
            // So we use this alternative to cut the String before we calculate the value
            var myString = "0x" + myJSON.Data.replace("0x", "").substr(4, 4);

            // finally we get an integer value by using the parseInt-Function
            var myRAWSignal = parseInt(myString);

            // now calculate the real speed based on this formula (see CANTrace-Format.pdf)
            var myRealSpeed = myRAWSignal * 0.01 + 0;   // in Kilometer per Hour
            var myRealSpeedM = (myRealSpeed * 0.621371); // in Miles per Hour

            myDebugMsg += "String: " + myString + '\r\n'
            + "RAW: " + myRAWSignal + '\r\n'
            + "RealSpeed (kmh): " + myRealSpeed + '\r\n'
            + "RealSpeed (mph): " + myRealSpeedM + '\r\n';

            // calculate rotation (min, max and target min max values)
            var MinimumValue = 0;	// Min Value from Trace Data
            var MaximumValue = 257; // Max Value from Trace Data
            var MinimumTargetValue = 0;
            var MaximumTargetValue = myCESpeed.height - 30; // -30px because of the text line
            var myValue = myRealSpeed;
            var myValueInRange = (Math.min(Math.max(myValue, MinimumValue), MaximumValue) - MinimumValue);
            var myRangeOfValue = (MaximumValue - MinimumValue);
            var myResult = MaximumValue == MinimumValue ? MaximumValue : MinimumTargetValue + (MaximumTargetValue - MinimumTargetValue) * myValueInRange / myRangeOfValue;

            // Do something	here

            if (myCECSpeed) {
                var mySpeedY = myCESpeed.height;
                var mySpeedX = myMessageCntSpeed % myCESpeed.width;

                // Clear Two Columns
                myCECSpeed.fillStyle = "#000000";
                myCECSpeed.fillRect(mySpeedX - 1, 0, 3, myCESpeed.height);

                // Draw the Dot
                myCECSpeed.strokeStyle = "#FFFF00";
                myCECSpeed.strokeRect(mySpeedX, mySpeedY - myResult, 1, 1);

                // Draw Blue Line
                myCECSpeed.strokeStyle = "#0000FF";
                myCECSpeed.strokeRect(mySpeedX + 1, 0, 2, myCESpeed.height);

                // Draw Some Text
                myCECSpeed.fillRect(0, 0, myCESpeed.width, 30);
                myCECSpeed.fillStyle = '#ff0';
                myCECSpeed.font = 'italic 30px sans-serif';
                myCECSpeed.textBaseline = 'top';
                myCECSpeed.fillText('Speed: ' + myRealSpeed.toFixed(2) + ' km/h', 0, 0);

                myMessageCntSpeed++;
            }
        }


        // RPM (Drehzahl & Pedal)
        if (myJSON.ID == 261) {
            // In Qt/C++ we would use bit masks and bit shifting to parse the 64bit value
            // qreal myRPM = (myCANMessageContainer & 0xFFFF0000) >> 16;

            // But JavaSript can't handle 64Bit (8Byte) integer values!
            // So we use this alternative to cut the String before we calculate the value
            var myString = "0x" + myJSON.Data.replace("0x", "").substr(8, 4);

            // finally we get an integer value by using the parseInt-Function
            var myRAWSignal = parseInt(myString);

            // Ok use the formula to calculate the real physical value
            var myRealRPM = myRAWSignal * 0.25 + 0;

            // calculate rotation (min, max and target min max values)
            var MinimumValue = 0;
            var MaximumValue = 8000;
            var MinimumTargetValue = 0;
            var MaximumTargetValue = myCERPM.height - 30; // -30px because of the text line
            var myValue = myRealRPM;
            var myValueInRange = (Math.min(Math.max(myValue, MinimumValue), MaximumValue) - MinimumValue);
            var myRangeOfValue = (MaximumValue - MinimumValue);
            var myResult = MaximumValue == MinimumValue ? MaximumValue : MinimumTargetValue + (MaximumTargetValue - MinimumTargetValue) * myValueInRange / myRangeOfValue;

            // Do something

            if (myCECRPM) {
                var myRPMY = myCERPM.height;
                var myRPMX = myMessageCntRPM % myCERPM.width;

                // Clear Two Columns
                myCECRPM.fillStyle = "#000000";
                myCECRPM.fillRect(myRPMX - 1, 0, 3, myCERPM.height);

                // Draw the Dot
                myCECRPM.strokeStyle = "#FFFF00";
                myCECRPM.strokeRect(myRPMX, myRPMY - myResult, 1, 1);

                // Draw Blue Line
                myCECRPM.strokeStyle = "#0000FF";
                myCECRPM.strokeRect(myRPMX + 1, 0, 2, myCERPM.height);

                myCECRPM.fillRect(0, 0, myCERPM.width, 30);
                myCECRPM.fillStyle = '#ff0';
                myCECRPM.font = 'italic 30px sans-serif';
                myCECRPM.textBaseline = 'top';
                myCECRPM.fillText('RPM: ' + myRealRPM.toFixed(2) + ' U/Min', 0, 0);

                myMessageCntRPM++;
            }
        }


        // Blinker
        if (myJSON.ID == 867) {
            // In Qt/C++ we would use bit masks and bit shifting to parse the 64bit value
            //int myBlinkerRechts = (int)((myCANMessageContainer & 0x200) >> 9);
            //int myBlinkerLinks = (int)((myCANMessageContainer & 0x100) >> 8);

            // But JavaSript can't handle 64Bit (8Byte) integer values!
            // So we use this alternative to cut the String before we calculate the value
            var myString = "0x" + myJSON.Data.replace("0x", "").substr(5, 1);

            var myBlinkerLinks = parseInt(myString) >> 1;
            var myBlinkerRechts = parseInt(myString) & 0x1;

            if (myBlinkerLinks > 0) {
                // Do something
            }

            if (myBlinkerRechts > 0) {
                // Do something
            }
        }

        // Add more IDs here

        displayDebugMessage(myDebugMsg);
    }

    switchMode = function () {
        $('#canvasWrapper').toggleClass('normal_mode special_mode');
    }

    myCanvasElement = document.getElementById("myCanvasSimpleDrawing");

// Draw something on a canvas
    drawCanvasExample = function () {
        console.debug("drawing canvas");
        // Make sure there is a context available
        if (!myCanvasElement.getContext) {
            console.debug("no canvas context");
            return;
        }

        // Reset the Canvas
        // Setting the width or height of a <canvas> element will erase its contents and
        // reset all the properties of its drawing context to their default values. The values don't have to be changed.
        // Simply re-set it to its current value, as for example:
        myCanvasElement.width = myCanvasElement.width;

        // Specify 2d canvas type.
        var ctx = myCanvasElement.getContext("2d");

        var speedNeedleNormal = new Image();
        speedNeedleNormal.src = 'data/bilder/normal-needle_speed.svg';

        console.debug("drawing speed needle");
        speedNeedleNormal.onload = function () {
            ctx.drawImage(speedNeedleNormal, 0, 0);
        }

    };

    drawSpeedNeedle = function () {

    }
}