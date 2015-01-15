toggleVisibility = ->
    if @style.visibility is "hidden"
        @style.visibility = "visible"
    else
        @style.visibility = "hidden"

class CanControls
    constructor: ->
        # Elements from DOM for JavaScript
        @myTraceCheckBox = document.getElementById("chkShowTrace")
        @myTraceArea = document.getElementById("txtTraceArea")
        @myTraceArea.toggleVisibility = toggleVisibility

        @myDebugArea = document.getElementById("txtDebugArea")
        @myDebugArea.toggleVisibility = toggleVisibility

$(->
    window.canControls = new CanControls
)

class CanConnection
    constructor: ->




# Get the canvas element for example purposes
$(->


    # Dynamisches erweitern der Objekt-Klasse um die "toggleVisibility" Methode
    Object::toggleVisibility = ->



        # Helper Functions for Numeric Conversion (Degree -> Radian)
    Number::toRadians = ->
        this * (Math.PI / 180)


    # Helper Functions for Numeric Conversion (Radian -> Degree)
    Number::toDegrees = ->
        this * (180 / Math.PI)


    # Debug&Trace Messages
    myTraceTemp = ""
    myTraceMessageCnt = 0

    # Display Trace Messages in TextArea
    displayTraceMessage = displayTraceMessage = (message) ->
        return  unless myTraceArea.style.visibility is "visible"

        # the following code is just to optimize refreshing of the trace,
        # which is the most expensive function here!
        if myTraceMessageCnt % 50 is 0
            myTraceArea.value = myTraceTemp + "\n"
            myTraceArea.scrollTop = txtTraceArea.scrollHeight
            myTraceTemp = "" # Reset Temp
        else
            myTraceTemp += message + "\n"
        myTraceMessageCnt++


    # Display Debug Messages in TextArea
    displayDebugMessage = displayDebugMessage = (message) ->
        return  unless txtDebugArea.style.visibility is "visible"
        txtDebugArea.value = message + "\n"
        txtDebugArea.scrollTop = txtDebugArea.scrollHeight


    # WebSocket Connection URL + Port
    wsUri = "ws://127.0.0.1:18000"
    websocket = null

    # Init WebSockets
    initWebsocket = initWebsocket = ->
        try

        # Browser Check
            WebSocket = MozWebSocket  if typeof MozWebSocket is "function"
            websocket.close()  if websocket and websocket.readyState is 1

            # New WebSocket Object
            websocket = new WebSocket(wsUri)

            # Event Handler when connection is openend
            websocket.onopen = (evt) ->
                displayTraceMessage "CONNECTED"


            # Event Handler when connection is closed
            websocket.onclose = (evt) ->
                displayTraceMessage "DISCONNECTED"


            # Event Handler for Errors
            websocket.onerror = (evt) ->
                displayTraceMessage "ERROR: " + evt.data


            # Event Handler
            websocket.onmessage = (evt) ->
                console.debug "message received"
                myDataType = ""
                if evt.data instanceof ArrayBuffer
                    myDataType = "ArrayBuffer"
                else if evt.data instanceof Blob
                    myDataType = "Blob"
                else
                    myDataType = "text"
                displayTraceMessage myDataType + ": " + evt.data  if myTraceCheckBox.checked

                # Process the received Data
                ProcessCANMessage evt.data
        catch exception
            displayTraceMessage "ERROR: " + exception


    # Stops/Closes the WebSocket and connection
    stopWebsocket = stopWebsocket = ->
        websocket.close()  if websocket


    # Returns the State of the current WebSocket Object
    checkSocket = checkSocket = ->
        if websocket?
            stateStr = switch websocket.readyState
                when 0 then "CONNECTING"
                when 1 then "OPEN"
                when 2 then "CLOSING"
                when 3 then "CLOSED"
                else "UNKNOW"
            alert "Websocket state = " + websocket.readyState + " ( " + stateStr + " )"
        else
            displayTraceMessage "Websocket is null"


    # Example Canvas for Speed
    myCESpeed = document.getElementById("myCanvasCarDataSpeed")
    myCECSpeed = myCESpeed.getContext("2d") # Get Canvas Context for Speed
    myCECSpeed.fillStyle = "#000000"
    myCECSpeed.lineWidth = 1

    # Example Canvas for RPM
    myCERPM = document.getElementById("myCanvasCarDataRPM")
    myCECRPM = myCERPM.getContext("2d") # Get Canvas Context for RPM
    myCECRPM.fillStyle = "#000000"
    myCECRPM.lineWidth = 1

    # Counts the received overall Messages
    myMessageCnt = 0

    # For Specific Message Types
    myMessageCntSpeed = 0
    myMessageCntRPM = 0

    # Here we process the received data
    # Can be optimized by seperating all of this into seperate functions
    ProcessCANMessage = ProcessCANMessage = (data) ->

        # The sent data comes in JSON-Format
        myJSON = JSON.parse(data)

        # List of IDs we are interested in. (just for performance)
        return  if myJSON.ID isnt 256 and myJSON.ID isnt 261 and myJSON.ID isnt 867

        # Debug
        myDebugMsg = data + "\r\n" + "obj: " + myJSON + "\r\n" + "ID: " + myJSON.ID + "\r\n" + "Data: " + myJSON.Data + "\r\n"

        # Count relevant Messages
        myMessageCnt++

        # SPEED => ID 256
        if myJSON.ID is 256

            # In C++ we would use bit masks and bit shifting to parse the 64bit value
            # var mySpeedValue = (myRAWSignal & 0xFFFF00000000) >> 32;

            # But JavaSript can't handle 64Bit (8Byte) integer values!
            # So we use this alternative to cut the String before we calculate the value
            myString = "0x" + myJSON.Data.replace("0x", "").substr(4, 4)

            # finally we get an integer value by using the parseInt-Function
            myRAWSignal = parseInt(myString)

            # now calculate the real speed based on this formula (see CANTrace-Format.pdf)
            myRealSpeed = myRAWSignal * 0.01 + 0 # in Kilometer per Hour
            myRealSpeedM = (myRealSpeed * 0.621371) # in Miles per Hour
            myDebugMsg += "String: " + myString + "\r\n" + "RAW: " + myRAWSignal + "\r\n" + "RealSpeed (kmh): " + myRealSpeed + "\r\n" + "RealSpeed (mph): " + myRealSpeedM + "\r\n"

            # calculate rotation (min, max and target min max values)
            MinimumValue = 0 # Min Value from Trace Data
            MaximumValue = 257 # Max Value from Trace Data
            MinimumTargetValue = 0
            MaximumTargetValue = myCESpeed.height - 30 # -30px because of the text line
            myValue = myRealSpeed
            myValueInRange = (Math.min(Math.max(myValue, MinimumValue), MaximumValue) - MinimumValue)
            myRangeOfValue = (MaximumValue - MinimumValue)
            myResult = (if MaximumValue is MinimumValue then MaximumValue else MinimumTargetValue + (MaximumTargetValue - MinimumTargetValue) * myValueInRange / myRangeOfValue)

            # Do something	here
            if myCECSpeed
                mySpeedY = myCESpeed.height
                mySpeedX = myMessageCntSpeed % myCESpeed.width

                # Clear Two Columns
                myCECSpeed.fillStyle = "#000000"
                myCECSpeed.fillRect mySpeedX - 1, 0, 3, myCESpeed.height

                # Draw the Dot
                myCECSpeed.strokeStyle = "#FFFF00"
                myCECSpeed.strokeRect mySpeedX, mySpeedY - myResult, 1, 1

                # Draw Blue Line
                myCECSpeed.strokeStyle = "#0000FF"
                myCECSpeed.strokeRect mySpeedX + 1, 0, 2, myCESpeed.height

                # Draw Some Text
                myCECSpeed.fillRect 0, 0, myCESpeed.width, 30
                myCECSpeed.fillStyle = "#ff0"
                myCECSpeed.font = "italic 30px sans-serif"
                myCECSpeed.textBaseline = "top"
                myCECSpeed.fillText "Speed: " + myRealSpeed.toFixed(2) + " km/h", 0, 0
                myMessageCntSpeed++

        # RPM (Drehzahl & Pedal)
        if myJSON.ID is 261

            # In Qt/C++ we would use bit masks and bit shifting to parse the 64bit value
            # qreal myRPM = (myCANMessageContainer & 0xFFFF0000) >> 16;

            # But JavaSript can't handle 64Bit (8Byte) integer values!
            # So we use this alternative to cut the String before we calculate the value
            myString = "0x" + myJSON.Data.replace("0x", "").substr(8, 4)

            # finally we get an integer value by using the parseInt-Function
            myRAWSignal = parseInt(myString)

            # Ok use the formula to calculate the real physical value
            myRealRPM = myRAWSignal * 0.25 + 0

            # calculate rotation (min, max and target min max values)
            MinimumValue = 0
            MaximumValue = 8000
            MinimumTargetValue = 0
            MaximumTargetValue = myCERPM.height - 30 # -30px because of the text line
            myValue = myRealRPM
            myValueInRange = (Math.min(Math.max(myValue, MinimumValue), MaximumValue) - MinimumValue)
            myRangeOfValue = (MaximumValue - MinimumValue)
            myResult = (if MaximumValue is MinimumValue then MaximumValue else MinimumTargetValue + (MaximumTargetValue - MinimumTargetValue) * myValueInRange / myRangeOfValue)

            # Do something
            if myCECRPM
                myRPMY = myCERPM.height
                myRPMX = myMessageCntRPM % myCERPM.width

                # Clear Two Columns
                myCECRPM.fillStyle = "#000000"
                myCECRPM.fillRect myRPMX - 1, 0, 3, myCERPM.height

                # Draw the Dot
                myCECRPM.strokeStyle = "#FFFF00"
                myCECRPM.strokeRect myRPMX, myRPMY - myResult, 1, 1

                # Draw Blue Line
                myCECRPM.strokeStyle = "#0000FF"
                myCECRPM.strokeRect myRPMX + 1, 0, 2, myCERPM.height
                myCECRPM.fillRect 0, 0, myCERPM.width, 30
                myCECRPM.fillStyle = "#ff0"
                myCECRPM.font = "italic 30px sans-serif"
                myCECRPM.textBaseline = "top"
                myCECRPM.fillText "RPM: " + myRealRPM.toFixed(2) + " U/Min", 0, 0
                myMessageCntRPM++

        # Blinker
        if myJSON.ID is 867

            # In Qt/C++ we would use bit masks and bit shifting to parse the 64bit value
            #int myBlinkerRechts = (int)((myCANMessageContainer & 0x200) >> 9);
            #int myBlinkerLinks = (int)((myCANMessageContainer & 0x100) >> 8);

            # But JavaSript can't handle 64Bit (8Byte) integer values!
            # So we use this alternative to cut the String before we calculate the value
            myString = "0x" + myJSON.Data.replace("0x", "").substr(5, 1)
            myBlinkerLinks = parseInt(myString) >> 1
            myBlinkerRechts = parseInt(myString) & 0x1
            myBlinkerLinks > 0

            # Do something
            myBlinkerRechts > 0

        # Do something

        # Add more IDs here
        displayDebugMessage myDebugMsg

    window.switchMode = ->
        $("#hmi_normal_mode").toggleClass('hidden')
        $("#hmi_special_mode").toggleClass('hidden')

    # Draw something on a canvas
    window.drawCanvasExample = ->
        console.debug "drawing canvas"
        # Reset the Canvas
        # Setting the width or height of a <canvas> element will erase its contents and
        # reset all the properties of its drawing context to their default values. The values don't have to be changed.
        # Simply re-set it to its current value, as for example:
        window.hmi_normal = new HmiNormal();
        window.hmi_special = new HmiSpecial();
)