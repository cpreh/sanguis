class Rand
  # if created without a seed, uses current time as seed
  constructor: (@seed) ->
    # Knuth and Lewis' improvements to Park and Miller's LCPRNG
    @multiplier = 1664525
    @modulo = 4294967296 # 2**32-1;
    @offset = 1013904223
    unless @seed? && 0 <= seed < @modulo
      @seed = (new Date().valueOf() * new Date().getMilliseconds()) % @modulo

  # sets new seed value
  seed: (seed) ->
    @seed = seed

  # return a random integer 0 <= n < @modulo
  randn: ->
    # new_seed = (a * seed + c) % m
    @seed = (@multiplier*@seed + @offset) % @modulo

 # return a random float 0 <= f < 1.0
  randf: ->
    this.randn() / @modulo

  # return a random int 0 <= f < n
  rand: (n) ->
    Math.floor(this.randf() * n)

  # return a random int min <= f < max
  rand2: (min, max) ->
    min + this.rand(max-min)

class Pos
	constructor: (@x, @y) ->
	plus: (dim) ->
		new Pos(@x + dim.w, @y + dim.h)
	minus: (dim) ->
		new Pos(@x - dim.w, @y - dim.h)

class Dim
	constructor: (@w, @h) ->

class AALine
	constructor: (@p1, @p2) ->
		if @p1.x == @p2.x
			if @p2.y < @p1.y
				[@p1, @p2] = [@p2, @p1]
				return
		if @p1.y == @p2.y
			if @p2.x < @p1.x
				[@p1, @p2] = [@p2, @p1]
				return

class Rect
	constructor: (@pos, @dim) ->
		@adj = []

	top: ->
		new AALine(
			@pos,
			new Pos(@pos.x + @dim.w, @pos.y))
	right: ->
		new AALine(
			new Pos(@pos.x + @dim.w, @pos.y),
			new Pos(@pos.x + @dim.w, @pos.y + @dim.h))

	bottom: ->
		new AALine(
			@pos.plus(@dim),
			new Pos(@pos.x, @pos.y + @dim.h))
	left: ->
		new AALine(
			new Pos(@pos.x, @pos.y + @dim.h),
			@pos)

	clip: (other) ->
		if inside(other.pos, @) and inside(other.pos.plus(other.dim), @)
			@dim.w = other.pos.x - @pos.x - 1
			@adj.push other

		if intersect @top(), other
			oldy = @pos.y
			@pos.y = other.pos.y + other.dim.h + 1
			@dim.h -= @pos.y - oldy
			@adj.push other

		if intersect @right(), other
			@dim.w = other.pos.x - 1 - @pos.x
			@adj.push other

		if intersect @bottom(), other
			@dim.h = other.pos.y - 1 - @pos.y
			@adj.push other

		if intersect @left(), other
			oldx = @pos.x
			@pos.x = other.pos.x + other.dim.w + 1
			@dim.w -= @pos.x - oldx
			@adj.push other

inside = (point, rect) ->
	return point.x >= rect.pos.x and
		point.x <= rect.pos.x + rect.dim.w and
		point.y >= rect.pos.y and
		point.y <= rect.pos.y + rect.dim.h

intersect = (line, rect) ->
	return line.p2.x >= rect.pos.x and
		line.p1.x <= rect.pos.x + rect.dim.w and
		line.p1.y <= rect.pos.y + rect.dim.h and
		line.p2.y >= rect.pos.y

seed = new Rand().randn()
console.log "seed: #{seed}"
rng = new Rand(seed)

randn = -> rng.randn()

random_int = (a, b) ->
	a + randn() % (b - a + 1)

shuffle = (a) ->
	# From the end of the list to the beginning, pick element `i`.
	for i in [a.length-1..1]
		# Choose random element `j` to the front of `i` to swap with.
		j = random_int(0,i)
		# Swap `j` with `i`, using destructured assignment
		[a[i], a[j]] = [a[j], a[i]]
		# Return the shuffled array.
	a

generate_rects = (ctx, width, height) ->
	rects = []

	for i in [1..100]
		x = random_int 0, 100
		y = random_int 0, 75
		w = Math.min(random_int(10, 40), 100 - x)
		h = Math.min(random_int(10, 40), 75 - y)

		rect = new Rect(
			new Pos(x, y),
			new Dim(w, h))

		wellformed = true

		for other in rects
			rect.clip other
			wellformed = rect.dim.w > 2 and rect.dim.h > 2
			unless wellformed
				break

		if wellformed
			rects.push rect

	rects

find_closest = (graph, nodes) ->
	ret = undefined
	min_length = Infinity
	for n1 in graph
		for n2 in nodes
			if distance(n1, n2) < min_length
				ret = n2
	ret

build_graph = (rects) ->
	graph = []
	for rect in rects
		graph.push rect
		closest = find_closest(rect, rects)

draw_rect = (ctx, tilesize, rect, color) ->
	ctx.fillStyle = color ? "#883"
	ctx.fillRect(
		tilesize * rect.pos.x,
		tilesize * rect.pos.y,
		tilesize * rect.dim.w,
		tilesize * rect.dim.h)

	if rect.dim.w == 1 or rect.dim.h == 1
		return

	ctx.fillStyle = "#000"
	ctx.fillRect(
		tilesize * (rect.pos.x + 1),
		tilesize * (rect.pos.y + 1),
		tilesize * (rect.dim.w - 2),
		tilesize * (rect.dim.h - 2))


clear = (ctx, color) ->
	ctx.fillStyle = color ? "#aaa"
	ctx.fillRect(
		0,
		0,
		canvas.width,
		canvas.height)


draw_rects = (ctx, tilesize, width, height, rects) ->
	canvas = ctx.canvas
	gridsize = new Dim canvas.width / tilesize, canvas.height / tilesize
	console.log "grid: #{gridsize.w} x #{gridsize.h}"

	clear ctx

	set_tile = (x, y, color) ->
		ctx.fillStyle = color ? "#883"
		ctx.fillRect(
			tilesize * x,
			tilesize * y,
			tilesize,
			tilesize)


	random_color = ->
		r = [random_int(0, 255), 255, 0]
		shuffle r
		return "rgb(#{r[0]},#{r[1]},#{r[2]})"

	for rect in rects
		draw_rect ctx, tilesize, rect, '#883'

###
# draw a corridor from point 'p1' to point 'p2'
# with at most one bend in the middle, open at each end to connect rooms
# 'thickness' wide total, leaving
# 'inner_thickness' space between sides,
# 'flipped' determines in which direction the corridor bends,
# following the x or y axis first, respectively
###
draw_corridor = (ctx, tilesize, p1, p2, thickness, inner_thickness, flipped) ->
	flipped = flipped ? false

	start = p1
	mid = undefined
	if flipped
		mid = new Pos(p1.x, p2.y)
	else
		mid = new Pos(p2.x, p1.y)
	end = p2

	###
	# Helper function to fill a rectangle spanned by two points
	# d is the diameter. If the diameter is even, this results
	# in an asymmetric shape.
	###
	fill_rect = (a, b, d, color) ->
		[x1, x2] = if a.x < b.x then [a.x, b.x] else [b.x, a.x]
		[y1, y2] = if a.y < b.y then [a.y, b.y] else [b.y, a.y]
		w = x2 - x1
		h = y2 - y1
		ctx.fillStyle = color
		ctx.fillRect(
			tilesize * (x1 - d//2),
			tilesize * (y1 - d//2),
			tilesize * (w + d),
			tilesize * (h + d))

	# set a single tile
	set_tile = (x, y, color) ->
		fill_rect(new Pos(x, y), new Pos(x, y), 1, color ? '#0ff')

	sign = (x) ->
		if x < 0 then -1 else if close(x, 0) then 0 else 1

	# floating point comparison using epsilon
	close = (x, y) ->
		Math.abs(x - y) < 0.001

	# determine orientation of starting tile
	if close(mid.y, start.y)
		dir1 = new Dim(
			(thickness // 2) * sign(mid.x - start.x),
			0)
	else
		dir1 = new Dim(
			0,
			(thickness // 2) * sign(mid.y - start.y))
	
	# determine orientation of end tile
	if close(mid.y, end.y)
		dir2 = new Dim(
			(thickness // 2) * sign(mid.x - end.x),
			0)
	else
		dir2 = new Dim(
			0,
			(thickness // 2) * sign(mid.y - end.y))

	###
	# horizontal or vertical paths without mid have only one rect
	# all other paths consist of two rects
	# cut off one tile on the side leading into and out of the corridor,
	# respectively
	###
	if close(end.x, start.x) or close(end.y, start.y)
		if close(end.x, start.x)
			dir = new Dim(0,(thickness // 2) * sign(end.y - start.y))
		else
			dir = new Dim((thickness // 2) * sign(end.x - start.x),0)
		fill_rect start.plus(dir), end.minus(dir), thickness, '#f00'
	else
		fill_rect start.plus(dir1), mid, thickness, '#080'
		fill_rect mid, end.plus(dir2), thickness, '#808'

	# fill the inner area
	fill_rect start, mid, inner_thickness, '#ff0'
	fill_rect mid, end, inner_thickness, '#ff0'

	# draw the start and end points
	set_tile p1.x, p1.y, '#0f0'
	set_tile p2.x, p2.y, '#f0f'


init = ->
	canvas = document.getElementById 'canvas'
	ctx = canvas.getContext '2d'
	rects = generate_rects()
	#rects = build_graph(rects)

	outer_slider = document.getElementById 'outer'
	outer_label = document.getElementById 'outer_label'
	inner_slider = document.getElementById 'inner'
	inner_label = document.getElementById 'inner_label'
	tilesize_slider = document.getElementById 'tilesize'
	tilesize_label = document.getElementById 'tilesize_label'

	tilesize = ->
		tilesize_slider.value

	mouse_pos = (event) ->
		rect = canvas.getBoundingClientRect()
		new Pos(
			(event.clientX - rect.left) // tilesize(),
			(event.clientY - rect.top) // tilesize())

	redraw = (event) ->
		clear ctx
		draw_corridor(
			ctx,
			tilesize(),
			new Pos(5, 5),
			new Pos(15, 2),
			Math.floor(outer_slider.value),
			Math.floor(inner_slider.value),
			false)
		draw_corridor(
			ctx,
			tilesize(),
			new Pos(25, 25),
			mouse_pos(event),
			Math.floor(outer_slider.value),
			Math.floor(inner_slider.value),
			event.shiftKey)

	highlight_rect = (event) ->
		draw_rects ctx, tilesize(), 800, 600, rects
		for rect in rects
			if inside(mouse_pos(event), rect)
				draw_rect ctx, tilesize(), rect, '#f00'
				for neighbor in rect.adj
					draw_rect ctx, tilesize(), rect.neighbor, '#0f0'

	canvas.addEventListener 'mousemove', redraw
	canvas.addEventListener 'keydown', redraw

	outer_slider.addEventListener 'input', (event) ->
		outer_label.innerHTML = outer_slider.value
		redraw event
	inner_slider.addEventListener 'input', (event) ->
		inner_label.innerHTML = inner_slider.value
		redraw event
	tilesize_slider.addEventListener 'input', (event) ->
		tilesize_label.innerHTML = tilesize_slider.value
		redraw event

window.addEventListener 'load', init
