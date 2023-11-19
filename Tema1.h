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
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void RenderScene(float deltaTimeSeconds);
        void deacrease_life();
        void dissapear_shooter(float deltaTimeSeconds);
        void dissapear_enemy(float deltaTimeSeconds);
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        bool isDragging;
        float levelUp;
        float easy, medium, hard;
        float red, green, blue;
        float angleStar;
        std::map<int, std::vector<struct Hexagon>> enemiesOnBoard;
        struct Diamond shootersOnBoard[3][3];
        float freeze;
        int index_i, index_j;
        struct Diamond shooterOnMove;
    };
}   // namespace m1
