function dijkstra(nodes, edges, source, target)
{
	var dist = new Array();
	var previous = new Array();

	for (v = 0; v < nodes.length; ++v)
	{
		dist[v] = Infinity;
		previous[v] = undefined;
	}

	dist[source] = 0;

	var Q = Array(nodes.length);
	for (var i = 0; i < Q.length; ++i)
		Q[i] = [i, nodes[i]]; // Q consists of index, node pairs

	while (Q.length > 0)
	{
		// u := vertex in Q with smallest distance in dist;
		var u = Q[0][0]; //first element in Q, its index
		var u_dist = dist[u];
		var w = 0;
		for (var i = 0; i < Q.length; ++i)
		{
			if (dist[Q[i][0]] < u_dist)
			{
				u = Q[i][0];
				w = i;
				u_dist = dist[Q[i][0]];
			}
		}
		// remove u from queue
		Q.splice(w,1);

		if (dist[u] === Infinity)
			break;

		// for each neighbor v of u:
		edges.forEach(
			function(edge, index, array)
			{
				if (edge[0] === u || edge[1] === u)
				{
					var v = (u === edge[0]) ? edge[1] : edge[0];
					var alt = dist[u] + edge[2]; // d(u, v)
					if (alt < dist[v])
					{
						dist[v] = alt;
						previous[v] = u;
						//decrease-key v in Q;
					} // end if
				}
			}
		);
	}

	var ret = new Array();
	var u = target;
	// Construct the shortest path with a stack S
	while (previous[u] != undefined)
{
			// Push the vertex into the stack
			ret.unshift(u);
			// Traverse from target to source
			u = previous[u]
	}//end while ;

	return ret;
}
