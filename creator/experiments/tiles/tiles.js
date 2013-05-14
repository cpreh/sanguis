
var draw_tiles = function(ctx, width, height, threshold, tilesize)
{
	if (threshold == undefined)
		threshold = 0.5;
	if (tilesize == undefined)
		tilesize = 32;
	var gridsize = {"x": ctx.canvas.width / tilesize, "y": ctx.canvas.width / tilesize};

	var images = document.getElementsByTagName("img");

	var grid = [];

	for (var j = 0; j < gridsize.y; ++j)
	{
		grid[j] = [];
		for (var i = 0; i < gridsize.x; ++i)
		{
			grid[j][i] = Math.random() < threshold ? 1 : 0;
		}
	}

	for (var j = 0; j < gridsize.y; ++j)
	{
		for (var i = 0; i < gridsize.x; ++i)
		{
			var index = calculate_index(grid, i, j);

			sprite = images[index];

			ctx.fillStyle = grid[j][i] ? "#550000" : "#005500";
			ctx.fillRect(
				i * tilesize,
				j * tilesize,
				tilesize,
				tilesize
			);

			if (grid[j][i])
				ctx.drawImage(
					sprite,
					i * tilesize,
					j * tilesize,
					tilesize,
					tilesize
				);
		}
	}

	// draw_help_text(ctx);
}

var draw_help_text = function(ctx)
{
	ctx.fillStyle = "white";
	ctx.font = "16pt sans-serif";
	ctx.textAlign = "left";
	ctx.textBaseline = "top";
	ctx.shadowOffsetX = 1;
	ctx.shadowOffsetY = 1;
	ctx.shadowColor = "rgba(0, 0, 0, 1.0)";
	ctx.fillText(
		"click to redraw",
		0,
		0
	);
	ctx.shadowColor = "rgba(0,0,0,0)";
}

var cell_value = function(grid, i, j)
{
	var row = grid[j];
	if (!row)
		return 0;
	return row[i] || 0;
}

var calculate_index = function(grid, i, j)
{
	if (cell_value(grid, i, j) == 0)
		return 0;
	var north = cell_value(grid, i, j - 1);
	var west = cell_value(grid, i - 1, j);
	var south = cell_value(grid, i, j + 1);
	var east = cell_value(grid, i + 1, j);

	return 1 * north +
		2 * west +
		4 * east +
		8 * south;
}
