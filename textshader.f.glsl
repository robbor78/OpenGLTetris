    varying vec2 f_texcoord;
  uniform sampler2D f_texturemap;
    void main(void) {
  gl_FragColor =  texture2D(f_texturemap, f_texcoord)*vec4(1.0,0.0,0.0,1.0);
    }