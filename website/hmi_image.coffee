class window.HmiImage
  constructor: (container, path, img_width, img_height, context_x, context_y, context_width=img_width, context_height=img_height, img_pos_x=0, img_pos_y=0) ->
    @img_width=img_width
    @img_height=img_height
    @context_width= context_width
    @context_height= context_height
    @img_pos_x=img_pos_x
    @img_pos_y=img_pos_y
    @name= path.split('/')[path.split('/').length-1]
    @$canvas = $("<canvas>").addClass 'hmi_image'
    @$canvas.attr 'id', @name
    @$canvas.attr 'width', @context_width
    @$canvas.attr 'height', @context_height
    @$canvas.css left: context_x, top: context_y
    @$canvas.appendTo container
    ctx = @$canvas[0].getContext "2d"
    @img = new Image()
    @img.src= path
    $(@img).on 'load', =>
      ctx.drawImage @img, @img_pos_x, @img_pos_y, @img_width, @img_height
    @

  remove: ->
    @$canvas.remove()

  rotate: (deg)->
    ctx = @$canvas[0].getContext("2d")
    ctx.clearRect(0,0, @$canvas[0].width, @$canvas[0].height);
    ctx.save();
    ctx.translate(@canvas_width, 0)
    ctx.rotate(deg.toRadians())
    ctx.translate(-@canvas_width, 0)
    ctx.drawImage(@img, @img_pos_x, @img_pos_y, @img_width, @img_height)
    ctx.restore();
