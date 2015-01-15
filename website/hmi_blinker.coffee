class window.Blinker extends HmiImage
  constructor: (container, path, width, height, x, y) ->
    super(container, path, width, height, x, y)
    @
  remove: ->
    @$canvas.remove()

  start: ()->
    removeTimeout(@timeout) if @timeout
    @interval= setInterval (->
      @$canvas.toggleClass('hidden')
      ), 500
    @timeout = setTimeout (=>
      @stop()
    ), 1500
  stop: ()->
    removeInterval(@interval);