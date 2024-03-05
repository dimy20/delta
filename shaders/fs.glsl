#version 330 core

out vec4 finalColor;

in vec4 fragColor;
in vec3 fragNormal;
in vec3 fragPosition;

uniform vec3 ambientColor;

vec3 ligthPosition = vec3(0.0f, 10.f, -10.f);
float ambientStrength = 0.1f;

float compute_diffuse(){
    vec3 light_dir = (normalize(ligthPosition - fragPosition));
    vec3 normal = normalize(fragNormal);
    return max(dot(light_dir, normal), 0);
};

void main(){
    //ambient
    vec3 ambient = (ambientColor * ambientStrength);
    //diffuse
    float diff = compute_diffuse();
    vec3 diffuse = diff * ambientColor;

    vec3 res = (ambient + diffuse) * fragColor.xyz;
    finalColor = vec4(res, fragColor.a);
}
