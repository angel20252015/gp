#version 330

in vec3 InterpolatedColor;
in vec3 pposition;
in mat3 NormalMatrix;
in vec3 normal;
in vec2 InterpolatedTexCoord;
in vec4 PixelPositionLightSpace;

uniform float pluzx;
uniform float pluzy;
uniform float pluzz;

uniform float pcamarax;
uniform float pcamaray;
uniform float pcamaraz;
uniform sampler2D ShadowMap;          
uniform sampler2D DiffuseTexture;

out vec4 FragColor;

float IsPixelOccluded(vec4 fragPosLightSpace){

//Correccion de persepectiva. Coordenadas entre [-1,1] = Normalized Device Space
//Transformar projCoords al rango[0,1](projCoords * 0.5 + 0.5)
vec3 projCoords = (fragPosLightSpace.xyz/fragPosLightSpace.w)* 0.5f + 0.5f;

// Muestrear el mapa de profundidad usando projCoords.xy como coordenadas de textura.
// Con esto obtenemos la profundidad del pixel en el primer render (desde la luz).
float closestDepth = texture2D(ShadowMap, projCoords.xy).r;

// La profundidad del pixel desde la actual cámara (ya transformado) está en projCoords.z
float currentDepth = projCoords.z;

// Si la profundidad del render actual es mayor a closestDepth, regresar 1.0f
// De lo contrario, regresar 0.0f
float shadow = currentDepth - 0.005f > closestDepth ? 1.0f : 0.0f;
return shadow;
}

void main(){
	float shadow = IsPixelOccluded(PixelPositionLightSpace);
	//vec3 interpolatedNormal =  NormalMatrix * normal;
	vec3 pluz = vec3(pluzx,pluzy,pluzz);
	vec3 pcamara = vec3(pcamarax,pcamaray,pcamaraz);
	vec3 l =  normalize(pluz-pposition);
	vec3 v =  normalize(pcamara-pposition);
	vec3 r = reflect(-l,normal);
	vec3 lightColor =vec3(1.0f,1.0f,1.0f);
	vec3 ambient = 0.1f*lightColor;
	vec3 diffuse = clamp(dot(normal,l),0,1)*lightColor;
	//vec3 specular = pow(clamp(dot(v,r),0,1), )*lightColor*.5f;
	vec3 specular = clamp(dot(v,r),0,1)*lightColor*0.02f;
	vec4 phong = vec4((ambient + (1.0f - shadow)*(diffuse + specular)),1.0f)* texture2D(DiffuseTexture, InterpolatedTexCoord);
	FragColor = vec4(phong);	
}