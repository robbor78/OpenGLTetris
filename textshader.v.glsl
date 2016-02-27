in layout (location = 0) vec2 vertex_position;
in layout (location = 1) vec2 vertex_texcoord;

out vec2 f_texcoord;


void main () {
	gl_Position = vec4(vertex_position,0,1);
	f_texcoord = vertex_texcoord;
}