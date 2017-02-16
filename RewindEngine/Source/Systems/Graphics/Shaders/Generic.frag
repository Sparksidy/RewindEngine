#version 440

const int Color_Mode = 0;
const int Texture_Mode = 1;
const int Animated_Mode = 2;

uniform int mode;

uniform vec3 color;
uniform sampler2D sampler;
uniform mat3 textureMatrix;

in vec2 uv;

layout(location = 0) out vec4 color0;
layout(location = 1) out vec4 color1;

void main() {
	if(mode == Color_Mode)
	{
		color0 = vec4(color, 1);
	}
	else if(mode == Texture_Mode)
	{
		color0 = texture(sampler, uv);
	}
	else
	{
		color0 = texture(sampler, (textureMatrix * vec3(uv, 1)).xy);
	}

	//output to bloom target if surpases threshold, otherwise output black
	float brightness = dot(1.5 * color0.rgb, vec3(0.2126, 0.7152, 0.0722));
	if(brightness > 1.0)
		color1 = color0 * 2;
	else
		color1 = vec4(0, 0, 0, color0.a);
}