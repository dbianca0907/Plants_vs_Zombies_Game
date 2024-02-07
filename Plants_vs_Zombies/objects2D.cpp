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
    glm::vec3 color2 = glm::vec3(0.4f, 0.2f, 0.6f);
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

Mesh* objects2D::CreateEND(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
     glm::vec3 corner = leftBottomCorner;
    //float distance = length / 16;
    float start_n = length - length / 8;
    float start_d = start_n + length + length / 8;
    float aux = length - (length / 7);
    Mesh* square = new Mesh(name);
    std::vector<VertexFormat> vertices = {
    //"E"
    VertexFormat(corner + glm::vec3(length / 4, length / 7, 5), color), // 0
    VertexFormat(corner + glm::vec3(3 * length / 8, length / 7, 5), color), // 1
    VertexFormat(corner + glm::vec3(3 * length / 8, 6 * length / 7, 5), color), // 2
    VertexFormat(corner + glm::vec3(length / 4, 6 * length / 7, 5), color), // 3

    VertexFormat(corner + glm::vec3(3 * length / 8, 5 * length / 7, 5), color), // 4
    VertexFormat(corner + glm::vec3(3 * length / 4, 5 * length / 7, 5), color), // 5
    VertexFormat(corner + glm::vec3(3 * length / 4, 6 * length / 7, 5), color), // 6
    VertexFormat(corner + glm::vec3(3 * length / 8, 6 * length / 7, 5), color), // 7

    VertexFormat(corner + glm::vec3(3 * length / 8, 3 * length / 7, 5), color), // 8
    VertexFormat(corner + glm::vec3(length / 2, 3 * length / 7, 5), color), // 9
    VertexFormat(corner + glm::vec3(length / 2, 4 * length / 7, 5), color), // 10
    VertexFormat(corner + glm::vec3(3 * length / 8, 4 * length / 7, 5), color), // 11

    VertexFormat(corner + glm::vec3(3 * length / 8, length / 7, 5), color), // 12
    VertexFormat(corner + glm::vec3(3 * length / 4, length / 7, 5), color), // 13
    VertexFormat(corner + glm::vec3(3 * length / 4, 2 * length / 7, 5), color), // 14
    VertexFormat(corner + glm::vec3(3 * length / 8, 2 * length / 7, 5), color), // 15

    //"N"
    VertexFormat(corner + glm::vec3(start_n  + length / 8, length / 7, 5), color), // 16
    VertexFormat(corner + glm::vec3(start_n + length / 4, length / 7, 5), color), // 17
    VertexFormat(corner + glm::vec3(start_n + length / 4, 6 * length / 7, 5), color), // 18
    VertexFormat(corner + glm::vec3(start_n + length / 8, 6 * length / 7, 5), color), // 19

    VertexFormat(corner + glm::vec3(start_n + 5 * length / 8 + length / 16, length / 7, 5), color), // 20
    VertexFormat(corner + glm::vec3(start_n + 6 * length / 8, 2 * length / 7, 5), color), // 21
    VertexFormat(corner + glm::vec3(start_n + 2 * length / 8 + length / 16, 6 * length / 7, 5), color), // 22
    VertexFormat(corner + glm::vec3(start_n + length / 4, 5 * length / 7, 5), color), // 23


    VertexFormat(corner + glm::vec3(start_n + 6 * length / 8, length / 7, 5), color), // 24
    VertexFormat(corner + glm::vec3(start_n + 7 * length / 8, length / 7, 5), color), // 25
    VertexFormat(corner + glm::vec3(start_n + 7 * length / 8, 6 * length / 7, 5), color), // 26
    VertexFormat(corner + glm::vec3(start_n + 6 * length / 8, 6 * length / 7, 5), color), // 27


    // "D"
    // VertexFormat(corner + glm::vec3(start_d + length / 8, length / 7, 5), color), // 28
    // VertexFormat(corner + glm::vec3(start_d + length / 4, length / 7, 5), color), // 29
    // VertexFormat(corner + glm::vec3(start_d + length / 4, 6 * length / 7, 5), color), // 30
    // VertexFormat(corner + glm::vec3(start_d + length / 8, 6 * length / 7, 5), color), // 31
    VertexFormat(corner + glm::vec3(start_d, length / 7, 5), color), // 28
    VertexFormat(corner + glm::vec3(start_d + length / 8, length / 7, 5), color), // 29
    VertexFormat(corner + glm::vec3(start_d + length / 8, 6 * length / 7, 5), color), // 30
    VertexFormat(corner + glm::vec3(start_d, 6 * length / 7, 5), color), // 31

    VertexFormat(corner + glm::vec3(start_d + length / 8, 6 * aux / 7 , 5), color), // 32
    VertexFormat(corner + glm::vec3(start_d + 2 * length / 8, 6 * aux / 7, 5), color), // 33
    VertexFormat(corner + glm::vec3(start_d + length / 4 + length / 16, aux, 5), color), // 34
    
    VertexFormat(corner + glm::vec3(start_d + 3 * length / 8, 5 * aux / 7, 5), color), // 35
    VertexFormat(corner + glm::vec3(start_d + 4 * length / 8, 6 * aux / 7 - aux / 14, 5), color), // 36

    VertexFormat(corner + glm::vec3(start_d + 3 * length / 8, 3 * aux / 7, 5), color), // 37
    VertexFormat(corner + glm::vec3(start_d + 4 * length / 8, 2 * aux / 7 + aux / 14, 5), color), // 38
    VertexFormat(corner + glm::vec3(start_d + 2 * length / 8, 2 * length / 7, 5), color), // 39
    VertexFormat(corner + glm::vec3(start_d + length / 4 + length / 16, length / 7, 5), color), // 40
    VertexFormat(corner + glm::vec3(start_d + length / 8, 2 * length / 7, 5), color), // 41

    };

    std::vector<unsigned int> indices = {
        // First vertical bar
        0, 1, 2,
        2, 3, 0,

        // First horizontal bar
        4, 5, 6,
        6, 7, 4,

        // Middle vertical bar
        8, 9, 10,
        10, 11, 8,

        // Second horizontal bar
        12, 13, 14,
        14, 15, 12,

        // "N"
        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20,

        23, 22, 18,
        20, 21, 24,

        24, 25, 26,
        26, 27, 24,

        // Indices for "D"
        28, 29, 30,
        30, 31, 28,

        32, 33, 34,
        34, 30, 32,

        35, 36, 34,
        34, 33, 35,

        37, 38, 36,
        36, 35, 37,
        
        39, 40, 38,
        38, 37, 39,

        29, 40, 39,
        39, 41, 29,
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
