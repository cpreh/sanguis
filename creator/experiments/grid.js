window.onload=function(){init();};

function init()
{
	var canvas=document.getElementById('canvas');
	if (!canvas.getContext)
	{
		alert("Could not get a 2D context!");
	}

	const width = 800;
	const height = 600;

	var ctx=canvas.getContext('2d');
	ctx.fillStyle='rgba(255,255,255,1.0)';
	ctx.fillRect(0,0,width,height);

	ctx.lineWidth = 1;

	ctx.fillStyle =
		rgbColor(
			Math.random() * 205,
			Math.random() * 205,
			Math.random() * 205);

	ctx.strokeStyle =
		rgbaColor(
			Math.random() * 100,
			Math.random() * 100,
			Math.random() * 100,
			0.25);

	spacing = {'x': 40, 'y': 40};
	jitter = {'x': 20, 'y': 20};
	len = {
		'x': Math.floor(width/spacing['x']),
		'y': Math.floor(height/spacing['y'])
	};

	points = Array(len['x'] * len['y']);

	for (var p = 0; p < points.length; ++p)
	{
		var y = Math.floor(p / len['x']);
		var x = Math.floor(p % len['x']);
		points[p] = [
			spacing['x'] * x + Math.floor(Math.random() * jitter['x']),
			spacing['y'] * y + Math.floor(Math.random() * jitter['y'])
		];

		ctx.fillRect(
			points[p][0] - 2,
			points[p][1] - 2,
			4,
			4
		);
	}

	var edges = [];

	for (var p = 0; p < points.length; ++p)
	{
		var x = Math.floor(p % len['x']);
		var lenx = len['x'];

		function weight() {return Math.pow(Math.random(), 50);}

		if (p + 1 < points.length && x < (lenx - 1))
			edges.push([p, p + 1, weight()]);
		if (p + len['x'] < points.length)
			edges.push([p, p + len['x'], weight()]);
		if (p + len['x'] + 1 < points.length && x < (lenx - 1))
			edges.push([p, p + len['x'] + 1, weight()]);
		if (p + len['x'] - 1 < points.length && x > 0)
			edges.push([p, p + len['x'] - 1, weight()]);
	}

	for (var e in edges)
	{
		ctx.beginPath();
		ctx.strokeStyle = rgbaColor(0,0,100,edges[e][2]);
		line(ctx, points[edges[e][0]], points[edges[e][1]]);
		ctx.closePath();
		ctx.stroke();
	}

	// shortest path
	var target = Math.floor(Math.random() * len.y + 1) * len.x - 1;

	ctx.fillStyle='rgba(255,0,0,0.5)';
	ctx.fillRect(points[0][0]-8,points[0][1]-8,16,16);
	ctx.fillStyle='rgba(0,255,0,0.5)';
	ctx.fillRect(points[target][0]-8,points[target][1]-8,16,16);

	var path = dijkstra(points, edges, 0, target);

	ctx.lineWidth = 4;
	ctx.strokeStyle = rgbaColor(255, 0, 0, 0.5);
	ctx.beginPath();
	line(ctx, points[0], points[path[0]]);
	for (var v=0; v < path.length - 1; ++v)
	{
		line(ctx, points[path[v]], points[path[v+1]]);
	}
	ctx.closePath();
	ctx.stroke();
}

function rgbColor(r, g, b)
{
	return 'rgb(' +
		Math.floor(r) + ',' +
		Math.floor(g) + ',' +
		Math.floor(b) + ')';
}

function rgbaColor(r, g, b, a)
{
	return 'rgba(' +
		Math.floor(r) + ',' +
		Math.floor(g) + ',' +
		Math.floor(b) + ',' +
		a + ')';
}

function line(context, from, to)
{
	context.moveTo(from[0], from[1]);
	context.lineTo(to[0], to[1]);
}
