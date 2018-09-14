#version 450 core

out vec4 color;
in vec4 vs_color;
in vec2 vs_texCoord;
uniform bool useTex;
uniform sampler2D sample_tex0;
uniform sampler2D sample_tex1;
void main()
{
	if(useTex)
		color = mix(texture(sample_tex0,vs_texCoord) , texture(sample_tex1 , vs_texCoord) , 0.5);
	else
		color = vs_color;
}