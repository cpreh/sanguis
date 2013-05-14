window.onload = init;

function makeLogger(lines){
	return function(text){
		var console = document.getElementById('console');
		var items = console.childNodes;
		if (items.length > lines)
			console.removeChild(items[0]);
		var p = document.createElement('p');
		p.appendChild(document.createTextNode('> ' + text));
		console.appendChild(p);
	};
}

function init()
{
	var log = makeLogger(10);

	var canvas = document.getElementById('canvas');
	canvas.onmousemove = function(e) { log('(' + e.clientX + ', ' + e.clientY + ')'); };

	var ctx = canvas.getContext('2d');

	grid = new JitteredGrid(ctx, 800, 600);
}


function line(context, from, to)
{
	context.moveTo(from[0], from[1]);
	context.lineTo(to[0], to[1]);
}
