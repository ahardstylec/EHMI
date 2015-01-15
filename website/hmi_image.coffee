class window.HmiImage
  constructor: (container, path, width, height, x, y) ->
    @name= path.split('/')[path.split('/').length-1]
    @$canvas = $("<canvas>").addClass 'hmi_image'
    @$canvas.attr 'id', @name
    @$canvas.attr 'width', width
    @$canvas.attr 'height', height
    @$canvas.css left: x, top: y, visibility: 'visible'
    @$canvas.appendTo container
    ctx = @$canvas[0].getContext "2d"
    @img = new Image()
    @img.src= path
    $(@img).on 'load', =>
      ctx.drawImage @img, 0, 0, width, height
    @
  remove: ->
    @$canvas.remove()