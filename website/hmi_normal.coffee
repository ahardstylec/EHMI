class window.HmiNormal  extends Hmi
  constructor: ->
    @container= $('#hmi_normal_mode')
    @createImages()
    @

  createImages: ->
    @speedNeedle= new HmiImage(@container, "data/bilder/normal-needle_speed.svg", 70, 40, 397, 57, 70*3, 40*5, 40, 100)
    @rpmNeedle= new HmiImage(@container, "data/bilder/normal-needle_rpm.svg", 40, 40, 110, 110, 150, 150, 30, 70)
    @temperatureBar= new HmiImage(@container, "data/bilder/normal-temperature.svg", 5, 80, 270, 110, 5, 80, 0, 5)
    @blinkerLeft= new Blinker(@container, "data/bilder/normal-blinker_left.svg", 15, 10, 93, 227)
    @blinkerRight= new Blinker(@container, "data/bilder/normal-blinker_right.svg", 15, 10, 583, 239)
    @gasPedal= new HmiImage(@container, "data/bilder/normal-gas_pedal.svg", 30, 30, 255, 134, 60*2, 50*2, 63, 22)
    @steeringWheel= new HmiImage(@container, "data/bilder/normal-steering_wheel.svg", 10, 14, 190, 72, 10*20, 14, 98)
    @
  remove: ->
    @speedNeedle.remove()
    @rpmNeedle.remove()
    @temperatureBar.remove()
    @blinkerLeft.remove()
    @blinkerRight.remove()
    @gasPedal.remove()

  updateSpeed: (value)->
    @speedNeedle.rotate(value*0.036, true);

  updateRpm: (value)->
    @rpmNeedle.rotate(value*0.036, false)

  updatePedal: (value)->
    @gasPedal.rotate((value*0.4), false);

  updateSteeringWheel: (value)->
    console.debug(value)
    ctx = @steeringWheel.ctx
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
    #console.debug(scale)
    lose_px= -((scale*@temperatureBar.img_height )- @temperatureBar.img_height)
    #console.debug(lose_px)
    ctx.translate(0, lose_px)
    ctx.drawImage(@temperatureBar.img, @temperatureBar.img_pos_x, @temperatureBar.img_pos_y, @temperatureBar.img_width, @temperatureBar.img_height)
    ctx.restore();