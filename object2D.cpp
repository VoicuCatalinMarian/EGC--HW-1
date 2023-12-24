#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* object2D::CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float width, float length, glm::vec3 color)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color), // 0
        VertexFormat(corner + glm::vec3(0, length, 0), color), // 1
        VertexFormat(corner + glm::vec3(width, length, 0), color), // 2
        VertexFormat(corner + glm::vec3(width, 0, 0), color) // 3
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        0, 2, 3
    };

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2D::CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color), // 0
        VertexFormat(corner + glm::vec3(0, length, 0), color), // 1
        VertexFormat(corner + glm::vec3(length, length, 0), color), // 2
        VertexFormat(corner + glm::vec3(length, 0, 0), color) // 3
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        0, 2, 3
    };

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateSquareEmpty(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color), // 0
        VertexFormat(corner + glm::vec3(0, length, 0), color), // 1
        VertexFormat(corner + glm::vec3(length, length, 0), color), // 2
        VertexFormat(corner + glm::vec3(length, 0, 0), color) // 3
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices =
    {
        0, 1, 2, 3
    };

    square->SetDrawMode(GL_LINE_LOOP);

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateDiamond(const std::string& name, glm::vec3 leftBottomCorner, float height, float width, glm::vec3 color)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, 0, 1), color), // 0
        VertexFormat(corner + glm::vec3(0.5f * width, 0.5f * height, 1), color), // 1
        VertexFormat(corner + glm::vec3(width, 0, 1), color), // 2
        VertexFormat(corner + glm::vec3(0.5f * width, -0.5f * height, 1), color), // 3
        VertexFormat(corner + glm::vec3(0.5f * width, 0.1f * height, 1), color), // 4
        VertexFormat(corner + glm::vec3(1.6f * width, 0.1f * height, 1), color), // 5
        VertexFormat(corner + glm::vec3(1.6f * width, -0.1f * height, 1), color), // 6
        VertexFormat(corner + glm::vec3(0.5f * width, -0.1f * height, 1), color) // 7
    };

    Mesh* diamond = new Mesh(name);
    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        0, 2, 3,
        2, 4, 5,
        2, 5, 6,
        2, 6, 7
    };

    diamond->InitFromData(vertices, indices);
    return diamond;
}

Mesh* object2D::CreateStar(const std::string& name, glm::vec3 leftBottomCorner, float side, glm::vec3 color)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        //VertexFormat(corner + glm::vec3(0.65f * side, 0.875f * side, 2), color), // 0
        //VertexFormat(corner + glm::vec3(0, 0, 2), color), // 1
        //VertexFormat(corner + glm::vec3(0.2f * side, 0.7f * side, 2), color), // 2
        //VertexFormat(corner + glm::vec3(-0.35f * side, 1.15f * side, 2), color), // 3
        //VertexFormat(corner + glm::vec3(0.4f * side, 1.15f * side, 2), color), // 4
        //VertexFormat(corner + glm::vec3(0.6f * side, 1.75f * side, 2), color), // 5
        //VertexFormat(corner + glm::vec3(0.8f * side, 1.15f * side, 2), color), // 6
        //VertexFormat(corner + glm::vec3(1.55f * side, 1.15f * side, 2), color), // 7
        //VertexFormat(corner + glm::vec3(1.00f * side, 0.7f * side, 2), color), // 8
        //VertexFormat(corner + glm::vec3(1.20f * side, 0, 2), color), // 9
        //VertexFormat(corner + glm::vec3(0.6f * side, 0.4f * side, 2), color), // 10

        VertexFormat(corner + glm::vec3(0, 0, 2), color), // 0
        VertexFormat(corner + glm::vec3(-0.35f * side, 1.15f * side, 2), color), // 1
        VertexFormat(corner + glm::vec3(0.6f * side, 1.75f * side, 2), color), // 2
        VertexFormat(corner + glm::vec3(0.8f * side, 1.15f * side, 2), color), // 3
        VertexFormat(corner + glm::vec3(1.55f * side, 1.15f * side, 2), color), // 4
        VertexFormat(corner + glm::vec3(1.00f * side, 0.7f * side, 2), color), // 5
        VertexFormat(corner + glm::vec3(1.20f * side, 0, 2), color), // 6
        VertexFormat(corner + glm::vec3(0.6f * side, 0.4f * side, 2), color), // 7
    };

    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices =
    {
        /*0, 3, 7,
        1, 5, 8,
        3, 6, 9,
        3, 7, 10*/

        0, 2, 5,
        1, 3, 6,    
        1, 4, 7
    };

    star->InitFromData(vertices, indices);
    return star;
}

Mesh* object2D::CreateEnemy(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color)
{
    glm::vec3 corner = leftBottomCorner;
    glm::vec3 inside_color = glm::vec3(0.2f, 0.6f, 0.6f);

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0.875f * length, 0.625f * length, 4), inside_color), // 0
        VertexFormat(corner + glm::vec3(0, 0, 4), inside_color), // 1
        VertexFormat(corner + glm::vec3(0, length, 4), inside_color), // 2
        VertexFormat(corner + glm::vec3(0.875f * length, 1.5f * length, 4), inside_color), // 3
        VertexFormat(corner + glm::vec3(1.75f * length, length, 4), inside_color), // 4
        VertexFormat(corner + glm::vec3(1.75f * length, 0, 4), inside_color), // 5
        VertexFormat(corner + glm::vec3(0.875f * length, -0.5f * length, 4), inside_color), // 6

        VertexFormat(corner + glm::vec3(0.875f * length, 0.625f * length, 3), color), // 7
        VertexFormat(corner + glm::vec3(-0.3f * length, -0.2f * length, 3), color), // 8
        VertexFormat(corner + glm::vec3(-0.3f * length, 1.2f * length, 3), color), // 9
        VertexFormat(corner + glm::vec3(0.875f * length, 1.9f * length, 3), color), // 10
        VertexFormat(corner + glm::vec3(2.05f * length, 1.2f * length, 3), color), // 11
        VertexFormat(corner + glm::vec3(2.05f * length, -0.2f * length, 3), color), // 12
        VertexFormat(corner + glm::vec3(0.875f * length, -0.9f * length, 3), color), // 13
    };

    Mesh* enemy = new Mesh(name);
    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 5,
        0, 5, 6,
        0, 6, 1,

        7, 8, 9,
        7, 9, 10,
        7, 10, 11,
        7, 11, 12,
        7, 12, 13,
        7, 13, 8

    };

    enemy->InitFromData(vertices, indices);
    return enemy;
}
