#shader vertex
#version 330

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragPos;
out vec3 normal;

void main() 
{
	fragPos = vec3(model * vec4(vertex_position, 1.0));
	normal = normalize(mat3(transpose(inverse(model))) * vertex_normal);
	gl_Position = (projection * view * model) * vec4(vertex_position, 1.0);
}



#shader fragment
#version 330

uniform vec3 eye;
uniform samplerCube skybox;
uniform vec3 colour;

in vec3 fragPos;
in vec3 normal;

out vec4 frag_colour;

void main()
{
	vec3 viewDir = normalize(fragPos - eye);
	vec3 reflection = reflect(viewDir, normal);
    frag_colour = texture(skybox, reflection) * vec4(colour, 1.0);
}