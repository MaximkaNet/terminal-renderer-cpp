#include "frame.hpp"
#include "resources.hpp"

void tren::drawRect(const tren::RectDef& rectDef) {
    int frame_width = tren::getBufferWidth();
    int frame_height = tren::getBufferHeight();

    int width = rectDef.width;
    int height = rectDef.height;

    int pos_x = rectDef.x;
    int pos_y = rectDef.y;

    for (int j = 0; j < height; j++) {
        if (pos_y > frame_height - 1) break;
        else if (pos_y < 0) continue;
        for (int i = 0; i < width; i++) {
            pos_x = rectDef.x + i;
            // Pixel by x axis on screen?
            if (pos_x > frame_width - 1) break;
            else if (pos_x < 0) continue;

            FrameUnit f_unit = { rectDef.ch, rectDef.backgroundColor, rectDef.color };

            int pos = pos_x + pos_y * frame_width;
            tren::getVirtualBuffer()[pos] = f_unit;
        }
    }
}

void tren::drawText(const tren::TextDef& textDef) {

    // TODO throw exception here?
    if (textDef.content.empty()) return;

    int pos_x = textDef.x;
    int pos_y = textDef.y;
    for (const char ch : textDef.content) {
        if (ch == '\n') {
            pos_y++;
            pos_x = textDef.x;
            continue;
        }
        if (pos_x > tren::getBufferWidth() - 1 || pos_x < 0 || pos_y < 0) continue;
        if (pos_y > tren::getBufferHeight() - 1) break;

        FrameUnit unit = { ch, textDef.backgroundColor, textDef.color };

        int pos = pos_y * tren::getBufferWidth() + pos_x;
        tren::getVirtualBuffer()[pos] = unit;
        pos_x++;
    }
}

void tren::clear() {
    int size = tren::getBufferWidth() * tren::getBufferHeight();
    tren::FrameUnit* buff_ptr = tren::getVirtualBuffer();
    for (int i = 0; i < size; i++)
    {
        buff_ptr[i] = tren::FrameUnit();
    }
}

void tren::clearRect(/*const tren::RectDef& rectDef*/) {
    throw std::exception("Not implemented yet");
}

void tren::drawImage() {
    //    unsigned int w = img.get_width();
    //    unsigned int h = img.get_height();
    //    auto img_units = img.get_frame_units();
    //
    //    for (unsigned int j = 0; j < h; j++) {
    //        for (unsigned int i = 0; i < w; i++) {
    //            // Get positon of pixel
    //            int pos_x = i + x;
    //            int pos_y = j + y;
    //            // Pixel on screen ?
    //            if (pos_x < 0 || pos_y < 0 || pos_x > m_width - 1 || pos_y > m_height - 1)
    //                continue;
    //            // Calculate indexes
    //            unsigned int index = pos_x + pos_y * m_width;
    //            unsigned int img_index = i + j * w;
    //            // Insert frame unit from image to frame buffer
    //            // m_buffer[index] = img_units[img_index]; // cannot be applyed to non-same coordinates
    //            m_buffer[index] += img_units[img_index];
    //        }
    //    }
    throw std::exception("Not implemented yet");
}

void tren::drawPixel(const tren::PixelDef& pixelDef) {
    int frame_width = tren::getBufferWidth();
    const int buf_size = tren::getBufferWidth() * tren::getBufferHeight();

    int pos = pixelDef.x + pixelDef.y * frame_width;
    // TODO throw exception?
    if (pos > buf_size - 1 || pos < 0) return;

    tren::getVirtualBuffer()[pos] = pixelDef.unit;
}