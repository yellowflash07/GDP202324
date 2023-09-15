// Fragment shader
#version 420

in vec4 colour;

out vec4 outputColour;		// To the frame buffer (aka screen)

void main()
{
//	gl_FragColor = vec4(color, 1.0);

	vec4 vertexRGBA = colour;

//	outputColour = vec4(vertexRGB, 1.0);
	outputColour = vertexRGBA;
}
