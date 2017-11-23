#version 330

in vec3 InterpolatedColor;
in vec3 pposition;
in mat3  NormalMatrix;
in vec3 normal;
in vec2 InterpolatedTexCoord;

uniform float pluzx;
uniform float pluzy;
uniform float pluzz;
uniform sampler2D DiffuseTexture;

uniform float pcamarax;
uniform float pcamaray;
uniform float pcamaraz;

out vec4 FragColor;
void main()
{
	vec3 interpolatedNormal =  NormalMatrix * normal;
	vec3 pluz = vec3(pluzx,pluzy,pluzz);
	vec3 pcamara = vec3(pcamarax,pcamaray,pcamaraz);
	vec3 l =  normalize(pluz-pposition);
	vec3 v =  normalize(pcamara-pposition);
	vec3 r = reflect(-l,interpolatedNormal);
	vec3 lightColor =vec3(1.0f,1.0f,1.0f);
	vec3 ambient = 0.1f*lightColor;
	vec3 diffuse = dot(interpolatedNormal,l)*lightColor;
	vec3 specular = 0.5f*dot(v,r)*lightColor;
	vec4 phong = vec4((ambient + diffuse + specular),1.0f)* texture2D(DiffuseTexture, InterpolatedTexCoord);
	FragColor = phong;
	//FragColor = texture2D(DiffuseTexture, InterpolatedTexCoord);
}