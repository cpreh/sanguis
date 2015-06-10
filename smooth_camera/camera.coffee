init = ->
	canvas = document.getElementById 'canvas'
	ctx = canvas.getContext '2d'

	img = document.getElementById 'backgroundImage'

	mouse_pos = (event) ->
		rect = canvas.getBoundingClientRect()
		return {
			x: (event.clientX - rect.left),
			y: (event.clientY - rect.top)
		}

	accel = document.getElementById 'accel'
	console.log accel.value

	pos =
		x: canvas.width / 2
		y: canvas.height / 2

	newpos =
		pos

	redraw = ->
		pos.x += (newpos.x - pos.x) / accel.value
		pos.y += (newpos.y - pos.y) / accel.value

		w = canvas.width
		h = canvas.height
		ctx.drawImage(
			img,
			x,
			y,
			img.width,
			img.height
		) for y in [(pos.y - h)..h] by img.height for x in [(pos.x - w)..w] by img.width

	canvas.addEventListener 'mousemove', (event) ->
		newpos = mouse_pos event
	window.setInterval redraw, 40

window.addEventListener 'load', init
