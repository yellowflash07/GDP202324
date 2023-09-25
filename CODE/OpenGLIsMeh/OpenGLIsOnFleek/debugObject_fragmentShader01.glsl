// Fragment shader
#version 420

in vec4 fColour;

out vec4 outputColour;

void main()
{
	outputColour = fColour;
	outputColour.rgb *= 0.001f;
	outputColour.rgb += vec3(1.0, 1.0f, 1.0f);
}
