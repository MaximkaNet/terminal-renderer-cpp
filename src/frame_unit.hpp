#ifndef RENDERER_FRAME_UNIT_HPP // include guard
#define RENDERER_FRAME_UNIT_HPP
#include <string>

#include "color.hpp"

/**
 * Frame unit. (Pixel, but in terminal)
 */
class FrameUnit {
    unsigned int m_x, m_y;
    char m_char;
    color m_fg;
    color m_bg;
public:

    /**
     * Construct new FrameUnit
     */
    FrameUnit(char ch, color bg, color fg, unsigned int x, unsigned int y);

    /**
     * Construct new FrameUnit
     */
    FrameUnit(char ch, color bg, unsigned int x, unsigned int y);

    /**
     * Construct new FrameUnit
     */
    FrameUnit(char ch, unsigned int x, unsigned int y);

    /**
     * FrameUnit destructor
     */
    ~FrameUnit();

    /**
     * Set x axis
     */
    void set_x(unsigned int x);

    /**
     * Set y axis
     */
    void set_y(unsigned int y);

    /**
     * Set position
     */
    void set_position(unsigned int x, unsigned int y);

    /**
     * Set default values to frame unit
     */
    void reset();

    /**
     * Merge the units. 
     * Merge every member without position
     */
    void merge(FrameUnit& rhs);

    /**
     * Set background color pointer
     */
    void set_bg(color color);

    /**
     * Set background color pointer
     */
    void set_fg(color color);

    /**
     * Set background color pointer
     */
    void set_char(char ch);

    /**
     * Compile unit to ascii escape sequence
     */
    std::string compile() const;

    /**
     * Compile cursor movement
     */
    std::string compile_pos() const;

    ///**
    // * Delete background and foreground colors memory using member pointers
    // */
    //void destroy_colors();

    ///**
    // * Delete background color memory using member pointer
    // */
    //void destroy_bg_color();

    ///**
    // * Delete foreground color memory using member pointer
    // */
    //void destroy_fg_color();

    bool operator==(const FrameUnit& rhs) const;
    bool operator!=(const FrameUnit& rhs) const;

    FrameUnit& operator=(const FrameUnit& rhs);
    FrameUnit& operator+=(const FrameUnit& rhs);
};
#endif //! FRAME_UNIT_HPP