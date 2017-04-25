// https://learnopengl.com/#!In-Practice/Text-Rendering
#version 430 core
layout (location = 0) in vec4 VertexPosition; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 mProjection;
uniform mat4 mModel;
uniform mat4 mViewO;
uniform mat4 mView;

void main()
{
	vec2 pos = vec2(10,10) * VertexPosition.xy;

	gl_Position = mProjection * vec4(pos, 1.0f, 0.0f);
    gl_Position = mProjection * mModel * vec4(VertexPosition.xy, 0.0, 1.0);
    gl_Position = mProjection * mView * mModel * vec4(pos, VertexPosition.z, 1.0);
    TexCoords = VertexPosition.zw;
}  