#include "Scene.h"

#include <vector>
#include <iostream>
#include <random>

#include "objects2D.h"
#include "Transform2D.h"

using namespace std;
using namespace m1;

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

void Scene::Init()
{   
    background = new Backgroundfield();
    player = new User();
    background->grid = new Grid();
    glm::vec3 corner = glm::vec3(0, 0, 0);
    squareSide = 150;
    //cout<<"Size fereastra: "<<window->GetResolution().x<< " "<<window->GetResolution().y<<endl;
    squaresDistance = 54;
    rectangleWidth = squareSide / 2;
    rectangleHeight = 3 * squareSide + 2 * squaresDistance;

    diamondDistanceH = squareSide / 7;
    diamondDistanceW = squareSide / 3;
    smallRectangleWidth = squareSide / 7;
    smallRectangleDistance = squareSide / 10;

    rx = corner.x + 33;
    ry = corner.y + 33;

    player->life = 3;
    player->score = 5;
    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;    

    //Initialize delay and counter for stars
    delay_stars = 10;
    timer_stars = 10;

    // Initialize angularStep
    angularStep = 0;

    Mesh* square1 = objects2D::CreateSquare("square1", corner, squareSide, glm::vec3(0, 1, 0), true);
    AddMeshToList(square1);

    Mesh* life = objects2D::CreateSquare("life", corner, squareSide, glm::vec3(1, 0, 0), true);
    AddMeshToList(life);

    Mesh* mainRectangle = objects2D::CreateRectangle("main_rectangle", corner, rectangleWidth, squareSide, squaresDistance, glm::vec3(1, 0, 0), true);
    AddMeshToList(mainRectangle);

    for (int i = 0; i < 4; i++) {
        struct Diamond diamond;
        background->diamonds[i] = diamond;
    }
    background->diamonds[0].color = glm::vec3(1, 0.7, 0);
    background->diamonds[0].scoreDamage = 1;
    background->diamonds[1].color = glm::vec3(0, 0, 1);
    background->diamonds[1].scoreDamage = 2;
    background->diamonds[2].color = glm::vec3(1, 1, 0);
    background->diamonds[2].scoreDamage = 2;
    background->diamonds[3].color = glm::vec3(1, 0, 1);
    background->diamonds[3].scoreDamage = 3;


    background->diamonds[0].mesh = objects2D::CreateDiamond("diamond", corner, squareSide, diamondDistanceH, diamondDistanceW, smallRectangleWidth, smallRectangleDistance, background->diamonds[0].color, true);
    AddMeshToList(background->diamonds[0].mesh);

    background->diamonds[1].mesh = objects2D::CreateDiamond("diamond1", corner, squareSide, diamondDistanceH, diamondDistanceW, smallRectangleWidth, smallRectangleDistance, background->diamonds[1].color, true);
    AddMeshToList(background->diamonds[1].mesh);

    background->diamonds[2].mesh = objects2D::CreateDiamond("diamond2", corner, squareSide, diamondDistanceH, diamondDistanceW, smallRectangleWidth, smallRectangleDistance, background->diamonds[2].color, true);
    AddMeshToList(background->diamonds[2].mesh);

    background->diamonds[3].mesh = objects2D::CreateDiamond("diamond3", corner, squareSide, diamondDistanceH, diamondDistanceW, smallRectangleWidth, smallRectangleDistance, background->diamonds[3].color, true);
    AddMeshToList(background->diamonds[3].mesh);

    Mesh *hex1 = objects2D::CreateHexagon("hexagon1", corner, squareSide, diamondDistanceH, glm::vec3(1, 0.7, 0), true);
    AddMeshToList(hex1);

    Mesh *hex2 = objects2D::CreateHexagon("hexagon2", corner, squareSide, diamondDistanceH, glm::vec3(0, 0, 1), true);
    AddMeshToList(hex2);

    Mesh *hex3 = objects2D::CreateHexagon("hexagon3", corner, squareSide, diamondDistanceH, glm::vec3(1, 1, 0), true);
    AddMeshToList(hex3);

    Mesh *hex4 = objects2D::CreateHexagon("hexagon3", corner, squareSide, diamondDistanceH, glm::vec3(1, 0, 1), true);
    AddMeshToList(hex4);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            struct Hexagon hexagon;
            hexagon.modelMatrix = glm::mat3(1);
            hexagon.position.x = window->GetResolution().x;
            hexagon.position.y = ry + i * (squareSide + squaresDistance);
            hexagon.isSeen = false;
            hexagon.length = 3 * squareSide / 5;
            hexagon.width = squareSide - 2 * diamondDistanceH;
            switch(j) {
                case 0:
                    hexagon.mesh = hex1;
                    hexagon.lifeDamage = 1;
                    hexagon.life = 1;
                    hexagon.color = background->diamonds[0].color;
                    break;
                case 1:
                    hexagon.mesh = hex2;
                    hexagon.lifeDamage = 2;
                    hexagon.life = 2;
                    hexagon.color = background->diamonds[1].color;
                    break;
                case 2:
                    hexagon.mesh = hex3;
                    hexagon.lifeDamage = 2;
                    hexagon.life = 2;
                    hexagon.color = background->diamonds[2].color;
                    break;
                case 3:
                    hexagon.mesh = hex4;
                    hexagon.lifeDamage = 3;
                    hexagon.life = 3;
                    hexagon.color = background->diamonds[3].color;
                    break;
            }
            background->enemies[i][j] = hexagon;
        }
    }

    Mesh* star = objects2D::CreateStar("star", corner, squareSide, glm::vec3(0.5, 0.5, 0.5), true);
    AddMeshToList(star);

    background->diamonds[0].starMesh = objects2D::CreateStar("star0", corner, squareSide,  background->diamonds[0].color, true);
    AddMeshToList(background->diamonds[0].starMesh);

    background->diamonds[1].starMesh = objects2D::CreateStar("star1", corner, squareSide,  background->diamonds[1].color, true);
    AddMeshToList( background->diamonds[1].starMesh);

    background->diamonds[2].starMesh = objects2D::CreateStar("star2", corner, squareSide,  background->diamonds[2].color, true);
    AddMeshToList( background->diamonds[2].starMesh);

    background->diamonds[3].starMesh = objects2D::CreateStar("star3", corner, squareSide,  background->diamonds[3].color, true);
    AddMeshToList(background->diamonds[3].starMesh);

    Mesh* bonus = objects2D::CreateStar("bonus", corner, squareSide, glm::vec3(0.5, 0.5, 1), true);
    AddMeshToList(bonus);

    for (int i = 0; i < 3; i++) {
        struct Star bonus;
        bonus.collected = false;
        bonus.position = glm::vec3(0, 0 ,0);
        bonus.radius = squareSide / 2;
        background->bonus.push_back(bonus);
    }

    for (int i = 0; i < 3; i++) {
        background->bonus[i].mesh = bonus;
    }


    Mesh* box = objects2D::CreateSquare("box", corner, squareSide, glm::vec3(1, 1, 1), false);
    AddMeshToList(box);
}



void Scene::Update(float deltaTimeSeconds)
{   
    float aux;
    // GRID ------------------------------------------------------------
    // rectangle
    modelMatrix = glm::mat3(1);
    modelMatrix *= Transform2D::Translate(rx, ry);
    struct Rectangle rectangle;
    rectangle.mesh = meshes["main_rectangle"];
    rectangle.color = glm::vec3(1, 0, 0);
    rectangle.position = glm::vec3(rx, ry, 0);
    rectangle.width = rectangleWidth;
    rectangle.height = rectangleHeight;
    background->grid->rectangle = &rectangle;
    RenderMesh2D(meshes["main_rectangle"], shaders["VertexColor"], modelMatrix);

    // squares
        for (int j = 0; j < 3; j++) {
            for (int i = 0; i < 3; i++) {
                if (i == 0) {
                    translateX = rx + rectangleWidth + squaresDistance;
                 } else {
                translateX = rx + (i + 1) * squaresDistance + (2 * i + 1) * squareSide / 2;
             }
            modelMatrix = glm::mat3(1);
            translateY = ry + j * (squareSide + squaresDistance);
            struct Square square;
            square.mesh = meshes["square1"];
            square .color = glm::vec3(0, 1, 0);
            square .position = glm::vec3(translateX, translateY, 0);
            square .squareSide = squareSide;
            background->grid->squares[i][j] = square;
            //cout<<"Grid pe indecsii "<<i<<" "<<j<<" "<<background->grid->squares[i][j].position.x<<" "<<background->grid->squares[i][j].position.y<<endl;
            modelMatrix *= Transform2D::Translate(translateX, translateY);
            RenderMesh2D(background->grid->squares[i][j].mesh, shaders["VertexColor"], modelMatrix);
        }
    }

    //BOXES ---------------------------------------------------------------
    boxDistance = rx + rectangleWidth;
    translateY = ry + rectangleHeight + squareSide;
    for (int i = 1; i <= 4; i++) {
        modelMatrix = glm::mat3(1);
        translateX = i * boxDistance + (i - 1) * squareSide;
        struct Square square;
        square.mesh = meshes["box"];
        square.color = glm::vec3(1, 1, 1);
        square.position = glm::vec3(translateX, translateY, 0);
        square.squareSide = squareSide;
        background->boxes[i - 1] = square;
        modelMatrix *= Transform2D::Translate(translateX, translateY);
        RenderMesh2D( background->boxes[i - 1].mesh, shaders["VertexColor"], modelMatrix);
    }

    //DIAMONDS -------------------------------------------------------

    for (int i = 0; i < 4; i++) {
        modelMatrix = glm::mat3(1);
        translateX = (i + 1) * boxDistance + i * squareSide;
        background->diamonds[i].position = glm::vec3(translateX, translateY, 0);
        modelMatrix *= Transform2D::Translate(translateX, translateY);
        RenderMesh2D(background->diamonds[i].mesh, shaders["VertexColor"], modelMatrix);
    }

    // LIVES -----------------------------------------------------------
    aux = translateX + squareSide + 2 * boxDistance / 3;
    if (player->life > 0) {
        struct Square life;
        translateY = ry + rectangleHeight + 5 * squareSide / 3 - 0.4 * squareSide;
        modelMatrix = glm::mat3(1);
        translateX += squareSide + 2 * boxDistance / 3;
        life.mesh = meshes["life"];
        life.color = glm::vec3(1, 1, 1);
        life.position = glm::vec3(translateX, translateY, 0);
        background->lives[0] = life;
        //aux = translateX;
        modelMatrix *= Transform2D::Translate(translateX, translateY);
        modelMatrix *= Transform2D::Scale(0.7, 0.7);
        RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
    }
    for (int i = 1; i < player->life; i++) {
        struct Square life;
        modelMatrix = glm::mat3(1);
        translateX += 0.7 * squareSide + 2 * boxDistance / 3;
        life.mesh = meshes["life"];
        life.color = glm::vec3(1, 1, 1);
        life.position = glm::vec3(translateX, translateY, 0);
        background->lives[i] = life;
        modelMatrix *= Transform2D::Translate(translateX, translateY);
        modelMatrix *= Transform2D::Scale(0.7, 0.7);
        RenderMesh2D(background->lives[i].mesh, shaders["VertexColor"], modelMatrix);
    }

    // DAMAGE -----------------------------------------------------------
    translateY = ry + rectangleHeight + squareSide - 0.4 * squareSide;
    float radius = 0.4 * 2 * squareSide / 3;
    float star_length = 0.4 * 23 * squareSide / 24;

     //first box
    modelMatrix = glm::mat3(1);
    translateX = boxDistance - radius / 3;
    modelMatrix *= Transform2D::Translate(translateX, translateY);
    modelMatrix *= Transform2D::Scale(0.4, 0.4);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    // second box
    modelMatrix = glm::mat3(1);
    translateX = 2 * boxDistance + squareSide - radius / 2;
    modelMatrix *= Transform2D::Translate(translateX, translateY);
    modelMatrix *= Transform2D::Scale(0.4, 0.4);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    translateX +=  star_length;
    modelMatrix *= Transform2D::Translate(translateX, translateY);
    modelMatrix *= Transform2D::Scale(0.4, 0.4);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    //third box
    modelMatrix = glm::mat3(1);
    translateX = 3 * boxDistance + 2 * squareSide - radius / 2;
    modelMatrix *= Transform2D::Translate(translateX, translateY);
    modelMatrix *= Transform2D::Scale(0.4, 0.4);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    translateX +=  star_length;
    modelMatrix *= Transform2D::Translate(translateX, translateY);
    modelMatrix *= Transform2D::Scale(0.4, 0.4);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    //fourth box
    modelMatrix = glm::mat3(1);
    translateX = 4 * boxDistance + 3 * squareSide - radius / 2;
    modelMatrix *= Transform2D::Translate(translateX, translateY);
    modelMatrix *= Transform2D::Scale(0.4, 0.4);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    translateX +=  star_length;
    modelMatrix *= Transform2D::Translate(translateX, translateY);
    modelMatrix *= Transform2D::Scale(0.4, 0.4);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    translateX +=  star_length;
    modelMatrix *= Transform2D::Translate(translateX, translateY);
    modelMatrix *= Transform2D::Scale(0.4, 0.4);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

     // SCORE -----------------------------------------------------------
    if (player->score != 0) {
        modelMatrix = glm::mat3(1);
        translateX = aux  - radius / 2;
        translateY = ry + rectangleHeight + squareSide / 2 + radius;
        modelMatrix *= Transform2D::Translate(translateX, translateY);
        modelMatrix *= Transform2D::Scale(0.4, 0.4);
        struct Star score;
        score.color = glm::vec3(0.5, 0.5, 0.5);
        score.mesh = meshes["star"];
        score.position = glm::vec3(translateX, translateY, 0);
        background->score.push_back(score);
        RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
    }

    for (int i = 1; i <= player->score - 1; i++) {
        translateX +=  star_length;
        modelMatrix = glm::mat3(1);
        struct Star score;
        score.color = glm::vec3(0.5, 0.5, 0.5);
        score.mesh = meshes["star"];
        score.position = glm::vec3(translateX, translateY, 0);
        background->score.push_back(score);
        modelMatrix *= Transform2D::Translate(translateX, translateY);
        modelMatrix *= Transform2D::Scale(0.4, 0.4);
        RenderMesh2D(background->score[i].mesh, shaders["VertexColor"], modelMatrix);
    }

    //BONUS -----------------------------------------------------------
    delay_stars -= deltaTimeSeconds * 0.8;
  
    for (int i = 0; i < 3; i++) {
        if (!background->bonus[i].collected) {
            if (background->bonus[i].position.x == 0
                && background->bonus[i].position.y == 0) {
                int aux = window->GetResolution().x - 3 * squareSide;
                translateX = rand() % aux;
                translateY = rand() % window->GetResolution().y;
                background->bonus[i].position = glm::vec3(translateX, translateY, 0);
            }
                modelMatrix = glm::mat3(1);
                modelMatrix *= Transform2D::Translate( background->bonus[i].position.x,  background->bonus[i].position.y);
                modelMatrix *= Transform2D::Scale(0.3, 0.3);
                RenderMesh2D(background->bonus[i].mesh, shaders["VertexColor"], modelMatrix);
        }
    }

    if (delay_stars <= 0) {
        delay_stars = 10;
        for (int i = 0; i < 3; i++) {
            background->bonus[i].collected = false;
        }
    }
}