#include "resources.hpp"
#include "renderer.hpp"
#include "terminal.hpp"
#include "utils.hpp"

#include <sstream>

void tren::init() {
	// auto detect window size
	auto size = tren::getScreenSize();
	tren::init(size.first, size.second);
}

void tren::init(int w, int h) {
	tren::resizeBuffers(w, h);
	tren::attrOn(ATTR_ALT_SCREEN);
}

void tren::refresh()
{
	tren::FrameUnit* buff_ptr = tren::getBuffer();
	tren::FrameUnit* virt_buff_ptr = tren::getVirtualBuffer();
	// Compare two screens
	auto compared = compareBuffers(tren::getBufferWidth(), tren::getBufferHeight(), buff_ptr, virt_buff_ptr);

	// Pring different frame units

	std::stringstream ss;

	ss << std::noskipws;

	for (const ComparedFrameUnit& unit: compared) {
		// Update real buffer
		int pos = unit.x + unit.y * getBufferWidth();

		// Skip units that out of the buffer
		if (pos < 0 || pos >= getBufferWidth() * getBufferHeight()) continue;

		tren::getBuffer()[pos] = unit.ref;

		ss << compileFrameUnit(unit.ref, unit.x, unit.y);
	}

	printf(ss.str().c_str());
}

void tren::endwin()
{
	tren::cleanResources();

	tren::attrOff(ATTR_ALT_SCREEN);
}