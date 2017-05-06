// https://learnopengl.com/#!In-Practice/Text-Rendering
#version 430 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D sprite;
uniform vec3 spriteColor;

void main()
{    
   color = vec4(spriteColor, 1.0) * texture(sprite, TexCoords);
   //color = texture(sprite, TexCoords);
   //color = vec4(1.0f);
   //color = vec4(spriteColor, 1.0) * texture2D(sprite, TexCoords); 
   //if (spriteColor.w < 1) gl_FragColor = vec4(1,0,0,1); 
  // else gl_FragColor = vec4(0,1,0,1);
}  