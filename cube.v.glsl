in layout (location = 0) vec3 vertex_position;
in layout (location = 1) vec3 vertex_normal;
in layout (location = 2) vec3 vertex_colour;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 position_eye;
out vec3 f_colour;
out vec3 normal_eye;

void main () {
	position_eye = vec3 (view *model* vec4 (vertex_position, 1.0));
	normal_eye = vec3 (view*model * vec4 (vertex_normal, 0.0));
	gl_Position = projection * vec4 (position_eye, 1.0);
	f_colour = vertex_colour;
}