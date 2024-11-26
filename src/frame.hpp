#pragma once
#include <string>

#include "frame_unit.hpp"

namespace tren {

    /**
     * Draw rectangle using definition
     */
    void drawRectFilled(int x, int y, int w, int h, char ch);

    /**
     * Draw text on the screen
     */
    void drawText(int x, int y, const char* str);

    /**
     * Clear rectangle space
     */
    void clearRect(/*const RectDef& rectDef*/);

    /**
     * Clear virtual screen
     */
    void clear();

    /**
    * Draw terminal text based image
    */
    void drawImage(/*TODO draw image*/);

    /**
     * Draw pixel
     */
    void drawPixel(int x, int y, char ch);

}