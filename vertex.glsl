uniform vec2 expl_center;

void main()
{
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_TexCoord[1].st = gl_Vertex.xy;
	gl_Position = ftransform();
}
