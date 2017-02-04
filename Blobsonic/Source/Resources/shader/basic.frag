#version 430

//Light intensity
uniform vec3 Ld;            //Diffuse light intensity
uniform vec3 La;			//Ambient intensity
uniform vec3 Ls;			//Specular intensity

//Material
uniform vec3 Ka;			//Ambient reflectivity
uniform vec3 Kd;            //Diffuse reflectivity
uniform vec3 Ks;			//Specular reflectivity

//Texture
uniform sampler2D tex;
in vec2 texCoord;

out vec4 colour;			//Returns fragment - Data to render pixel

void main() {
	colour = texture(tex,texCoord);
}