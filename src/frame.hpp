#pragma once
#include <string>

#include "frame_unit.hpp"

namespace tren {

    struct TextDef {
        std::string content = "";
        tren::color color = FUNIT_DEFAULT_FG_COLOR;
        tren::color backgroundColor = FUNIT_DEFAULT_BG_COLOR;
        int x = 0;
        int y = 0;
    };

    struct RectDef
    {
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;
        char ch = FUNIT_DEFAULT_CHAR;
        tren::color color = FUNIT_DEFAULT_FG_COLOR;
        tren::color backgroundColor = FUNIT_DEFAULT_BG_COLOR;
    };

    struct PixelDef
    {
        int x = 0;
        int y = 0;
        tren::FrameUnit unit;
    };

    /**
     * Draw rectangle using definition
     */
    void drawRect(const RectDef& rectDef);

    /**
     * Draw text on the screen
     */
    void drawText(const TextDef& textDef);

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
     * Set pixel
     */
    void drawPixel(const tren::PixelDef& frameUnit);

}