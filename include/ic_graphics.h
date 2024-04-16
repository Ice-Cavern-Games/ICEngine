#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include <imgui.h>

#include <stdexcept>
#include <string>
#include <vector>

namespace IC {
    enum class RendererType {
        None = -1,
        Vulkan
    };

    enum MaterialFlags {
        Lit = 1 << 0,
        Transparent = 1 << 1
    };

    struct MaterialConstants {
        glm::vec4 color;
    };

    struct Material {
        MaterialFlags flags;

        std::string fragShaderData;
        std::string vertShaderData;

        MaterialConstants constants;
    };

    struct VertexData {
        glm::vec3 pos;
        glm::vec3 color;
        glm::vec2 texCoord;

        bool operator==(const VertexData &other) const {
            return pos == other.pos && color == other.color && texCoord == other.texCoord;
        }
    };

    struct Mesh {
        std::vector<VertexData> vertices;
        std::vector<uint32_t> indices;
        uint32_t vertexCount;
        uint32_t indexCount;
        glm::vec3 pos;
        glm::vec3 scale;
        glm::vec3 rotation;

        void LoadFromFile(std::string fileName);
    };

    // lights
    struct PointLight {
        // todo: move mesh and material to gameobject/gameobject components
        glm::vec3 color;
        float ambientStrength;

        Mesh previewMesh;
        Material previewMaterial;

        void ParameterGui() {
            ImGui::Begin("Point Light Parameters");
            ImGui::DragFloat3("Light Position", (float *)&previewMesh.pos, 0.01, FLT_MIN, FLT_MAX, "%.3f", 0);
            ImGui::ColorEdit3("Light Color", (float *)&color);
            ImGui::DragFloat("Ambient Strength", &ambientStrength, 0.01, 0, 1.0, "%.3f", 0);
            ImGui::End();
        }
    };
} // namespace IC

namespace std {
    // define hash function for vertices
    template <> struct hash<IC::VertexData> {
        size_t operator()(IC::VertexData const &vertex) const {
            return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^
                   (hash<glm::vec2>()(vertex.texCoord) << 1);
        }
    };
} // namespace std
