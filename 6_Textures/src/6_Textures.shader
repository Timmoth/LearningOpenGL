#shader vertex
#version 410 core

out vec3 Color;
out vec2 Texcoord;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texcoord;

void main()
{
	gl_Position = vec4(position, 1.0f);
	Color = color;
	Texcoord = texcoord;
};

#shader fragment
#version 410 core

layout(location = 0) in vec3 Color;
layout(location = 1) in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D tex;

void main()
{
	outColor = texture(tex, Texcoord) * vec4(0.5f, 0.5f, 0.5f, 1.0);
};


