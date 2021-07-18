#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 3) in vec3 color;
layout(location = 2) in vec2 texture;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float time;

// TODO: output values to fragment shader
out vec3 frag_color;
out vec3 frag_normal;

void main()
{
	// TODO: send output to fragment shader
	frag_color = color;
	frag_normal = normal;

	// TODO: compute gl_Position
	gl_Position = Projection * View * Model * vec4(position, 1.0);
	
}
