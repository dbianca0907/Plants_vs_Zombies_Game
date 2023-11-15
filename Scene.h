#pragma once

#include "components/simple_scene.h"
#include "objects2D.h"
using namespace objects2D;


namespace m1
{ 
    class Scene : public gfxc::SimpleScene {
        public:
        void Init()override;
        void Update(float deltaTimeSeconds)override;

        protected:
        Backgroundfield *background;
        User *player;
        struct Star stars[4];
        float cx, cy;
        float rx, ry, rectangleWidth, rectangleHeight;
        float smallRectangleWidth, smallRectangleDistance;
        float squaresDistance, squareSide;
        float diamondDistanceH, diamondDistanceW;
        float boxDistance;
        float delay_stars, timer_stars;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float translateXEnemeys;
        float scaleX, scaleY;
        float angularStep;
    };
}
