#pragma once

#include <string>
#include<vector>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace objects2D
{
    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateRectangle(const std::string &name, glm::vec3 leftBottomCorner, float width, float length, float distance, glm::vec3 color, bool fill = false);
    Mesh* CreateDiamond(const std::string &name, glm::vec3 leftBottomCorner, float length, float distanceHeight, float distanceWidth, float smallRectangleWidth,
    float smallRectangleDistance, glm::vec3 color, bool fill = false);
    Mesh* CreateHexagon(const std::string &name, glm::vec3 leftBottomCorner, float length, float distanceHeight, glm::vec3 color, bool fill = false);
    Mesh* CreateStar(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

struct Rectangle {
    Mesh *mesh;
    glm::vec3 color;
    glm::vec3 position;
    float width, height;
};


struct Square {
    Mesh *mesh;
    glm::vec3 color;
    glm::vec3 position;
    float squareSide;
};

struct Star {
    Mesh *mesh;
    glm::vec3 color;
    glm::vec3 position;
    bool collected;
    float radius;
};

struct Diamond {
    Mesh *mesh;
    glm::vec3 color;
    glm::vec3 position;
    glm::mat3 modelMatrix;
    int scoreDamage;
    int positionXStar;
    int positionYStar;
    bool startshooting, isDissapearing;
    float length;
    float width;
    Mesh *starMesh;
    glm::vector<struct Star> ammunition;
    //de vazut ce mai adaug
};

struct Hexagon {
    Mesh *mesh;
    glm::vec3 position;
    glm::vec3 color;
    glm::mat3 modelMatrix;
    bool isSeen;
    float length;
    float width;
    int lifeDamage;
    int life;
};
    struct Grid {
        struct Rectangle *rectangle;
        struct Square squares[3][3];
    };
    struct Backgroundfield {
        struct Grid *grid;
        struct Square boxes[4];
        struct Diamond diamonds[4];
        struct Square lives[3];
        std::vector<struct Star> score;
        struct Hexagon enemies[3][4];
        std::vector<struct Star> bonus;
    };

    struct User {
        int life;
        int score;
    };
}
