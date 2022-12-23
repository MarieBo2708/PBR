#version 330 core

out vec4 FragColor;
in vec2 coordonnees_texture;
/*in vec3 espaceTangent_positionLumiere;
in vec3 espaceTangent_positionVue;
in vec3 espaceTangent_positionFragment;*/

in vec3 position_monde;
in vec3 normal;

uniform vec3 albedo;
//uniform sampler2D normalMap;
uniform float metallic;
uniform float roughness;
uniform float ao;

uniform vec3 position_lumiere;
uniform vec3 couleur_lumiere;

uniform vec3 position_camera;

const float PI = 3.141592653559;

/*vec3 getNormalMap(){
    vec3 normale = texture(normalMap, coordonnees_texture).rgb;
    normale = normalize(normale*2.0 -1.0);

    vec3 color = texture(albedoMap, coordonnees_texture).rgb;

    vec3 ambient = 1.0 * color;

    vec3 direction_lumiere = normalize(espaceTangent_positionLumiere - espaceTangent_positionFragment);
    float diff = max(dot(direction_lumiere, normale), 0.0);
    vec3 diffuse = diff*color;

    vec3 direction_vue = normalize(espaceTangent_positionVue - espaceTangent_positionFragment);
    vec3 reflexion = reflect(-direction_lumiere, normale);
    vec3 halfway = normalize(direction_lumiere + direction_vue);
    float spec = pow(max(dot(normale, halfway), 0.0), 32.0);
    vec3 specular = vec3(0.2)*spec;

    return ambient + diffuse + specular;
}*/

//Normal distribution function
float distribution_normale(vec3 N, vec3 H, float rugosite){
    float a = rugosite*rugosite;
    float a2 = a*a;
    float NH = max(dot(N,H), 0.0);
    float NH2 = NH*NH;

    float numerateur = a2;
    float denominateur = (NH2 * (a2-1.0) + 1.0);
    denominateur = PI * denominateur * denominateur;

    return numerateur/denominateur;
}

//Geometric Schlick function
float geometrie_schlick_beckmann(float NV, float rugosite){
    float r = (rugosite + 1.0);
    float k = (r*r)/8.0;

    float numerateur = NV;
    float denominateur = NV * (1.0 - k) + k;

    return numerateur/denominateur;
}

//Geometric Smith function that uses Schlick function
float geometrie_smith(vec3 N, vec3 V, vec3 L, float rugosite){
    float NV = max(dot(N,V), 0.0);
    float NL = max(dot(N,L), 0.0);
    float ggx2 = geometrie_schlick_beckmann(NV, rugosite);
    float ggx1 = geometrie_schlick_beckmann(NL, rugosite);

    return ggx1*ggx2;
}

//Fesnel function
vec3 fresnel(float costeta, vec3 F0){
    return F0+(1.0-F0)*pow(clamp(1.0 - costeta, 0.0, 1.0), 5.0);
}

void main(){

    vec3 N = normalize(normal);
    vec3 V = normalize(position_camera - position_monde);

   /* vec3 albedo = pow(texture(albedoMap, coordonnees_texture).rgb, vec3(2.2));
    float metallic = texture(metallicMap, coordonnees_texture).r;
    float roughness = texture(roughnessMap, coordonnees_texture).r;
    float ao = texture(aoMap, coordonnees_texture).r;*/

    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, metallic);

    vec3 Lo = vec3(0.0);

    vec3 L = normalize(position_lumiere - position_monde);
        
    vec3 H = normalize(V + L);
    
    float distance = length(position_lumiere - position_monde);
    float attenuation = 1.0/(distance*distance);
    vec3 radiance = couleur_lumiere * attenuation;

    float NDF = distribution_normale(N, H, roughness);
    float G = geometrie_smith(N, V, L, roughness);
    vec3 F = fresnel(clamp(dot(H,V), 0.0, 1.0), F0);

    vec3 numerator = NDF * G * F;
    float denominator = 4.0 * max(dot(N,V), 0.0) * max(dot(N,L), 0.0) + 0.0001;
    vec3 speculaire = numerator/denominator;
   
    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;

    float NL = max(dot(N,L), 0.0);

    Lo += (kD*albedo/PI*speculaire) * radiance * NL;
    
    vec3 ambient = vec3(0.03) * albedo * ao;

    vec3 color = ambient + Lo;

    color = color/(color + vec3(1.0));
    
    color = pow(color, vec3(1.0/2.2));

    FragColor = vec4(color, 1.0);


}