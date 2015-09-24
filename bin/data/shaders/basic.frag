#version 120

// Input data from vertex shader
varying vec2 UV;
varying vec3 position_worldspace;
varying vec3 normal_cameraspace;
varying vec3 eyeDirection_cameraspace;
varying vec3 lightDirection_cameraspace;

// Constant data
uniform sampler2D textureSampler;
uniform vec3 lightPosition_worldspace;

void main()
{
	vec3 lightColor = vec3(1.0, 1.0, 1.0);
	float lightPower = 45.0f;
	
	vec3 materialDiffuseColor = texture2D( textureSampler, UV ).rgb;
	vec3 materialAmbientColor = vec3(0.5, 0.5, 0.5) * materialDiffuseColor;
	vec3 materialSpecularColor = vec3(0.3, 0.3, 0.3);

	float distanceToLight = length( lightPosition_worldspace - position_worldspace );

	vec3 normalFragment = normalize( normal_cameraspace );
	vec3 lightDirection = normalize( lightDirection_cameraspace );
	float cosTheta = clamp( dot(normalFragment, lightDirection), 0.0, 1.0 );
	
	vec3 eyeDirection = normalize(eyeDirection_cameraspace);
	vec3 reflectionDirection = reflect(-lightDirection, normalFragment);
	
	float cosAlpha = clamp( dot(eyeDirection, reflectionDirection), 0.0, 1.0 );
	
	gl_FragColor.rgb = 
		// Ambient
		materialAmbientColor +
		// Diffuse
		materialDiffuseColor * lightColor * lightPower * cosTheta / (distanceToLight * distanceToLight) +
		// Specular
		materialSpecularColor * lightColor * lightPower * pow(cosAlpha, 5) / (distanceToLight * distanceToLight);

}