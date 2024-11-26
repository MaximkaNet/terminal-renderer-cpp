#include "frame.hpp"
#include "resources.hpp"

void tren::drawRectFilled(int x, int y, int w, int h, char ch) {
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++)
        {
            drawPixel(x + i, y + j, ch);
        }
    }
}

void tren::drawText(int x, int y, const char* str) {
    // TODO throw exception here?
    if (str == nullptr) return;

    int pos_x = x;
    int pos_y = y;

    while (*str) {

        if (*str == '\n') {
            pos_y++;
            pos_x = x;
            str++;
        }

        if (pos_x < 0 || pos_y < 0 || pos_x > tren::getBufferWidth() - 1) { str++; continue; }
        if (pos_y > tren::getBufferHeight() - 1) break;

        drawPixel(pos_x, pos_y, *str);
        pos_x++;
        str++;
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

void tren::drawPixel(int x, int y, char ch) {
    int frame_width = tren::getBufferWidth();
    int frame_height = tren::getBufferHeight();
    const int buf_size = tren::getBufferWidth() * tren::getBufferHeight();

    if (x < 0 || x > frame_width - 1) return;
    else if (y < 0 || y > frame_height - 1) return;

    int pos = x + y * frame_width;
    // TODO throw exception?
    if (pos > buf_size - 1 || pos < 0) return;

    tren::getVirtualBuffer()[pos] = FrameUnit{ ch, FUNIT_DEFAULT_COLOR };
}