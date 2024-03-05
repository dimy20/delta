#version 330 core

in vec3 vertexPosition;
in vec3 vertexNormal;
in vec4 vertexColor;

uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProjection;

out vec4 fragColor;
out vec3 fragNormal;
out vec3 fragPosition;

void main(){
    fragPosition = vec3(matModel * vec4(vertexPosition, 1.0));
    fragNormal = vertexNormal;
    fragColor = vertexColor;
    gl_Position = matProjection * matView * matModel * vec4(vertexPosition, 1.0);
}
