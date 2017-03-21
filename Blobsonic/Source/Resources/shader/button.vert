#version 430

layout (location=0) in vec3 VertexPosition;
layout (location=2) in vec3 VertexNormal;

uniform mat4 mModel;			//Model Matrix
uniform mat3 NormalMatrix;		

uniform mat4 mView;				//View matrix
uniform mat4 mProjection;		//Projection matrix

out vec3 fragNormal;			//Fragment vertex in world space
out vec3 fragVert;				//Fragment normal scaled

void main()
{
	//ModelView Matrix
	mat4 mModelView = mView * mModel;

	//Normal Matrix
	mat4 NMatrix = transpose(inverse(mModel));

	fragVert = vec3(mModel * vec4(VertexPosition,1.0));
	fragNormal = vec3(NMatrix * vec4(VertexNormal,0.0));

	//Vertex position with Model, View and Projection transformations
	gl_Position = mProjection * mView * mModel * vec4(VertexPosition,1.0);
}
