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

uniform float speedBuffDuration;

// TODO: output values to fragment shader
out vec3 frag_color;
out vec3 frag_normal;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453) * 0.2;
}

float rnd(vec2 x)
{
    int n = int(x.x * 40.0 + x.y * 6400.0);
    n = (n << 13) ^ n;
    return 1.0 - float( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0;
}

void main()
{
	// TODO: send output to fragment shader
	frag_color = color;
	frag_normal = normal;

	// TODO: compute gl_Position
	if (speedBuffDuration > 0) {
		gl_Position = Projection * View * Model * vec4(position + normal * sin(time) * rand(vec2(position.x, position.y)) * 0.7, 1.0);
	} else {
		gl_Position = Projection * View * Model * vec4(position, 1.0);
	}
}
