uniform vec2 expl_center;

void main()
{
	gl_TexCoord[0] = gl_MultiTexCoord0;

	/*
	if (gl_Vertex.x < expl_center.x)
		gl_TexCoord[1].s = expl_center.x-128;
	else
		gl_TexCoord[1].s = expl_center.x+128;
	
	if (gl_Vertex.y < expl_center.y)
		gl_TexCoord[1].t = expl_center.y-128;
	else
		gl_TexCoord[1].t = expl_center.y+128;
	*/

	gl_TexCoord[1].st = gl_Vertex.xy;
	gl_Position = ftransform();
}
