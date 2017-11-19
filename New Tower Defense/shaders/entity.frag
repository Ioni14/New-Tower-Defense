uniform sampler2D texture;

void main()
{
    // récupère le pixel dans la texture
	vec4 pixel = vec4(1, 1, 1, 1);
	if (gl_TexCoord[0].x >= 0 && gl_TexCoord[0].y >= 0) {
		pixel = texture2D(texture, gl_TexCoord[0].xy);
	}

    // et multiplication avec la couleur pour obtenir le pixel final
    gl_FragColor = gl_Color * pixel;
}
