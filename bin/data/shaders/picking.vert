#version 120

// Input vertex data
attribute vec3 inPosition;
attribute vec2 inUV; //unused TODO remove
attribute vec3 inNormal; //unused TODO remove

// Constant data
uniform mat4 modelViewProjectionMatrix;
uniform int entityID;

void main()
{
	gl_Position =  modelViewProjectionMatrix * vec4(inPosition, 1.0);
}


