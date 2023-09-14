// Fragment shader
#version 420

in vec3 color;

out vec4 outputColour;		// To the frame buffer (aka screen)

void main()
{
//	gl_FragColor = vec4(color, 1.0);

	vec3 vertexRGB = color;

	outputColour = vec4(vertexRGB, 1.0);
}
