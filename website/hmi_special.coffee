class window.temperatureSpecial extends HmiImage
  constructor: (container, path, w,h,x,y)->
    super(container, path, w,h,x,y)
    @tmpTwo = new HmiImage container, "data/bilder/special-temperature-2.svg", w,h,x,y
    @tmpThree = new HmiImage container, "data/bilder/special-temperature-1.svg", w,h,x-3,y-5
    @

class window.RpmSpecial extends HmiImage
  constructor: (container, path, w,h,x,y)->
    super container, path, w,h,x,y
    @tmpTwo = new HmiImage container, "data/bilder/special-rpm-2.svg", w, h, x, y
    @tmpThree = new HmiImage container, "data/bilder/special-rpm-3.svg", w, h, x, y
    @tmpFour = new HmiImage container, "data/bilder/special-rpm-4.svg", w, h, x+3, y-2
    @

class window.HmiSpecial
  constructor: ->
    @container= $('#hmi_special_mode')
    @createImages()
  createImages: ->
    @speedNeedle= new HmiImage(@container, "data/bilder/special-needle_speed.svg", 70, 70, 150, 50)
    @temperature= new temperatureSpecial(@container, "data/bilder/special-temperature-3.svg", 50, 130, 243, 88)
    @rpm= new RpmSpecial(@container, "data/bilder/special-rpm-1.svg", 50, 130, 420, 85)
    @blinkerLeft= new HmiImage(@container, "data/bilder/special-blinker_left.svg", 50, 35, 120, 235)
    @blinkerRight= new HmiImage(@container, "data/bilder/special-blinker_right.svg", 30, 40, 583, 239)
    @gasPedal= new HmiImage(@container, "data/bilder/special-gas_pedal.svg", 20, 90, 537, 95)
    @
  remove: ->
    @speedNeedle.remove()
    @rpm.remove()
    @temperature.remove()
    @blinkerLeft.remove()
    @blinkerRight.remove()
    @gasPedal.remove()