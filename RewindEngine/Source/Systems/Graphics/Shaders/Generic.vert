#version 440

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 transformMatrix;

layout(location = 0) in vec2 in_position;
layout(location = 1) in vec2 in_uv;

out vec2 uv;

void main() {
	gl_Position = projectionMatrix * viewMatrix * transformMatrix * vec4(in_position, 0, 1);
	uv = in_uv;
}