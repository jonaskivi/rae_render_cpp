#version 120

uniform int entityID; // up to 65535 id's supported with this system

void main()
{
	float f = float(entityID);
	// put low 8 bits into .r, and next 8 bits into .g
	gl_FragColor = vec4(mod(f,256.0) / 255.0, mod(floor(f / 256.0), 256.0) / 255.0, 0.0, 1.0);

	//gl_FragColor = vec4(entityID/255.0);
}

