uniform sampler2D grasstex,expltex;
uniform vec2 expl_center;

void main()
{
	vec4 expl = texture2D(
		expltex,
		gl_TexCoord[0].st);

	vec2 add = normalize(gl_TexCoord[1].st - expl_center) * expl.x;
	vec2 final_pos = vec2(gl_TexCoord[1]) + add;

	vec4 final = texture2D(
		grasstex,
		final_pos);

	gl_FragColor = final;
}
