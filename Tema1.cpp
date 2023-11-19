#include "Tema1.h"

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



Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            struct Diamond newShooter;
            newShooter.position.x = 0;
            newShooter.position.y = 0;
            newShooter.modelMatrix = glm::mat3(1);
            newShooter.isDissapearing = false;
            newShooter.startshooting = false;
            newShooter.starTimer = 0;
            shootersOnBoard[i][j] = newShooter;
        }
    }

    translateXEnemeys = window->GetResolution().x;
    isDragging = false;
    freeze = 5;
    levelUp = 0;
    // red = 0.1f;
    // green = 0.05f;
    // blue = 0.2f;
    red = 0.1f;
    green = 0.05f;
    blue = 0.15f;
    cnt = 0;
    angleStar = 0;
    moveDiamond = false;
    Scene::Init();
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    //glClearColor(0.9f, 0.8f, 0.6f, 1.0f);
    //glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    //glClearColor(0, 0, 0, 1.0f);
    //glClearColor(0.1f, 0.05f, 0.15f, 1.0f); 
    //glClearColor(0.1f, 0.05f, 0.2f, 1.0f);  // Mov mai închis pentru nivel ușor    
    //glClearColor(0.05f, 0.1f, 0.15f, 1.0f);  // Albastru închis pentru nivel mediu
    //glClearColor(0.15f, 0.05f, 0.1f, 1.0f);  // Roșu închis pentru nivel dificil
    glClearColor(red, green, blue, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::deacrease_life() {
    player->life--;
    if (player->life == 0) {
        endGame = true;
    }
}

void Tema1::dissapear_shooter(float deltaTimeSeconds) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (shootersOnBoard[i][j].isDissapearing && shootersOnBoard[i][j].position.x != 0) {
                shootersOnBoard[i][j].length -= shootersOnBoard[i][j].length * 0.9;
                shootersOnBoard[i][j].width -= shootersOnBoard[i][j].length * 0.9;
                shootersOnBoard[i][j].modelMatrix *= Transform2D::Translate(deltaTimeSeconds * 850, deltaTimeSeconds * 850);
                shootersOnBoard[i][j].modelMatrix *= Transform2D::Scale(0.9f, 0.9f);
                RenderMesh2D(shootersOnBoard[i][j].mesh, shaders["VertexColor"], shootersOnBoard[i][j].modelMatrix);
                if (shootersOnBoard[i][j].length <= 0 || shootersOnBoard[i][j].width <= 0) {
                    //cout<<"incepe sa stearga shooterul"<<endl;
                    shootersOnBoard[i][j].isDissapearing = false;
                    shootersOnBoard[i][j].position.x = 0;
                    shootersOnBoard[i][j].position.y = 0;
                    shootersOnBoard[i][j].length = squareSide / 2 - diamondDistanceH;
                    shootersOnBoard[i][j].width =squareSide - diamondDistanceW - smallRectangleDistance;
                    shootersOnBoard[i][j].startshooting = false;
                    shootersOnBoard[i][j].starTimer = 0;
                    for (int i = 0; i < shootersOnBoard[i][j].ammunition.size(); i++) {
                        if (!shootersOnBoard[i][j].ammunition[i].isGoingForward) {
                            //cout<<"sterge steaua cu nr in dissapearing: "<<i<<endl;
                            shootersOnBoard[i][j].ammunition.erase(shootersOnBoard[i][j].ammunition.begin() + i, shootersOnBoard[i][j].ammunition.begin() + i + 1);
                        }
                    }
                }
            }
        }
    }  
}

void Tema1::dissapear_enemy(float deltaTimeSeconds) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < enemiesOnBoard[i].size(); j++) {
            if (enemiesOnBoard[i][j].life <= 0) {
                //cout<<"incepe sa stearga inamicul"<<endl;
                enemiesOnBoard[i][j].length -= enemiesOnBoard[i][j].length * 0.9;
                enemiesOnBoard[i][j].width -= enemiesOnBoard[i][j].width * 0.9;
                enemiesOnBoard[i][j].modelMatrix *= Transform2D::Translate(deltaTimeSeconds * 850, deltaTimeSeconds * 850);
                enemiesOnBoard[i][j].modelMatrix *= Transform2D::Scale(0.9f, 0.9f);
                RenderMesh2D(enemiesOnBoard[i][j].mesh, shaders["VertexColor"], enemiesOnBoard[i][j].modelMatrix);
                if (enemiesOnBoard[i][j].length <= 0 || enemiesOnBoard[i][j].width <= 0) {
                    //cout<<"a sters inamicul"<<endl;
                    enemiesOnBoard[i].erase(enemiesOnBoard[i].begin() + j);
                }
            }
        }
    }
    
}

void Tema1::RenderScene(float deltaTimeSeconds) {

    // MOVE SHOOTER, DRAG AND DROP---------------------------------------------
    float coordX = window->GetCursorPosition().x;
    float coordY = window->GetCursorPosition().y;
    if (isDragging) {
        shooterOnMove.position.x = coordX - squareSide / 2;
        shooterOnMove.position.y = window->GetResolution().y - coordY - squareSide / 2;
        modelMatrix = glm::mat3(1);
        modelMatrix *= Transform2D::Translate(shooterOnMove.position.x, shooterOnMove.position.y);
        RenderMesh2D(shooterOnMove.mesh, shaders["VertexColor"], modelMatrix);
    } 

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (shootersOnBoard[i][j].position.x != 0 && !shootersOnBoard[i][j].isDissapearing) {
                //cout<<"deseneaza shooterul"<<endl;
                shootersOnBoard[i][j].modelMatrix = glm::mat3(1);
                shootersOnBoard[i][j].modelMatrix *= Transform2D::Translate(shootersOnBoard[i][j].position.x, shootersOnBoard[i][j].position.y);
                RenderMesh2D(shootersOnBoard[i][j].mesh, shaders["VertexColor"], shootersOnBoard[i][j].modelMatrix);
                // LOAD AMMUNITION -------------------------------------------------------- 
                if (shootersOnBoard[i][j].startshooting) {
                    shootersOnBoard[i][j].starTimer -= deltaTimeSeconds;
                    //cout<<"timer: "<<shootersOnBoard[i][j].starTimer<<endl;
                    if (shootersOnBoard[i][j].starTimer < 0) {
                        struct Star star;
                        star.position.x = shootersOnBoard[i][j].positionXStar;
                        star.position.y = shootersOnBoard[i][j].positionYStar;
                        star.color = shootersOnBoard[i][j].color;
                        star.isGoingForward = false;
                        shootersOnBoard[i][j].ammunition.push_back(star);
                        shootersOnBoard[i][j].starTimer = 1.2;
                    }
                    //cout<<"sunt in total "<<shootersOnBoard[i][j].ammunition.size()<<" stele"<<endl;
                }
            }
            // MOVE AMMUNITION -------------------------------------------------------- 
            for (int k = shootersOnBoard[i][j].ammunition.size() - 1; k >= 0; k--) {
                //cout<<"misca steaua nr: "<<k<<endl;
                modelMatrix = glm::mat3(1);
                shootersOnBoard[i][j].ammunition[k].isGoingForward = true;
                shootersOnBoard[i][j].ammunition[k].position.x += 2;
                int cx = shootersOnBoard[i][j].ammunition[k].position.x + squareSide / 2 * 0.4;
                int cy = shootersOnBoard[i][j].ammunition[k].position.y + squareSide / 2 * 0.4;
                modelMatrix *= Transform2D::Translate(cx, cy);
                modelMatrix *= Transform2D::Rotate(angleStar);
                modelMatrix *= Transform2D::Translate(-cx, -cy);
                modelMatrix *= Transform2D::Translate(shootersOnBoard[i][j].ammunition[k].position.x, shootersOnBoard[i][j].ammunition[k].position.y);
                modelMatrix *= Transform2D::Scale(0.4, 0.4);
                RenderMesh2D(shootersOnBoard[i][j].starMesh, shaders["VertexColor"], modelMatrix);
                // COLLISION -------------------------------------------------------------------------------------------------------------------------
                for (int m = enemiesOnBoard[i].size() - 1; m >= 0; m--) {
                    if (enemiesOnBoard[i][m].color == shootersOnBoard[i][j].ammunition[k].color
                        && shootersOnBoard[i][j].ammunition.size() != 0 // daca e 0 mai trebuie sa faca load
                        && shootersOnBoard[i][j].ammunition[k].position.x + shootersOnBoard[i][j].ammunition[k].radius * 0.4 >= enemiesOnBoard[i][m].position.x) {
                       // cout<<"a sters steaua nr: "<<k<<"in total sunt: "<<shootersOnBoard[i][j].ammunition.size()<<endl;
                        shootersOnBoard[i][j].ammunition.erase(shootersOnBoard[i][j].ammunition.begin() + k, shootersOnBoard[i][j].ammunition.begin() + k + 1);
                        enemiesOnBoard[i][m].life--;
                        if (enemiesOnBoard[i][m].life <= 0) {
                            //cout<<"a omorat inamicul nu nr: "<<m<<endl;
                            shootersOnBoard[i][j].startshooting = false;
                            enemiesOnBoard[i][m].life = 0;
                        }
                    }
                }
                if (shootersOnBoard[i][j].ammunition[k].position.x > window->GetResolution().x) {
                    //cout<<"a sters steaua nr: "<<k<<"in total sunt: "<<shootersOnBoard[i][j].ammunition.size()<<endl;
                    shootersOnBoard[i][j].ammunition.erase(shootersOnBoard[i][j].ammunition.begin() + k, shootersOnBoard[i][j].ammunition.begin() + k + 1);
                }
            }
        }
    }
    //ENEMIES -----------------------------------------------------------------------------------------------------
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < enemiesOnBoard[i].size(); j++) {
            if (enemiesOnBoard[i][j].life > 0) {
                enemiesOnBoard[i][j].modelMatrix  = glm::mat3(1);
                enemiesOnBoard[i][j].position.x -= 1.2;
                enemiesOnBoard[i][j].modelMatrix  *= Transform2D::Translate(enemiesOnBoard[i][j].position.x, enemiesOnBoard[i][j].position.y);
                RenderMesh2D(enemiesOnBoard[i][j].mesh, shaders["VertexColor"], enemiesOnBoard[i][j].modelMatrix);
                if (enemiesOnBoard[i][j].position.x < 1600) {
                    for (int k = 0; k < 3; k++) {
                        if (shootersOnBoard[i][k].position.x != 0 && !shootersOnBoard[i][k].isDissapearing) {
                            float distance = shootersOnBoard[i][k].position.x + squareSide;
                            if (enemiesOnBoard[i][j].position.x + squareSide / 4 < distance - smallRectangleDistance 
                                && enemiesOnBoard[i][j].position.x + squareSide / 4 > shootersOnBoard[i][k].position.x + squareSide / 2) {
                                //cout<<"a murit shooterul"<<endl;
                                shootersOnBoard[i][k].isDissapearing = true;
                            } else {
                                if (shootersOnBoard[i][k].color == enemiesOnBoard[i][j].color) {
                                    //cout<<"incepe sa traga shooterul: "<<k<<endl;
                                    shootersOnBoard[i][k].startshooting = true;
                                }
                                if (shootersOnBoard[i][k].position.x + squareSide > enemiesOnBoard[i][j].position.x) {
                                    //cout<<"s-a oprit din tras shooterul: "<<k<<endl;
                                    shootersOnBoard[i][k].startshooting = false;
                                }
                            }
                        }
                    }
                }
                if (enemiesOnBoard[i][j].position.x < - squareSide) {
                    //cout<<"a disparut inamicul: "<<j<<endl;
                    deacrease_life();
                    enemiesOnBoard[i][j].position.x = window->GetResolution().x;
                    enemiesOnBoard[i].erase(enemiesOnBoard[i].begin() + j, enemiesOnBoard[i].begin() + j + 1);
                }
            }
        }
    }
}


void Tema1::Update(float deltaTimeSeconds)
{ 
    Scene::Update(deltaTimeSeconds);
    if (!endGame) {
        freeze -= deltaTimeSeconds;
        angleStar -= deltaTimeSeconds * 3;
        levelUp += deltaTimeSeconds;
        if (freeze < 0) {
            int i = rand() % 3;
            index_i = i;
            index_j = rand() % 4;
            enemiesOnBoard[index_i].push_back(background->enemies[index_i][index_j]);
            if (levelUp <= 60) {
                //easy
                freeze = rand() % 7 + 3;
            } else if (levelUp <= 150) {
                cout<<"medium"<<endl;
                //medium
                freeze = rand() % 3 + 2;
                // red = 0.05f;
                // green = 0.1f;
                // blue = 0.15f;
                red = 0.1f;
                green = 0.05f;
                blue = 0.2f;
            } else {
                cout<<"hard"<<endl;
                //hard
                freeze = rand() % 2 + 1;
                red = 0.15f;
                green = 0.05f;
                blue = 0.1f;
            }
        }

        RenderScene(deltaTimeSeconds);
        dissapear_shooter(deltaTimeSeconds);
        dissapear_enemy(deltaTimeSeconds);
    }
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{

}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
    
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (!endGame) {
        mouseY = window->GetResolution().y - mouseY; 
        if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
            for (int i = 0; i < 3; i++) {
                float posX = background->bonus[i].position.x;
                float posY = background->bonus[i].position.y;
                float radius = background->bonus[i].radius;
                if (mouseX > posX && mouseX < posX + radius
                    && mouseY > posY && mouseY < posY + radius) {
                    background->bonus[i].collected = true;
                    background->bonus[i].position.x = 0;
                    background->bonus[i].position.y = 0;
                    if (player->score < 8) {
                        player->score++;
                    }
                }
            }
        }
        if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_RIGHT)) {
            for (int i = 0; i < 4; i++) {
                float posX = background->boxes[i].position.x;
                float posY = background->boxes[i].position.y;
                float squareSide = background->boxes[i].squareSide;
                if (mouseX > posX && mouseX < posX + squareSide
                    && mouseY > posY && mouseY < posY + squareSide) {
                    isDragging = true;
                    shooterOnMove.color = background->diamonds[i].color;
                    shooterOnMove.position.x = mouseX;
                    shooterOnMove.position.y = mouseY;
                    shooterOnMove.mesh = background->diamonds[i].mesh;
                    shooterOnMove.starMesh = background->diamonds[i].starMesh;
                    shooterOnMove.scoreDamage = background->diamonds[i].scoreDamage;
                }
            }

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    float posX = background->grid->squares[i][j].position.x;
                    float posY =  background->grid->squares[i][j].position.y;
                    if (mouseX > posX && mouseX < posX + squareSide
                    && mouseY > posY && mouseY < posY + squareSide
                    && shootersOnBoard[j][i].position.x != 0) {
                        shootersOnBoard[j][i].isDissapearing = true;
                    }
                }
            }
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    mouseY = window->GetResolution().y - mouseY; 
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_RIGHT)) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                float gridX = background->grid->squares[i][j].position.x;
                float gridY = background->grid->squares[i][j].position.y;
                if (mouseX > gridX && mouseX < gridX + squareSide
                     && mouseY > gridY && mouseY < gridY + squareSide
                     && shootersOnBoard[j][i].position.x == 0
                     && shooterOnMove.scoreDamage <= player->score
                     && isDragging) {
                        shootersOnBoard[j][i].mesh = shooterOnMove.mesh;
                        shootersOnBoard[j][i].position.x = gridX;
                        shootersOnBoard[j][i].position.y = gridY;
                        shootersOnBoard[j][i].length =  squareSide / 2 - diamondDistanceH;
                        shootersOnBoard[j][i].width = squareSide - diamondDistanceW - smallRectangleDistance;
                        shootersOnBoard[j][i].color = shooterOnMove.color;
                        shootersOnBoard[j][i].scoreDamage = shooterOnMove.scoreDamage;
                        shootersOnBoard[j][i].positionXStar = shootersOnBoard[j][i].position.x + squareSide - smallRectangleDistance;
                        shootersOnBoard[j][i].positionYStar = shootersOnBoard[j][i].position.y + background->bonus[i].radius * 0.4 + squareSide / 7;
                        shootersOnBoard[j][i].starMesh = shooterOnMove.starMesh;
                        
                        player->score -= shooterOnMove.scoreDamage;
                        break;
                }
            }
        }
    }
    isDragging = false;
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{

}
