mandel = (x0, y0) ->
	x0 = x0 * 2.8 - 2.2
	y0 = y0 * 2.4 - 1.2

	x = 0
	y = 0
	
	counter = 0
	
	while ((x*x + y*y) < 4.0 and counter < 500)
		counter++;
		xtmp = x * x - y * y + x0;
		y = 2 * x * y + y0;
		x = xtmp;

	if x*x + y*y < 4.0
		return -1

	return counter % 16

normalize = (x, y, w, h) ->


init = ->
	canvas = document.getElementById 'canvas'
	ctx = canvas.getContext '2d'

	ctx.fillStyle = 'black'
	ctx.fillRect 0, 0, canvas.width, canvas.height

	img = ctx.getImageData 0, 0, canvas.width, canvas.height

	w = canvas.width
	h = canvas.height

	for y in [0..h-1]
		for x in [0..w-1]
			i = (x + y * w) * 4
			col = mandel x / w, y / h
			if col < 0
				img.data[i] = 0
				img.data[i + 1] = 0
				img.data[i + 2] = 0
				img.data[i + 3] = 255
			else
				col = col * 16
				img.data[i] = col
				img.data[i + 1] = 0
				img.data[i + 2] = 255 - col
				img.data[i + 3] = 255
	
	ctx.putImageData img, 0, 0

window.addEventListener 'load', init
