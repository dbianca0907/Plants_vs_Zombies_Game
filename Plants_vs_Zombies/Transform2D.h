#pragma once

#include "utils/glm_utils.h"


namespace Transform2D
{
    // Translate matrix
    inline glm::mat3 Translate(float translateX, float translateY)
    {
        return glm::mat3( 
        	 1,  0, 0,     // coloana 1 in memorie 
		 0,  1, 0,     // coloana 2 in memorie 
		translateX, translateY, 1);    // coloana 3 in memorie 
    }

    // Scale matrix
    inline glm::mat3 Scale(float scaleX, float scaleY)
    {
         return glm::transpose(
                  glm::mat3(scaleX, 0, 0,
                            0, scaleY, 0,
                            0, 0, 1)
        );
    }

    // Rotate matrix
    inline glm::mat3 Rotate(float radians)
    {
        return glm::transpose(
                glm::mat3(cos(radians), -sin(radians), 0,
                          sin(radians), cos(radians), 0,
                          0, 0, 1)
        );

    }
}   // namespace transform2D
