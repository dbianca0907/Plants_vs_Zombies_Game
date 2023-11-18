#pragma once

#include <map>
#include "components/simple_scene.h"
#include "Scene.h"

namespace m1
{
    class Tema1 : public Scene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices);
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        void RenderScene(float deltaTimeSeconds);
        void deacrease_life();
        void dissapear_shooter(float deltaTimeSeconds);
        void dissapear_enemy(float deltaTimeSeconds);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        bool isDragging, moveDiamond, changeRes;
        float index, initialCursorX, initialCursorY;
        GLenum cullFace;
        GLenum polygonMode;
        float resolutionX, resolutionY, offsetX, offsetY;
        float starTimeCounter;
        int previous_timer, same_i, same_j;
        float angleStar, dissapearTimeCounterX, dissapearTimeCounterY;
        std::map<int, std::vector<struct Hexagon>> enemiesOnBoard;
       // std::map<int, std::vector<struct Diamond>> shootersOnBoard;
         struct Diamond shootersOnBoard[3][3];
        int cnt;
        float freeze, translate_star;
        int index_i, index_j;
        struct Diamond shooterOnMove;
    };
}   // namespace m1
