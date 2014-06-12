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

class Edge
	@none: -1
	@right: 0
	@top: 1
	@left: 2
	@bottom: 3

class Rect
	neighbor: undefined

	constructor: (@pos, @dim) ->

	top: ->
		new AALine(
			@pos,
			new Pos(@pos.x + @dim.w, @pos.y))
	right: ->
		new AALine(
			new Pos(@pos.x + @dim.w, @pos.y),
			@pos.plus @dim)

	bottom: ->
		new AALine(
			new Pos(@pos.x, @pos.y + @dim.h),
			@pos.plus @dim)
	left: ->
		new AALine(
			new Pos(@pos.x, @pos.y + @dim.h),
			@pos)

	clip: (other) ->
		last = undefined
		#before = new Dim(@dim.w, @dim.h)
		if inside(other.pos, @) and inside(other.pos.plus(other.dim), @)
			@dim.w = other.pos.x - 1 - @pos.x
			last = Edge.right

		if intersect @top(), other
			oldy = @pos.y
			@pos.y = other.pos.y + other.dim.h + 1
			@dim.h -= @pos.y - oldy
			last = Edge.top

		if intersect @right(), other
			@dim.w = other.pos.x - 1 - @pos.x
			last = Edge.right

		if intersect @bottom(), other
			@dim.h = other.pos.y - 1 - @pos.y
			last = Edge.bottom

		if intersect @left(), other
			oldx = @pos.x
			@pos.x = other.pos.x + other.dim.w + 1
			@dim.w -= @pos.x - oldx
			last = Edge.left

		# modified?
		#not (before.w == @dim.w and before.h == @dim.h)
		last

###
# a corridor from point 'p1' to point 'p2'
# with at most one bend in the middle, open at each end to connect rooms
# 'thickness' wide total, leaving
# 'inner_thickness' space between sides,
# following the x or y axis first, respectively
###
class Corridor
	_bounds: undefined

	constructor: (@ctx, @tilesize, @p1, @p2, @thickness, @inner_thickness) ->
		@_bounds =
			new Rect(
				new Pos(
					@p1.x - @thickness // 2,
					@p1.y - @thickness // 2
				),
				new Dim(
					@p2.x - @p1.x + @thickness
					@p2.y - @p1.y + @thickness
				)
			)

	###
	# Helper function to fill a rectangle spanned by two points
	# d is the diameter. If the diameter is even, this results
	# in an asymmetric shape.
	###
	_fill_rect: (a, b, d, color) ->
		[x1, x2] = if a.x < b.x then [a.x, b.x] else [b.x, a.x]
		[y1, y2] = if a.y < b.y then [a.y, b.y] else [b.y, a.y]
		w = x2 - x1
		h = y2 - y1
		@ctx.fillStyle = color
		@ctx.fillRect(
			@tilesize * (x1 - d//2),
			@tilesize * (y1 - d//2),
			@tilesize * (w + d),
			@tilesize * (h + d))

	# set a single tile
	_set_tile: (x, y, color) ->
		@_fill_rect(new Pos(x, y), new Pos(x, y), 1, color ? '#0ff')

	bounds: ->
		new Rect(
			new Pos(
				@p1.x - @thickness // 2,
				@p1.y - @thickness // 2
			),
			new Dim(
				@p2.x - @p1.x + @thickness
				@p2.y - @p1.y + @thickness
			)
		)

	draw: (flipped) ->
		console.log 'draw()'
		flipped = flipped ? false

		start = @p1
		mid = undefined
		if flipped
			mid = new Pos(@p1.x, @p2.y)
		else
			mid = new Pos(@p2.x, @p1.y)
		end = @p2

		sign = (x) ->
			if x < 0 then -1 else if close(x, 0) then 0 else 1

		# floating point comparison using epsilon
		close = (x, y) ->
			Math.abs(x - y) < 0.001

		# determine orientation of starting tile
		if close(mid.y, start.y)
			dir1 = new Dim(
				(@thickness // 2) * sign(mid.x - start.x),
				0)
		else
			dir1 = new Dim(
				0,
				(@thickness // 2) * sign(mid.y - start.y))
		
		# determine orientation of end tile
		if close(mid.y, end.y)
			dir2 = new Dim(
				(@thickness // 2) * sign(mid.x - end.x),
				0)
		else
			dir2 = new Dim(
				0,
				(@thickness // 2) * sign(mid.y - end.y))

		###
		# horizontal or vertical paths without mid have only one rect
		# all other paths consist of two rects
		# cut off one tile on the side leading into and out of the corridor,
		# respectively
		###
		if close(end.x, start.x) or close(end.y, start.y)
			if close(end.x, start.x)
				dir = new Dim(0,(@thickness // 2) * sign(end.y - start.y))
			else
				dir = new Dim((@thickness // 2) * sign(end.x - start.x),0)
			@_fill_rect start.plus(dir), end.minus(dir), @thickness, '#883'
		else
			@_fill_rect start.plus(dir1), mid, @thickness, '#883'
			@_fill_rect mid, end.plus(dir2), @thickness, '#883'

		# fill the inner area
		@_fill_rect start.plus(dir1), mid, @inner_thickness, '#000'
		@_fill_rect mid, end.plus(dir2), @inner_thickness, '#000'

		# draw the start and end points
		###
		@_set_tile mid.x, mid.y, '#00f'
		###
		@_set_tile @p1.x, @p1.y, '#000'
		@_set_tile @p2.x, @p2.y, '#000'

inside = (point, rect) ->
	return point.x >= rect.pos.x and
		point.x <= rect.pos.x + rect.dim.w and
		point.y >= rect.pos.y and
		point.y <= rect.pos.y + rect.dim.h

intersect = (line, rect) ->
	return line.p2.x >= rect.pos.x and
		line.p2.y >= rect.pos.y and
		line.p1.x <= rect.pos.x + rect.dim.w and
		line.p1.y <= rect.pos.y + rect.dim.h

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
	random_rect = (i) ->
		x = random_int 0, 100 - 3
		y = random_int 0, 75 - 3
		w = Math.min(random_int(5, 15+i), 100 - x)
		h = Math.min(random_int(5, 15+i), 75 - y)

		new Rect(
			new Pos(x, y),
			new Dim(w, h))

	rects = [random_rect(1)]
	corr = []

	for i in [1..100]
		rect = random_rect(i)

		wellformed = true

		neighbor = undefined
		edge = undefined

		for other in rects
			e = rect.clip other
			if e?
				neighbor = other
				edge = e
			wellformed = rect.dim.w > 2 and rect.dim.h > 2
			unless wellformed
				break


		if wellformed and neighbor
			rect.neighbor = neighbor
			x1 = undefined
			y1 = undefined
			x2 = undefined
			y2 = undefined
			if edge in [Edge.top, Edge.bottom]
				xmin = 1 + Math.max rect.pos.x, neighbor.pos.x
				xmax = -2 + Math.min rect.pos.x + rect.dim.w, neighbor.pos.x + neighbor.dim.w
				x2 = x1 = random_int xmin, xmax
				if edge == Edge.top
					y1 = rect.pos.y - 2
					y2 = rect.pos.y
				if edge == Edge.bottom
					y1 = rect.pos.y + rect.dim.h - 1
					y2 = rect.pos.y + rect.dim.h + 1
			if edge in [Edge.left, Edge.right]
				ymin = 1 + Math.max rect.pos.y, neighbor.pos.y
				ymax = -2 + Math.min rect.pos.y + rect.dim.h, neighbor.pos.y + neighbor.dim.h
				y2 = y1 = random_int ymin, ymax
				if edge == Edge.left
					x1 = rect.pos.x - 2
					x2 = rect.pos.x
				if edge == Edge.right
					x1 = rect.pos.x + rect.dim.w - 1
					x2 = rect.pos.x + rect.dim.w + 1

			corr.push new Corridor(
				ctx, 8, new Pos(x1, y1), new Pos(x2, y2), 3, 1)

			rects.push rect

	[rects, corr]

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

	draw_rect ctx, tilesize, rects[0], '#f0f'

	for rect in rects[1..]
		draw_rect ctx, tilesize, rect, '#883'

seed = new Rand().randn()
rng = new Rand(seed)
randn = -> rng.randn()

change_seed = (s) ->
	seed = s ? new Rand().randn()
	console.log "seed: #{seed}"
	rng = new Rand(seed)

	randn = -> rng.randn()
	regenerate()

init = ->
	seed_input = document.getElementById 'seed'
	seed_input.value = seed
	seed_input.addEventListener 'change', -> change_seed seed_input.value
	regenerate()

regenerate = ->
	canvas = document.getElementById 'canvas'
	ctx = canvas.getContext '2d'
	[rects, corr] = generate_rects ctx

	tilesize = 8

	mouse_pos = (event) ->
		rect = canvas.getBoundingClientRect()
		new Pos(
			(event.clientX - rect.left) // tilesize,
			(event.clientY - rect.top) // tilesize)

	highlight_rect = (event) ->
		draw_rects ctx, tilesize, 800, 600, rects
		for rect in rects
			if inside(mouse_pos(event), rect)
				draw_rect ctx, tilesize, rect, '#f00'
				if rect.neighbor
					draw_rect ctx, tilesize, rect.neighbor, '#0f0'
		for c in corr
			c.draw()

	redraw = highlight_rect

	canvas.addEventListener 'mousemove', redraw
	canvas.addEventListener 'keydown', redraw

	draw_rects ctx, tilesize, 800, 600, rects
	console.log corr
	for c in corr
		c.draw()

window.addEventListener 'load', init
