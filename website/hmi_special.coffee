class window.temperatureSpecial extends HmiImage
  constructor: (container, path, w,h,x,y)->
    super(container, path, w,h,x,y)
    @tmpTwo = new HmiImage container, "data/bilder/special-temperature-2.svg", w,h,x,y
    @tmpThree = new HmiImage container, "data/bilder/special-temperature-1.svg", w,h,x-3,y-5
    @
  update: (value)->
    @tmpThree.$canvas.css('opacity', (value-90)/30)
    @tmpTwo.$canvas.css('opacity', (value-70)/20)
    @$canvas.css('opacity',(value-50)/20)


class window.RpmSpecial extends HmiImage
  constructor: (container, path, w,h,x,y)->
    super container, path, w,h,x,y
    @tmpTwo = new HmiImage container, "data/bilder/special-rpm-2.svg", w, h, x, y
    @tmpThree = new HmiImage container, "data/bilder/special-rpm-3.svg", w, h, x, y
    @tmpFour = new HmiImage container, "data/bilder/special-rpm-4.svg", w, h, x+3, y-2
    @
  update: (value)->
    @tmpFour.$canvas.css('opacity', (value-4000)/1000)
    @tmpThree.$canvas.css('opacity', (value-2500)/1500)
    @tmpTwo.$canvas.css('opacity', (value-1500)/1000)
    @$canvas.css('opacity', value/1500)


class window.HmiSpecial
  constructor: ->
    @container= $('#hmi_special_mode')
    @createImages()
  createImages: ->
    @speedNeedle= new HmiImage(@container, "data/bilder/special-speed.svg", 50, 50, 310, 150)
    @temperature= new temperatureSpecial(@container, "data/bilder/special-temperature-3.svg", 50, 130, 243, 88)
    @rpm= new RpmSpecial(@container, "data/bilder/special-rpm-1.svg", 50, 130, 420, 85)
    @blinkerLeft= new Blinker(@container, "data/bilder/special-blinker_left.svg", 47, 25, 153, 220)
    @blinkerRight= new Blinker(@container, "data/bilder/special-blinker_right.svg", 55, 25, 520, 224)
    @gasPedal= new HmiImage(@container, "data/bilder/special-gas_pedal.svg", 20, 90, 537, 95)
    @steeringWheel= new HmiImage(@container, "data/bilder/special-steering_wheel.svg", 3, 13, 349, 52)
    @
  remove: ->
    @speedNeedle.remove()
    @rpm.remove()
    @temperature.remove()
    @blinkerLeft.remove()
    @blinkerRight.remove()
    @gasPedal.remove()

  updateSpeed: (value)->
    @speedNeedle.$canvas.rotate(value*1.8);

  updateBlinker: (links, rechts)->
    if links
      @BlinkerLeft.start()
    else
      @BlinkerLeft.stop()
    if rechts
      @blinkerRight.start()
    else
      @blinkerRight.stop()

  update: (id, value)->
    switch(id)
      when 261 #SPEED
        myString = "0x#{value.replace("0x", "").substr(4, 4)}"
        @updateSpeed(parseInt(myString) * 0.01 + 0)
        break
      when 256 #RPM
        myString = "0x#{value.replace("0x", "").substr(8, 4)}"
        @rpm.update(parseInt(myString) * 0.25 + 0)
        break
      when 867 #Blinker
        myString = "0x#{value.replace("0x", "").substr(5, 1)}"
        myBlinkerLinks = parseInt(myString) >> 1
        myBlinkerRechts = parseInt(myString) & 0x1
        updateBlinker(myBlinkerLinks > 0, myBlinkerRechts > 0)
        break