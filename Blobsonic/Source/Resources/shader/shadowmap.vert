#version 430

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexNormal;
layout (location=2) in vec2 VertexUV;

layout (location=3) in ivec4 BoneIDs; // Stream of vertex bone IDs
layout (location=4) in vec4 Weights; // Stream of vertex weights

uniform mat3 NormalMatrix;

uniform mat4 mModel;			//Model Matrix
uniform mat4 mView;				//View matrix
uniform mat4 mProjection;		//Projection matrix

//uniform mat4 ShadowMatrix;
//uniform vec4 LightPosition;

const int MAX_BONES = 70; // Max number of bones
uniform mat4 gBones[MAX_BONES]; // Bone transformations 

out vec3 normal;
out vec3 N;

out vec2 texCoord;

out vec3 fragVert;				//Fragment vertex in world space
out vec3 fragNormal;			//Fragment normal scaled

out vec4 ShadowCoord
out vec3 LightPos;

void main()
{
	// Multiply each bone transformation by the particular weight
	// and combine them. 
   	mat4 BoneTransform = gBones[ BoneIDs[0] ] * Weights[0];
	BoneTransform += gBones[ BoneIDs[1] ] * Weights[1];
    BoneTransform += gBones[ BoneIDs[2] ] * Weights[2];
    BoneTransform += gBones[ BoneIDs[3] ] * Weights[3];

	// Transformed vertex position 
	vec4 tPos = BoneTransform * vec4(VertexPosition, 1.0);

	//ModelView Matrix
	mat4 mModelView = mView * mModel;

	//Normal Matrix 
	mat4 NMatrix = transpose(inverse(mModel));

	fragVert = vec3(mModel * vec4(VertexPosition,1.0));
	fragNormal = vec3(NMatrix * vec4(VertexNormal,0.0));

	//Texture
	texCoord = VertexUV;

	//Shadows
	ShadowCoord = ShadowMatrix * vec4(VertexPosition,1.0);
	LightPos = vec3(mView * LightPosition);

	//Vertex position with Model, View and Projection transformations
	gl_Position = mProjection * mView * mModel  * vec4(VertexPosition,1.0);
}
