#version 330

// TODO: get values from fragment shader
in vec3 frag_color;
in vec3 frag_normal;

layout(location = 0) out vec4 out_color;

uniform float time;


void main()
{
	// TODO: write pixel out color
	vec3 platformColor = vec3(frag_color.x * sin(time * 4) , frag_color.y + sin(time / 2) + 0.2, frag_color.z * cos(time * 3));
	out_color = vec4(platformColor, 1.0);
	//out_color = vec4(frag_normal, 1.0);
}