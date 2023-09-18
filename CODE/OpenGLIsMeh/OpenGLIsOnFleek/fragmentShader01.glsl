// Fragment shader
#version 420

in vec4 colour;
in vec4 vertexWorldNormal;

out vec4 outputColour;		// To the frame buffer (aka screen)

uniform vec3 directionalLightColour;
// rgb are the rgb of the light colour
uniform vec4 directionalLight_Direction_power;
// xyz is the normalized direction, w = power (between 0 and 1)


void main()
{
//	gl_FragColor = vec4(color, 1.0);

	vec4 vertexRGBA = colour;
	
	// *************************************
	// For now, just trust Michael
	// Very basic directional shader
	vec3 lightContrib = directionalLightColour * directionalLight_Direction_power.w;
	// 
	// Get the dot product of the light and normalize
	float dotProduct = dot( -directionalLight_Direction_power.xyz,  
							vertexWorldNormal.xyz );	
	// Clamp this to a positive number
	dotProduct = max( 0.0f, dotProduct );		// 0 to 1		
	
	lightContrib *= dotProduct;		
	// *************************************
			
//	outputColour = vec4(vertexRGB, 1.0);
	outputColour.rgb = (vertexRGBA.rgb * lightContrib);
	outputColour.a = 1.0f;
}
