class window.HmiNormal  extends Hmi
  constructor: ->
    @container= $('#hmi_normal_mode')
    @createImages()
    @

  createImages: ->
    @speedNeedle= new HmiImage(@container, "data/bilder/normal-needle_speed.svg", 70, 40, 397, 57, 70*3, 40*5, 40, 100)
    @rpmNeedle= new HmiImage(@container, "data/bilder/normal-needle_rpm.svg", 40, 40, 140, 180, 40*4, 40*4)
    @temperatureBar= new HmiImage(@container, "data/bilder/normal-temperature.svg", 5, 80, 270, 110, 5, 80)
    @blinkerLeft= new Blinker(@container, "data/bilder/normal-blinker_left.svg", 15, 10, 93, 227)
    @blinkerRight= new Blinker(@container, "data/bilder/normal-blinker_right.svg", 15, 10, 583, 239)
    @gasPedal= new HmiImage(@container, "data/bilder/normal-gas_pedal.svg", 30,30, 315, 154,30*2, 30)
    @steeringWheel= new HmiImage(@container, "data/bilder/normal-steering_wheel.svg", 10, 14, 190, 72, 10*20, 14, 98)
    @
  remove: ->
    @speedNeedle.remove()
    @rpmNeedle.remove()
    @temperatureBar.remove()
    @blinkerLeft.remove()
    @blinkerRight.remove()
    @gasPedal.remove()

  updateRpm: (value)->
    @rpmNeedle.rotate(value*1.8)

  updateSpeed: (value)->
    @speedNeedle.rotate(value*0.036)

  updatePedal: (value)->
    ctx = @gasPedal.$canvas[0].getContext("2d")
    ctx.clearRect(0,0, @gasPedal.$canvas[0].width, @gasPedal.$canvas[0].height);
    ctx.save();
    ctx.rotate((value*0.4).toRadians())
    ctx.translate(@gasPedal.img_width/2, 0)
    ctx.drawImage(@gasPedal.img, 0, 0, @gasPedal.img_width, @gasPedal.img_height)
    ctx.restore();

  updateSteeringWheel: (value)->
    ctx = @steeringWheel.$canvas[0].getContext("2d")
    ctx.clearRect(0,0, @steeringWheel.$canvas[0].width, @steeringWheel.$canvas[0].height);
    ctx.save();
    ctx.translate(value/70, 0)
    ctx.drawImage(@steeringWheel.img, @steeringWheel.img_pos_x, @steeringWheel.img_pos_y, @steeringWheel.img_width, @steeringWheel.img_height)
    ctx.restore();

  updateTemperature: (value)->
    scale = value/120
    ctx = @temperatureBar.$canvas[0].getContext("2d")
    ctx.clearRect(0,0, @temperatureBar.$canvas[0].width, @temperatureBar.$canvas[0].height);
    ctx.save();
    ctx.scale(1, scale)
    lose_px= Math.abs((scale*@temperatureBar.height )- @temperatureBar.height)
#    ctx.transform(0, lose_px)
    ctx.drawImage(@temperatureBar.img, @temperatureBar.img_pos_x, @temperatureBar.img_pos_y, @temperatureBar.img_width, @temperatureBar.img_height)
    ctx.restore();

  update: (id, value)->
    switch(id)
      when "261" #SPEED
        myString = "0x#{value.replace("0x", "").substr(4, 4)}"
        @updateSpeed(parseInt(myString) * 0.01 + 0)
        break
      when "256" #RPM
        myStringRpm = "0x#{value.replace("0x", "").substring(8, 4)}"
        myRealRPM= parseInt(myStringRpm) * 0.25 + 0
        myPedal= "0x#{value.replace("0x", "").substring(10, 2)}"
        myPedal = parseInt(myPedal) * 0.4 + 0;
        @updatePedal(myPedal)
        @updateRpm(parseInt(myRealRPM) * 0.25 + 0)
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
        vorzeichen =parseInt("0x#{value.replace("0x", "").substr(6, 1)}")
        wert= parseInt("0x#{value.replace("0x", "").substring(8, 4)}")* 0.1 + 0
        wert = wert*-1 if vorzeichen == 1
        @updateSteeringWheel(wert)
        break