class window.HmiNormal
  constructor: ->
    @container= $('#hmi_normal_mode')
    @createImages()
    @
  createImages: ->
    @speedNeedle= new HmiImage(@container, "data/bilder/normal-needle_speedn.svg", 70, 40, 440 , 155)
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