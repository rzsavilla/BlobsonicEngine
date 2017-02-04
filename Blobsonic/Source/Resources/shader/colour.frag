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

//Colour
uniform vec3 myColour;		//Vertex Colour

out vec4 Colour;			//Returns fragment - Data used to render pixel

void main() {

	vec3 viewDir = normalize(viewPos - fragVert);

	vec4 result;	//Result of all light calculations from array of lights
	for (int i = 0; i < POINT_LIGHT_COUNT; i++) {
		result += vec4(calcPointLight(pLight[i], fragNormal,fragVert, viewDir),1.0f);
	}

	Colour = result * vec4(myColour,1.0);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragVert);
	
	//////Ambient//////
	vec3 ambient = light.La * Ka;

	//////Diffuse//////
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = light.Ld * Kd * diff;
	diffuse = clamp(diffuse,0.0,1.0);

	//////Specular//////
	viewDir = normalize(viewPos - fragVert);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	vec3 specular =  light.Ls * Ks * spec;

	////Light Attenuation//////
	if (light.radius > 0) {
		//Gradual loss of light intensity over distance
		float att = smoothstep(light.radius, 0, length(light.position - fragVert));
		
		//Apply attenuation
		ambient *= att;
		diffuse *= att;
		specular *= att;
	}
	return ambient + diffuse + specular;
	//return vec3(1.0f,1.0f,1.0f);
}


