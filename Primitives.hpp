#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


enum Role {
    GRID,
    BOX,
    COLLECTED_STARS,
    ENEMY,
    LIFE,
    SHOOTER,
};

struct Rectangle {
    Mesh *mesh;
    Role role;
    glm::vec3 color;
    glm::vec3 position;
};

struct Diamond {
    Mesh *mesh;
    Role role;
    glm::vec3 color;
    glm::vec3 position;
};

struct Hexagon {
    Mesh *mesh;
    Role role;
    glm::vec3 color;
    glm::vec3 position;
};

struct Star {
    Mesh *mesh;
    Role role;
    glm::vec3 color;
    glm::vec3 position;
};

struct Grid {
    struct Rectangle rectangle;
    struct Rectangle **squares;
};

struct Scene {
    struct Rectangle *boxes;
    struct Diamond *diamonds;
    struct Rectangle *lives;
    struct Star *score;
};