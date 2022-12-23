#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 Normal;
//layout(location = 2) in vec3 tangent;
layout(location = 3) in vec2 uv0;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 coordonnees_texture;
out vec3 position_monde;
out vec3 normal;

/*out vec3 espaceTangent_positionLumiere;
out vec3 espaceTangent_positionVue;
out vec3 espaceTangent_positionFragment;

uniform vec3 position_lumiere;
uniform vec3 position_vue;
uniform vec3 couleur_lumiere;*/

void main() {

  
  coordonnees_texture = uv0;
  position_monde = vec3(model*vec4(position, 1.0));
  normal = mat3(model) * Normal;
  gl_Position = projection * view * vec4(position_monde, 1.0);

  /*mat3 normalMatrix = transpose(inverse(mat3(model)));
  vec3 T = normalize(normalMatrix*tangent);
  vec3 N = normalize(normalMatrix*Normal);
  T = normalize(T - dot(T,N) * N);
  vec3 B = cross(N, T);

  mat3 TBN = transpose(mat3(T,B,N));
  espaceTangent_positionLumiere = TBN * position_lumiere;
  espaceTangent_positionVue = TBN * position_vue;
  espaceTangent_positionFragment = TBN * position_monde;

  */

  

  
  
}
