#pragma once

#include "frame_unit.hpp"

namespace tren {
	/**
	* Get mutable pointer to "real" buffer
	*/
	tren::FrameUnit* getBuffer();

	/**
	* Get mutable pointer to "virtual" buffer
	*/
	tren::FrameUnit* getVirtualBuffer();

	/**
	* Get buffer width
	*/
	int getBufferWidth();

	/**
	* Get buffer height
	*/
	int getBufferHeight();

	/**
	* Resize buffer
	*/
	void resizeBuffers(int w, int h);

	/**
	* Clean buffer data
	*/
	void cleanResources();
}