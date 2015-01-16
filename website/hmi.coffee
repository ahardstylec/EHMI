class window.Hmi
  updateBlinker: (links, rechts)->
    if links then @blinkerLeft.start()# else @blinkerLeft.stop()
    if rechts then @blinkerRight.start()# else @blinkerRight.start()



  update: (id, value)->
    switch(id)
      when "256" #SPEED
        myString = "0x#{value.replace("0x", "").substr(4, 4)}"
        @updateSpeed(parseInt(myString,16) * 0.01 + 0)
        break
      when "261" #RPM
        myStringRpm = "0x#{value.replace("0x", "").substr(8, 4)}"
        myRealRPM= parseInt(myStringRpm, 16) * 0.25 + 0
        @updateRpm(myRealRPM)
        myPedal= "0x"+ value.replace("0x", "").substr(2, 2)
        myPedal = parseInt(myPedal,16) * 0.4 + 0
        @updatePedal(myPedal)
        break
      when "867" #Blinker
        myString = "0x#{value.replace("0x", "").substr(5, 1)}"
        myBlinkerLinks = parseInt(myString) >> 1
        myBlinkerRechts = parseInt(myString) & 0x1
        @updateBlinker(myBlinkerLinks > 0, myBlinkerRechts > 0)
        break
      when "1600"
        myString = "0x#{value.replace("0x", "").substr(8, 2)}"
        myTemp= (parseInt(myString)* 0.75 - 48)
        @updateTemperature(myTemp)
        break
      when "134"
        vorzeichen =parseInt("0x#{value.replace("0x", "").substr(7, 1)}")
        vorzeichen = vorzeichen & 0x4 >> 2
        wert= parseInt("0x#{value.replace("0x", "").substr(8, 4)}")
        wert= (wert & 0x1FFF)* 0.1 + 0
        wert = wert*-1 if vorzeichen == 1
        @updateSteeringWheel(wert)
        break