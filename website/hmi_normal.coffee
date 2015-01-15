class window.HmiNormal
  constructor: ->
    @container= $('#hmi_normal_mode')
    @createImages()
    @
  createImages: ->
    @speedNeedle= new HmiImage(@container, "data/bilder/normal-needle_speed.svg", 70, 40, 437 , 157)
    @rpmNeedle= new HmiImage(@container, "data/bilder/normal-needle_rpm.svg", 40, 40, 140, 180)
    @temperatureBar= new HmiImage(@container, "data/bilder/normal-temperature.svg", 5, 80, 270, 110)
    @blinkerLeft= new HmiImage(@container, "data/bilder/normal-blinker_left.svg", 15, 10, 93, 227)
    @blinkerRight= new HmiImage(@container, "data/bilder/normal-blinker_right.svg", 15, 10, 583, 239)
    @gasPedal= new HmiImage(@container, "data/bilder/normal-gas_pedal.svg", 30,30, 315, 154)
    @steeringWheel= new HmiImage(@container, "data/bilder/normal-steering_wheel.svg", 10, 14, 288, 72)
    @
  remove: ->
    @speedNeedle.remove()
    @rpmNeedle.remove()
    @temperatureBar.remove()
    @blinkerLeft.remove()
    @blinkerRight.remove()
    @gasPedal.remove()

  updateRpm: (value)->
    @rpmNeedle.$canvas.rotate(value*0.036);
  updateSpeed: (value)->
    @speedNeedle.$canvas.rotate(value*1.8);
  updateBlinker: (left, right)->

  update: (id, value)->
    switch(id)
      when 261 #SPEED
        myString = "0x#{value.replace("0x", "").substr(4, 4)}"
        @updateSpeed(parseInt(myString) * 0.01 + 0)
        break
      when 256 #RPM
        myString = "0x#{value.replace("0x", "").substr(8, 4)}"
        @updateRpm(parseInt(myString) * 0.25 + 0)
        break
      when 867 #Blinker
        myString = "0x#{value.replace("0x", "").substr(5, 1)}"
        myBlinkerLinks = parseInt(myString) >> 1
        myBlinkerRechts = parseInt(myString) & 0x1
        updateBlinker(myBlinkerLinks > 0, myBlinkerRechts > 0)
        break