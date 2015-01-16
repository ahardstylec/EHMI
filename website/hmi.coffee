class window.Hmi
  updateBlinker: (links, rechts)->
    if links then @blinkerLeft.start()# else @blinkerLeft.stop()
    if rechts then @blinkerRight.start()# else @blinkerRight.start()

