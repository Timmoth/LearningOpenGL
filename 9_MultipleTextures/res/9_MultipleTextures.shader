#shader vertex
#version 410 core

out vec3 Color;
out vec2 Texcoord;

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	gl_Position = vec4(position, 1.0f);
	Texcoord = texcoord;
};

#shader fragment
#version 410 core

layout(location = 0) in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D tex;

void main()
{
	outColor = texture(tex, Texcoord) * vec4(1.0f, 1.0f, 1.0f, 1.0f);
};


