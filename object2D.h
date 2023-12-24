#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color);
    Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color);
    Mesh* CreateSquareEmpty(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color);
    Mesh* CreateDiamond(const std::string& name, glm::vec3 leftBottomCorner, float height, float width, glm::vec3 color);
    Mesh* CreateEnemy(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color);
    Mesh* CreateStar(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color);
}
