#version 440

uniform sampler2D inputTexture;
uniform sampler2D bloomTexture;

uniform int stage;

in vec2 uv;

layout(location = 0) out vec4 color0;
layout(location = 1) out vec4 color1;

const float offset = 1.0f / 600.0f;

const vec2 offsets[9] = {
	vec2(-offset, offset),
	vec2(0.0f, offset),
	vec2(offset, offset),
	vec2(-offset, 0.0f),
	vec2(0.0f, 0.0f),
	vec2(offset, 0.0f),
	vec2(-offset, -offset),
	vec2(0.0f, -offset),
	vec2(offset, -offset)
};

const float gaussianKernel[9] = {
	1.0f/16.0f, 1.0f/8.0f, 1.0f/16.0f,
	1.0f/8.0f,  1.0f/4.0f, 1.0f/8.0f,
	1.0f/16.0f, 1.0f/8.0f, 1.0f/16.0f
};

void main()
{
	if(stage == 0)
	{
		//blur the inputTexture and output to color1
		vec3 samples[9];
		for(int i = 0;i < 9;i++)
		{
			samples[i] = texture(bloomTexture, uv + offsets[i]).xyz;
		}

		vec3 color = vec3(0, 0, 0);
		for(int i = 0;i<9;i++)
		{
			color += samples[i] * gaussianKernel[i];
		}

		color0 = texture(inputTexture, uv);
		color1 = vec4(color, 1);
	}
	else
	{
		//combine the inputTexture and bloomTexture and output to color0
		vec3 inColor0 = texture(inputTexture, uv).rgb;
		vec3 inColor1 = texture(bloomTexture, uv).rgb;

		inColor0 += inColor1;
		vec3 result = inColor0;
		color0 = vec4(result, 1);//texture(inputTexture, uv);
		color1 = texture(bloomTexture, uv);
	}	
}