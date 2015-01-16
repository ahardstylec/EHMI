class window.temperatureSpecial extends HmiImage
  constructor: (container, path, w,h,x,y)->
    super(container, path, w,h,x,y)
    @tmpTwo = new HmiImage container, "data/bilder/special-temperature-2.svg", w,h,x,y
    @tmpThree = new HmiImage container, "data/bilder/special-temperature-1.svg", w,h,x-3,y-5
    @$canvas.css('opacity', 0)
    @tmpTwo.$canvas.css('opacity', 0)
    @tmpThree.$canvas.css('opacity', 0)
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
    @$canvas.css('opacity', 0)
    @tmpTwo.$canvas.css('opacity', 0)
    @tmpThree.$canvas.css('opacity', 0)
    @tmpFour.$canvas.css('opacity', 0)
    @
  update: (value)->
    @tmpFour.$canvas.css('opacity', (value-4000)/1000)
    @tmpThree.$canvas.css('opacity', (value-2500)/1500)
    @tmpTwo.$canvas.css('opacity', (value-1500)/1000)
    @$canvas.css('opacity', value/1500)


class window.HmiSpecial extends Hmi
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
    @speedNeedle.rotate(value/180);

  updatePedal: (value)->

  updateSteeringWheel: (value)->
    ctx = @steeringWheel.$canvas[0].getContext("2d")
    ctx.clearRect(0,0, @steeringWheel.$canvas[0].width, @steeringWheel.$canvas[0].height);
    ctx.save();
    ctx.translate(value/70, 0)
    ctx.drawImage(@steeringWheel.img, @steeringWheel.img_pos_x, @steeringWheel.img_pos_y, @steeringWheel.img_width, @steeringWheel.img_height)
    ctx.restore();

  update: (id, value)->
    switch(id)
      when "261" #SPEED
        myString = "0x#{value.replace("0x", "").substr(4, 4)}"
        return
        @updateSpeed(parseInt(myString) * 0.01 + 0)
        break
      when "256" #RPM
        myStringRpm = "0x#{value.replace("0x", "").substring(8, 4)}"
        myRealRPM= parseInt(myStringRpm) * 0.25 + 0
        @rpm.update(myRealRPM)

        myPedal= "0x#{value.replace("0x", "").substring(10, 2)}"
        myPedal = parseInt(myPedal) * 0.4 + 0;
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
        @temperature.update(myTemp)
        break
      when "134"
        vorzeichen =parseInt("0x#{value.replace("0x", "").substr(6, 1)}")
        wert= parseInt("0x#{value.replace("0x", "").substring(8, 4)}")* 0.1 + 0
        wert = wert*-1 if vorzeichen == 1
        @updateSteeringWheel(wert)
        break