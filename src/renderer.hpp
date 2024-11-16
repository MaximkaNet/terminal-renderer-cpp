#ifndef RENDERER_RENDERER_HPP
#define RENDERER_RENDERER_HPP
#include <iostream>
#include <sstream>
#include <vector>

#include "frame.hpp"

#define DEFAULT_FRAME_UNIT_CHAR ' '
#define DEFAULT_BACKGROUND_COLOR 0x0C0C0C
#define DEFAULT_FOREGROUND_COLOR 0xF2F2F2

/**
 * Terminal renderer
 * 
 * Manage frames (build and render them)
 */
class TerminalRenderer {
    unsigned int m_width, m_height;
    Frame* m_current = nullptr;
    Frame* m_prev = nullptr;
    
    /**
     * Set renderer width
     */
    void set_width(unsigned int w);

    /**
     * Set renderer height
     */
    void set_height(unsigned int h);

public:

    /**
     * Create new terminal renderer
     */
    TerminalRenderer();

    /**
     * Create new terminal renderer by w - width, h - height
     */
    TerminalRenderer(unsigned int w, unsigned int h);

    /**
     * Destruct terminal renderer
     */
    ~TerminalRenderer();

    /**
     * Resize screen
     */
    void resize(unsigned int w, unsigned int h);

    /**
     * Get renderer width
     */
    unsigned int get_width() const;

    /**
     * Get renderer height
     */
    unsigned int get_height() const;

    /**
     * Create new frame
     */
    Frame* new_frame();

    /**
     * Get current frame
     */
    Frame* get_current() const;

    /**
     * Show frame in output stream 
     */
    void render();
};
#endif //! RENDERER_RENDERER_HPP