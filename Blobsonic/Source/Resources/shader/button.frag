/* https://learnopengl.com/ */

/*
	Colour shader used for Robot renders object with phong shading 
	but instead of texture a colour is applied.
	Allows for multiple point lights 
*/

#version 430

//OpenGL required const number for arrays, must be manually changed when lights are changed
#define POINT_LIGHT_COUNT 3  

struct PointLight {
	vec3 Ld;
	vec3 La;
	vec3 Ls;
	vec3 position;
	float radius;
};

uniform int pLightCount;
uniform PointLight pLight[POINT_LIGHT_COUNT];	//Array of point lights

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);	//Declare function

//Colour
uniform vec3 myColour;		//Vertex Colour

out vec4 Colour;			//Returns fragment - Data used to render pixel

void main() {

	Colour = vec4(myColour,1.0);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	
	return vec3(1.0f,1.0f,1.0f);
}


