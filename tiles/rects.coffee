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
		@neighbor = undefined

	@top = ->
		new AALine(
			@pos,
			new Pos(@pos.x + @dim.w, @pos.y))
	@right = ->
		new AALine(
			new Pos(@pos.x + @dim.w, @pos.y),
			new Pos(@pos.x + @dim.w, @pos.y + @dim.h))

	@bottom = ->
		new AALine(
			new Pos(@pos.x + @dim.w, @pos.y + @dim.h),
			new Pos(@pos.x, @pos.y + @dim.h))
	@left = ->
		new AALine(
			new Pos(@pos.x, @pos.y + @dim.h),
			@pos)

	clip: (other) ->
		if inside(other.pos, @) and inside(other.pos.plus(other.dim), @)
			@dim.w = other.pos.x - @pos.x - 1
			@neighbor = other

		if intersect @top(), other
			oldy = @pos.y
			@pos.y = other.pos.y + other.dim.h + 1
			@dim.h -= @pos.y - oldy
			@neighbor = other

		if intersect @right(), other
			@dim.w = other.pos.x - 1 - @pos.x
			@neighbor = other

		if intersect @bottom(), other
			@dim.h = other.pos.y - 1 - @pos.y
			@neighbor = other

		if intersect @left(), other
			oldx = @pos.x
			@pos.x = other.pos.x + other.dim.w + 1
			@dim.w -= @pos.x - oldx
			@neighbor = other

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

build_graph = (loose) ->
	graph = []
	while loose.length > 0
		next = find_closest graph, loose
		graph.push loose[next]
		delete loose[next]


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

draw_rects = (ctx, tilesize, width, height, rects) ->
	canvas = ctx.canvas
	gridsize = new Dim canvas.width / tilesize, canvas.height / tilesize
	console.log "grid: #{gridsize.w} x #{gridsize.h}"

	ctx.fillStyle = "#aaa"
	ctx.fillRect(
		0
		0
		canvas.width,
		canvas.height)

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


init = ->
	canvas = document.getElementById 'canvas'
	ctx = canvas.getContext '2d'
	rects = generate_rects()
	tilesize = 4
	draw_rects ctx, tilesize, 800, 600, rects

	mouse_pos = (event) ->
		rect = canvas.getBoundingClientRect()
		new Pos(
			(event.clientX - rect.left) // tilesize,
			(event.clientY - rect.top) // tilesize)

	highlight_rect = (event) ->
		console.log mouse_pos event
		draw_rects ctx, tilesize, 800, 600, rects
		for rect in rects
			if inside(mouse_pos(event), rect)
				draw_rect ctx, tilesize, rect, '#f00'
				if rect.neighbor?
					draw_rect ctx, tilesize, rect.neighbor, '#0f0'

	canvas.addEventListener 'click', highlight_rect

window.addEventListener 'load', init
