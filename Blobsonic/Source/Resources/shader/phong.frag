/* 
Tutorial https://learnopengl.com/ */
/*
*	@author Rozen Savilla
*	Phong fragment shader used for majority of models renders object with phong shading. 
*	Allows for multiple lights. 
*/

#version 430 core

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

//------------------------LIGHTING Variables/Uniforms/Functions-----------------------------//
//OpenGL required const number for arrays, must be manually changed when lights are changed
#define DIR_LIGHT_COUNT 1
#define POINT_LIGHT_COUNT 1  
#define SPOT_LIGHT_COUNT 1

//Dir Light parameters
struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

//Point Light parameters
struct PointLight {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 position;
	float radius;
};

//Spot Light parameters
struct Spotlight {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;
	float constant;
	float linear;
	float quadratic;
};

uniform DirLight dirLights[DIR_LIGHT_COUNT];		//Array of directional lights
uniform PointLight pointLights[POINT_LIGHT_COUNT];	//Array of point lights
uniform Spotlight spotlights[SPOT_LIGHT_COUNT];	//Array of point lights

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDirection) {
	//Calculate light direction to current vertex
	vec3 lightDirection = normalize(-light.direction);

    //--Diffuse--
    float diff = max(dot(normal, lightDirection), 0.0);

    //--Specular--
    vec3 reflectDir = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), shininess);

    vec3 ambient = light.ambient * Ka;
    vec3 diffuse = light.diffuse * diff * Kd ;
    vec3 specular = light.specular * spec * Ks;
    return (ambient + diffuse + specular);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragmentPosition, vec3 viewDirection) {
	vec3 norm = normalize(normal);
	vec3 lightDirection = normalize(light.position - fragmentPosition);
	
	//////Ambient//////
	vec3 ambient = light.ambient * Ka;

	//////Diffuse//////
	float diff = max(dot(norm,lightDirection),0.0);
	vec3 diffuse = light.diffuse * Kd * diff;
	diffuse = clamp(diffuse,0.0,1.0);

	//////Specular//////
	vec3 reflectDir = reflect(-lightDirection, norm);
	float spec = pow(max(dot(viewDirection, reflectDir), 0.0), shininess);
	vec3 specular =  light.specular * Ks * spec;

	////Light Attenuation//////
	if (light.radius > 0) {
		//Gradual loss of light intensity over distance
		float att = smoothstep(light.radius, 0, length(light.position - fragmentPosition));
		
		//Apply attenuation
		ambient *= att;
		diffuse *= att;
		specular *= att;
	}
	return ambient + diffuse + specular;
}

vec3 calcSpotlight(Spotlight light, vec3 normal, vec3 fragmentPosition, vec3 viewDirection) {
	vec3 lightDirection = normalize(light.position - fragmentPosition); //Light Direction to the current vertex;
	vec3 targetDirection = normalize(-light.direction);					//Light direction to spotlight target
	float angle = dot(lightDirection,targetDirection);

	//--Attenuation--------------------------
	float distance = length(light.position - fragmentPosition);
	float fAtt = angle / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
	fAtt = clamp(fAtt,0.0,1.0);

	//--Light Intensity-----------------
	float theta = dot(lightDirection, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	if (angle > light.outerCutOff) {
		//--Ambient------------------------
		vec3 ambient = light.ambient * Ka;

		//--Diffuse------------------------
		float diff = max(dot(normal,lightDirection),0.0);
		vec3 diffuse = light.diffuse * diff * Kd;

		//--Specular----------------------
		vec3 reflectDir = reflect(-lightDirection, normal);
		float spec = pow(max(dot(viewDirection, reflectDir), 0.0), shininess);
		vec3 specular = light.specular * spec * Ks;

		//Apply attenuation and light intensity
		ambient *= fAtt * intensity;
		diffuse *= fAtt * intensity;
		specular *= fAtt * intensity;

		return vec3(ambient + diffuse + specular);
	}
	return vec3(0.0f,0.0f,0.0f);
}

//Calculate light
vec4 applyLights(vec3 fragmentPos,vec3 fragmentNormal, vec3 viewDirection) {
	vec4 result = vec4(0.0f);
	for (int i = 0; i < DIR_LIGHT_COUNT; i++) {
		result += vec4(calcDirLight(dirLights[i], fragmentNormal, viewDirection),1.0f);
	}

	for (int i = 0; i < POINT_LIGHT_COUNT; i++) {
		result += vec4(calcPointLight(pointLights[i], fragmentNormal,fragmentPos, viewDirection),1.0f);
	}
	
	for (int i = 0; i < SPOT_LIGHT_COUNT; i++) {
		result += vec4(calcSpotlight(spotlights[i], fragmentNormal,fragmentPos, viewDirection),1.0f);
	}
	return result;
}
//-------------------------------------------------------------------------------------------//

//------------------------------------MAIN--------------------------------------------------//
out vec4 Colour;			//Returns fragment - Data used to render pixel

void main() {
	vec3 viewDir = normalize(viewPos - fragVert);

	//--Lighting--//
	vec4 lights;	//Result of all light calculations from array of lights
	lights = applyLights(fragVert,fragNormal,viewDir);
	//------------//

	//Colour = texture(tex, texCoord);	//Just Textures
	Colour = texture(tex, texCoord) * lights;	//Textures + lighting
	//Colour = vec4(1.0f,0.0f,1.0,0.1f);
}
//------------------------------------------------------------------------------------------//