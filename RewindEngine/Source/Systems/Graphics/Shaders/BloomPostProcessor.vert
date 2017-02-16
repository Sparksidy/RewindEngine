#version 440

uniform mat4 transformMatrix;

layout(location = 0) in vec2 in_position;
layout(location = 1) in vec2 in_uv;

out vec2 uv;

void main()
{
	gl_Position = transformMatrix * vec4(in_position, 0.0f, 1.0f);
	uv = in_uv;
}