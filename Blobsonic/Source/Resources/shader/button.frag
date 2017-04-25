// https://learnopengl.com/#!In-Practice/Text-Rendering
#version 430 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D button;

void main()
{    
    //vec4 sampled = vec4(1.0, 1.0, 1.0, texture(button, TexCoords).r);
    color =  vec4(1.0,1.0,1.0,1.0); //sampled; //vec4(buttonColor, 1.0) *
}  