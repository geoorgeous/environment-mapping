#shader vertex
#version 330

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;
layout (location = 2) in vec2 vertex_texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragPos;
out vec3 normal;
out vec2 texCoords;

void main() 
{
	mat4 mvp = projection * view * model;

	fragPos = vec3(model * vec4(vertex_position, 1.0));
	normal = normalize(mat3(transpose(inverse(model))) * vertex_normal);
	texCoords = vertex_texCoords;
	gl_Position = mvp * vec4(vertex_position, 1.0);
}



#shader fragment
#version 330

struct DirectionalLight
{
	vec3 position;
	vec3 direction;
	vec4 colour;
	float intensity;
};

struct PointLight
{
	vec3 position;
	vec4 colour;
	float intensity;
	float range;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	vec4 colour;
	float intensity;
	float angle;
	float range;
};

struct Material
{
	sampler2D map_diffuse;
	sampler2D map_normal;
	sampler2D map_specular;
	float shininess;
	vec4 colour;
};

uniform PointLight pointLight;
uniform Material material;
uniform vec3 eye;

in vec3 fragPos;
in vec3 normal;
in vec2 texCoords;

out vec4 frag_colour;

void main()
{
	vec4 lightColour = pointLight.colour * pointLight.intensity;

	float dist = distance(fragPos, pointLight.position);
	float attenuation = clamp(1.0 - dist * dist / (pointLight.range * pointLight.range), 0.0, 1.0); 

	float ambientStrength = 0.1;

	vec4 ambient = clamp(attenuation * lightColour, ambientStrength, 1.0);

	vec3 lightDirection = normalize(pointLight.position - fragPos);
	float diff = max(dot(normal, lightDirection), 0);

	vec4 diffuse = attenuation * diff * lightColour;

	vec3 viewDir = normalize(eye - fragPos);

	float spec = 0.0;
	vec3 halfwayDir = normalize(lightDirection + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    
    // vec3 reflectDir = reflect(-lightDirection, normal);
    // spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
	vec4 specular = vec4(1.0) * spec;  
	
    frag_colour = (vec4(texture(material.map_diffuse, texCoords)) * material.colour) * (specular + ambient + diffuse);
}