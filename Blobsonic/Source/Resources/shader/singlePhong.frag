/* https://learnopengl.com/ */

/*
	Phong fragment shader used for majority of models renders object with phong shading. 
	Allows for multiple point lights. 
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

//Material
uniform vec3 Ka;			//Ambient reflectivity
uniform vec3 Kd;            //Diffuse reflectivity
uniform vec3 Ks;			//Specular reflectivity
uniform float shininess;	//Specular highlight

//Camera/View
uniform vec3 viewPos;		//Camera position

//Fragment
in vec3 fragVert;			//Vertex position in eye space
in vec3 fragNormal;			//Normal position in eye space

//Texture
uniform sampler2D tex;
in vec2 texCoord;			//Texture coordinates

out vec4 Colour;			//Returns fragment - Data used to render pixel

void main() {
	return (texture(tex, texCoord));
}
