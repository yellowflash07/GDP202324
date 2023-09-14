// Vertex shader
#version 420

uniform mat4 MVP;

in vec3 vCol;		// was 'attribute' from vertex buffer
in vec3 vPos;

out vec3 color;

void main()
{
	gl_Position = MVP * vec4(vPos, 1.0);
	
	// bunny goes from -0.07 to 0.07
	vec3 stripeColour = vCol;
	
//	if ( vPos.y < 0.0 )
//	{
//		stripeColour = vec3(1.0f, 0.0f, 0.0f);
//	}
//	if ( vPos.y > 0.0 )
//	{
//		stripeColour = vec3(0.0f, 1.0f, 0.0f);
//	}
	
	
	color = stripeColour;
}
