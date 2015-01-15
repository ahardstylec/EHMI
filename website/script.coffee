class CanConnection
    constructor: ->
        # WebSocket Connection URL + Port
        @wsUri = "ws://127.0.0.1:18000"
        @websocket = null
        # Counts the received overall Messages
        @myMessageCnt = 0

        # For Specific Message Types
        @myMessageCntSpeed = 0
        @myMessageCntRPM = 0

    # Init WebSockets
    initWebsocket: ->
        try

        # Browser Check
            if typeof MozWebSocket is "function"
                window.WebSocket = MozWebSocket
            else
                console.info "MozWebSocket is not a function"
            @websocket.close()  if @websocket and @websocket.readyState is 1

            # New WebSocket Object
            @websocket = new window.WebSocket(@wsUri)

            # Event Handler when connection is openend
            @websocket.onopen = (evt) ->
                console.info "CONNECTED"

            # Event Handler when connection is closed
            @websocket.onclose = (evt) ->
                console.info "DISCONNECTED"

            # Event Handler for Errors
            @websocket.onerror = (evt) ->
                console.info "ERROR: " + evt.data


            # Event Handler
            @websocket.onmessage = (evt) =>
                #console.debug "message received"
                myDataType = ""
                if evt.data instanceof ArrayBuffer
                    myDataType = "ArrayBuffer"
                else if evt.data instanceof Blob
                    myDataType = "Blob"
                else
                    myDataType = "text"
                #console.info myDataType + ": " + evt.data

                # Process the received Data
                @processCanMessage evt.data

        catch exception
            console.debug( "ERROR: " + exception)
            console.debug(@websocket)

    # Here we process the received data
    # Can be optimized by seperating all of this into seperate functions
    processCanMessage: (data) ->

        # The sent data comes in JSON-Format
        myJSON = JSON.parse(data)

        # List of IDs we are interested in. (just for performance)
        return  if myJSON.ID isnt 256 and myJSON.ID isnt 261 and myJSON.ID isnt 867

        # Debug
        myDebugMsg = data + "\r\n" + "obj: " + myJSON + "\r\n" + "ID: " + myJSON.ID + "\r\n" + "Data: " + myJSON.Data + "\r\n"

        # Count relevant Messages
        @myMessageCnt++

        # SPEED => ID 256
        hmi_normal.update(myJSON.ID, myJSON.Data)
        hmi_special.update(myJSON.ID, myJSON.Data)

    # Stops/Closes the WebSocket and connection
    stopWebsocket: ->
        @websocket.close()  if @websocket

    # Returns the State of the current WebSocket Object
    checkSocket: ->
        if @websocket?
            stateStr = switch websocket.readyState
                when 0 then "CONNECTING"
                when 1 then "OPEN"
                when 2 then "CLOSING"
                when 3 then "CLOSED"
                else "UNKNOW"
            alert "Websocket state = " + @websocket.readyState + " ( " + stateStr + " )"
        else
            console.info "Websocket is null"


$(->
    window.canConnection = new CanConnection

        # Helper Functions for Numeric Conversion (Degree -> Radian)
    Number::toRadians = ->
        this * (Math.PI / 180)


    # Helper Functions for Numeric Conversion (Radian -> Degree)
    Number::toDegrees = ->
        this * (180 / Math.PI)

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