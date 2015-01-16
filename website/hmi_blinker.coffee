class window.Blinker extends HmiImage
  constructor: (container, path, width, height, x, y) ->
    super(container, path, width, height, x, y)
    @$canvas.addClass('hidden')
    @
  remove: ->
    @$canvas.remove()

  start: ()->
    clearTimeout(@timeout) if @timeout
    if typeof @interval is 'undefined'
      @interval= setInterval (=>
        @$canvas.toggleClass('hidden')
        ), 500
    @timeout = setTimeout (=>
      @stop()
    ), 1500
  stop: ()->
    clearInterval(@interval)
    @interval=undefined
    @$canvas.addClass('hidden')