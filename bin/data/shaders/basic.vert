#version 120

// Input vertex data
attribute vec3 inPosition;
attribute vec2 inUV;
attribute vec3 inNormal;

// Output data to fragment shader
varying vec2 UV;
varying vec3 position_worldspace;
varying vec3 normal_cameraspace;
varying vec3 eyeDirection_cameraspace;
varying vec3 lightDirection_cameraspace;

// Constant data
uniform mat4 modelViewProjectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform vec3 lightPosition_worldspace;

void main()
{
	gl_Position =  modelViewProjectionMatrix * vec4(inPosition, 1.0);
	
	position_worldspace = (modelMatrix * vec4(inPosition, 1.0)).xyz;
	
	vec3 vertexPosition_cameraspace = ( viewMatrix * modelMatrix * vec4(inPosition, 1.0)).xyz;
	eyeDirection_cameraspace = vec3(0.0, 0.0, 0.0) - vertexPosition_cameraspace;

	vec3 LightPosition_cameraspace = ( viewMatrix * vec4(lightPosition_worldspace, 1.0)).xyz;
	lightDirection_cameraspace = LightPosition_cameraspace + eyeDirection_cameraspace;
	
	normal_cameraspace = ( viewMatrix * modelMatrix * vec4(inNormal, 0.0)).xyz;
	
	UV = inUV;
}

