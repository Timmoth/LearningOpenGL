#shader vertex
#version 410 core

out vec3 Color;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

void main()
{
	gl_Position = vec4(position, 1.0f);
	Color = color;
};

#shader fragment
#version 410 core

layout(location = 0) in vec3 Color;
layout(location = 0) out vec3 color;

void main()
{
	color = Color;
};