#version 330

// TODO: get values from fragment shader
in vec3 frag_color;
in vec3 frag_normal;

layout(location = 0) out vec4 out_color;

uniform float time;


void main()
{
	// TODO: write pixel out color
	//out_color = vec4(frag_color * cos(time), 1.0);
	out_color = vec4(frag_color, 1.0);
}