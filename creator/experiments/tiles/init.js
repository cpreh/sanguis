window.onload = init;

function init()
{
	var canvas = document.getElementById('canvas');

	var ctx = canvas.getContext('2d');
	draw_tiles(ctx, 800, 600);

	var density = document.getElementById("threshold");
	var tilesize = document.getElementById("size");

	var redraw = function(e)
	{
		draw_tiles(ctx, 800, 600, density.value / 100, tilesize.value);
	};

	density.onchange = redraw;
	tilesize.onchange = redraw;

}

