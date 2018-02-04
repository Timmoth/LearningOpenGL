#shader vertex
#version 410 core

layout(location = 0) in vec4 position;

void main()
{
	gl_Position = position;
};

#shader fragment
#version 410 core

layout(location = 0) out vec3 color;

void main()
{
	color = vec3(0.2, 0.3, 0.4);
};