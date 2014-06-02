mandel = (x0, y0) ->
	x = 0
	y = 0
	
	counter = 0
	
	while ((x*x + y*y) < 4.0 and counter < 500)
		counter++
		xtmp = x * x - y * y + x0
		y = 2 * x * y + y0
		x = xtmp

	if x*x + y*y < 4.0
		return -1

	return counter % 64

xmin = -2.2
xmax = 0.6
ymin = -1.2
ymax = 1.2

canvas = document.getElementById 'canvas'
ctx = canvas.getContext '2d'

img = undefined

draw = ->
	ctx.fillStyle = 'black'
	ctx.fillRect 0, 0, canvas.width, canvas.height

	img = ctx.getImageData 0, 0, canvas.width, canvas.height

	w = canvas.width
	h = canvas.height

	for y in [0..h-1]
		for x in [0..w-1]
			i = (x + y * w) * 4

			col = mandel(
				(x / w) * (xmax - xmin) + xmin,
				(y / h) * (ymax - ymin) + ymin)

			col *= 4

			if col < 0
				img.data[i] = 0
				img.data[i + 1] = 0
				img.data[i + 2] = 0
				img.data[i + 3] = 255
			else
				img.data[i] = col
				img.data[i + 1] = 0
				img.data[i + 2] = col
				img.data[i + 3] = 255
	
	ctx.putImageData img, 0, 0

raw_mouse_pos = (event) ->
	rect = canvas.getBoundingClientRect()
	[
		event.clientX - rect.left,
		event.clientY - rect.top
	]

mouse_pos = (event) ->
	rect = canvas.getBoundingClientRect()
	[
		((event.clientX - rect.left) / canvas.width) * (xmax - xmin) + xmin,
		((event.clientY - rect.top) / canvas.height) * (ymax - ymin) + ymin
	]

[xpos, ypos] = [0, 0]

spanning = false

setMin = (e) ->
	[xmin, ymin] = mouse_pos e
	[xpos, ypos] = raw_mouse_pos e
	spanning = true

setMax = (e) ->
	[xmax, ymax] = mouse_pos e
	spanning = false
	draw()

drawRect = (e) ->
	unless spanning
		return
	ctx.putImageData img, 0, 0
	[x,y] = raw_mouse_pos e
	ctx.fillStyle = 'rgba(255,255,255,0.3)'
	ctx.fillRect xpos, ypos, x - xpos, y - ypos

canvas.addEventListener 'mousedown', setMin
canvas.addEventListener 'mouseup', setMax
canvas.addEventListener 'mousemove', drawRect

window.addEventListener 'load', draw
