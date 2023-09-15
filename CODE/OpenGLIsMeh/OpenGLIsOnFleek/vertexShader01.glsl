// Vertex shader
#version 420

uniform mat4 MVP;

//uniform vec3 modelScale;
//uniform vec3 modelOffset;

in vec4 vCol;		// was vec3
in vec4 vPos;		// was vec3
in vec4 vNormal;	// NEW for 2023!

out vec4 colour;

void main()
{
	vec4 finalPos = vPos;	
	
//	gl_Position = MVP * vec4(finalPos, 1.0);
	gl_Position = MVP * finalPos;
	
	// bunny goes from -0.07 to 0.07
	vec4 finalColour = vCol;
	
	finalColour *= 0.00001f;		// "black"
	
	finalColour += vNormal;
	
//	if ( vPos.y < 0.0 )
//	{
//		stripeColour = vec3(1.0f, 0.0f, 0.0f);
//	}
//	if ( vPos.y > 0.0 )
//	{
//		stripeColour = vec3(0.0f, 1.0f, 0.0f);
//	}
	
	
	colour = finalColour;
}
