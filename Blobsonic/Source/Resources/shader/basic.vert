#version 430

layout (location=0) in vec3 VertexPosition;
layout (location=2) in vec3 VertexColour;
layout (location=1) in vec2 VertexUV;

in vec4 vertPosition;

uniform mat4 mTranslate;
uniform mat4 mRotate;
uniform mat4 mScale;
uniform mat4 mOrigin;
uniform mat4 mOriginMinus;

uniform mat4 mView;
uniform mat4 mProjection;

in vec3 vertColour;
out vec3 Colour;
out vec2 texCoord;

void main()
{
    Colour = VertexColour;
	texCoord = VertexUV;
	//gl_Position = mProjection * mView * vec4(VertexPosition,1.0);
    gl_Position = mProjection * mView * mTranslate * mOriginMinus * mRotate * mOrigin * mScale * vec4(VertexPosition,1.0);
}
