#include "frame_unit.hpp"

#include <vector>
#include <string>

/**
* Compared frame unit
*/
struct ComparedFrameUnit {
	int x;
	int y;
	tren::FrameUnit& ref;
};

/**
* Compare the buffers
*/
std::vector<ComparedFrameUnit> compareBuffers(int w, int h, tren::FrameUnit*& b, tren::FrameUnit*& vb);

/**
* Returns true if the l equal r false otherwise
*/
bool areFrameUnitsEqual(const tren::FrameUnit& l, const tren::FrameUnit& r);

/**
* Compile the frame unit for rendering on specified position with cursor offset
*/
std::string compileFrameUnit(const tren::FrameUnit& ref, int x, int y, int offX = 1, int offY = 1);

/**
* Convert x and y to string and add ';' between
*/
std::string compilePos(int x, int y);

/**
* Returns formatted string "r:g:b"
*/
std::string compileColor(const tren::color& color);