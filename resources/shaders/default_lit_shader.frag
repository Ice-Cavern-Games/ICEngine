#version 450

#extension GL_GOOGLE_include_directive : require
#include "lighting_headers.glsl"

layout(binding = 2) uniform sampler2D diffuseTexture;
layout(binding = 3) uniform sampler2D specularMask;

layout(push_constant) uniform PushConstants {
    mat4 model;
    mat4 view;
}
mv;

layout(location = 0) in vec4 fragColor;
layout(location = 1) in vec3 fragPos;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
    vec3 result;
    result = calcDirectionalLight(lightData.directional, normal, fragPos);
    for (int i = 0; i < lightData.numPointLights; i++) {
        result += calcPointLight(lightData.pointLights[i], normal, fragPos);
    }
    outColor = texture(diffuseTexture, fragTexCoord) * vec4(result * fragColor.rgb, 1.0);
}
