#include "objects2D.h"

#include <vector>
#include <cmath>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* objects2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* objects2D::CreateRectangle(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float width,
    float length,
    float distance,
    glm::vec3 color,
    bool fill)
    {
    glm::vec3 corner = leftBottomCorner;
    float height = 3 * length + 2 * distance;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width, 0, 0), color),
        VertexFormat(corner + glm::vec3(width, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
    }

Mesh* objects2D::CreateDiamond(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    float distanceHeight,
    float distanceWidth,
    float smallRectangleWidth,
    float smallRectangleDistance,
    glm::vec3 color,
    bool fill)
    {
    glm::vec3 corner = leftBottomCorner;
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(length/2, distanceHeight, 2), color), // 0
        VertexFormat(corner + glm::vec3(distanceWidth, length / 2, 2), color), // 1
        VertexFormat(corner + glm::vec3(length / 2, length - distanceHeight, 2), color), // 2
        VertexFormat(corner + glm::vec3(length - distanceWidth, length / 2, 2), color), // 3

        //up tr
        VertexFormat(corner + glm::vec3(length / 2, (length + smallRectangleWidth) / 2, 2), color), // 4
        VertexFormat(corner + glm::vec3(length - distanceWidth, (length + smallRectangleWidth) / 2, 2), color), // 5
        VertexFormat(corner + glm::vec3(length - distanceWidth, length / 2, 2), color), // 6

        //down tr
        VertexFormat(corner + glm::vec3(length / 2 , (length - smallRectangleWidth) / 2, 2), color), // 7
        VertexFormat(corner + glm::vec3(length - distanceWidth,  (length - smallRectangleWidth) / 2, 2), color), // 8
        VertexFormat(corner + glm::vec3(length - distanceWidth, length / 2, 2), color), // 9


        // Rectangle tr
        VertexFormat(corner + glm::vec3(length - smallRectangleDistance, (length + smallRectangleWidth) / 2, 2), color),  // dr sus  10   
        VertexFormat(corner + glm::vec3(length - smallRectangleDistance, (length - smallRectangleWidth) / 2, 2), color), // dr jos 11
    };

    Mesh* diamond = new Mesh(name);
    std::vector<unsigned int> indices = {  
    // Diamond
    0, 1, 2, 3,
    // Upper triangle
    4, 5, 3,
    // Lower triangle
    7, 8, 3,
    // Rectangle tr 1
    5, 10, 3,
    // Rectangle tr 2
    11, 8, 3,
    // Rectangle tr 3
    10, 11, 3,
    };

    //std::vector<unsigned int> indices = { 0, 1, 2, 3, 4, 5};


    if (!fill) {
        diamond->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    diamond->InitFromData(vertices, indices);
    return diamond;
    }   

Mesh* objects2D::CreateHexagon(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    float distanceHeight,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;
    glm::vec3 color1 = color;
    glm::vec3 color2 = glm::vec3(0, 0.8, 1);
    float diff = 18;
    float center = length / 2;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(length / 2, length - 4 * distanceHeight / 3, 1), color1), // 0
        VertexFormat(corner + glm::vec3(4 * length / 5, 2 * length / 3, 1), color1), // 1
        VertexFormat(corner + glm::vec3(4 * length / 5, length / 3, 1), color1), // 2
        VertexFormat(corner + glm::vec3(length / 2, 4 * distanceHeight / 3, 1), color1), // 3
        VertexFormat(corner + glm::vec3(length / 5, length / 3, 1), color1), // 4
        VertexFormat(corner + glm::vec3(length / 5, 2 * length / 3, 1), color1), // 5
        VertexFormat(corner + glm::vec3(length / 2, length / 2, 1), color1), // 6

        VertexFormat(corner + glm::vec3(length / 2, length - 4 * distanceHeight / 3 - diff, 2), color2), // 7
        VertexFormat(corner + glm::vec3(4 * length / 5 - diff, 2 * length / 3 - diff + 7, 2), color2), // 8
        VertexFormat(corner + glm::vec3(4 * length / 5 - diff, length / 3 + diff - 7, 2), color2), // 9
        VertexFormat(corner + glm::vec3(length / 2, 4 * distanceHeight / 3 + diff, 2), color2), // 10
        VertexFormat(corner + glm::vec3(length / 5 + diff, length / 3 + diff - 7, 2), color2), // 11
        VertexFormat(corner + glm::vec3(length / 5 + diff, 2 * length / 3 - diff + 7, 2), color2), // 12
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = {
        // first hexagon
        0, 1, 6,
        1, 2, 6,
        2, 3, 6,
        3, 4, 6,
        4, 5, 6,
        5, 0, 6,

        // second hexagon
        7, 8, 6,
        8, 9, 6,
        9, 10, 6,
        10, 11, 6,
        11, 12, 6,
        12, 7, 6,
    };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* objects2D::CreateStar(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;
    float r = length / 6;
    std::vector<VertexFormat> vertices =
    {
    //Internal hexagon
    VertexFormat(corner + glm::vec3(5 * r / 2, 15 * r / 4, 3), color), // 0
    VertexFormat(corner + glm::vec3(7 * r / 2, 15 * r / 4, 3), color), // 1
    VertexFormat(corner + glm::vec3(4 * r, 11 * r / 4, 3), color), // 2
    VertexFormat(corner + glm::vec3(3 * r, 2 * r, 3), color), // 3
    VertexFormat(corner + glm::vec3(2 * r, 11 * r / 4, 3), color), // 4

    //External hexagon
    VertexFormat(corner + glm::vec3(3 * r, 6 * r, 3), color), // 5
    VertexFormat(corner + glm::vec3(6 * r - r / 8, 4 * r - r / 16, 3), color), // 6
    VertexFormat(corner + glm::vec3(19 * r / 4, r / 2, 3), color), // 7
    VertexFormat(corner + glm::vec3(5 * r / 4, r / 2, 3), color), // 8
    VertexFormat(corner + glm::vec3(r / 8, 4 * r - r / 16, 3), color), // 9
    };
    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = {
    // interior hexagon
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 1,
        1, 2, 3,
        1, 3, 4,
    // exterior triangles
        0, 5, 1,
        1, 6, 2,
        2, 7, 3,
        3, 8, 4,
        4, 9, 0,
    };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}
