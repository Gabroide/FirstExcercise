#version 330 core
uniform vec3 albedo;

out vec4 color;

void main()
{
	color = vec4(albedo.x, albedo.y, albedo.z, 1.0f);
}