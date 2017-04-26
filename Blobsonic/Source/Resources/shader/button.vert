// https://learnopengl.com/#!In-Practice/Text-Rendering
#version 430 core
layout (location = 0) in vec4 VertexPosition; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 mProjection;
uniform mat4 mModel;
uniform mat4 mViewO;
uniform mat4 mView;
uniform mat4 viewPos;

void main()
{
	vec2 pos = vec2(20,20) * VertexPosition.xy;
	vec2 viewSize = vec2(1024,768);
	vec2 viewOffset = vec2(20,20);

	vec4 clipSpacePos = mProjection * (mView * vec4(VertexPosition.xyz, 1.0));
	vec3 ndcSpacePos = clipSpacePos.xyz / clipSpacePos.w;
	vec2 windowSpacePos = ((ndcSpacePos.xy + 1.0) / 2.0) * viewSize + viewOffset;

	//gl_Position = mProjection * vec4(pos, 0.0, 1.0f);
    //gl_Position = mViewO * VertexPosition;
	gl_Position = mProjection * mView * mModel * vec4(VertexPosition.xyz, 1.0);

	//gl_Position = vec4(VertexPosition.xy, 0.0, 1.0);

	vec2 vertexPosition_homoneneousspace = VertexPosition.xy - vec2((1024/2),(768/2)); // [0..1024][0..768] -> [-400..400][-300..300]
    vertexPosition_homoneneousspace /= vec2((1024/2),(768/2));
	gl_Position = vec4(vertexPosition_homoneneousspace, 0.0, 1.0);
    TexCoords = VertexPosition.zw;
}  