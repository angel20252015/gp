#version 330

in vec3 VertexPosition;
in vec3 VertexColor;
in vec3 VertexNormal;
in vec2 VertexTexCoord;

out vec3 InterpolatedColor;
out vec3 pposition;
out vec3 normal;
out vec2 InterpolatedTexCoord;    
out vec4 PixelPositionLightSpace;
out mat3 NormalMatrix;

uniform mat4 mvpMatrix;
uniform mat4 LightVPMatrix;
uniform mat4 ModelMatrix;

void main(){
	mat3 NormalMatrix = transpose(inverse(mat3(ModelMatrix)));
	pposition = vec3(ModelMatrix * vec4(VertexPosition, 1.0f));
	PixelPositionLightSpace = LightVPMatrix * vec4(pposition, 1.0);
	InterpolatedColor = VertexColor;
	gl_Position = mvpMatrix * vec4(VertexPosition, 1.0f);
	normal = NormalMatrix*VertexNormal;
	InterpolatedTexCoord = VertexTexCoord;		
}