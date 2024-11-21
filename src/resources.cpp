#include "resources.hpp"

int frame_width = 0;
int frame_height = 0;

tren::FrameUnit* buffer = nullptr;
tren::FrameUnit* virtual_buffer = nullptr;

tren::FrameUnit* tren::getBuffer() {
	return buffer;
}

tren::FrameUnit* tren::getVirtualBuffer() {
	return virtual_buffer;
}

int tren::getBufferWidth()
{
	return frame_width;
}

int tren::getBufferHeight()
{
	return frame_height;
}

void tren::resizeBuffers(int w, int h)
{
	tren::cleanResources();

	frame_width = w;
	frame_height = h;

	buffer = new tren::FrameUnit[w * h];
	virtual_buffer = new tren::FrameUnit[w * h];
}

void tren::cleanResources() {
	// TODO delete pointers
	if(buffer) delete[] buffer;
	if(virtual_buffer) delete[] virtual_buffer;

	buffer = nullptr;
	virtual_buffer = nullptr;

	frame_width = 0;
	frame_height = 0;
}