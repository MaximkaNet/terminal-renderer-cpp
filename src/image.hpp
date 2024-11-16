#ifndef RENDERER_IMAGE_HPP // include guard (can use #pragma once, but is non-standard directive)
#define RENDERER_IMAGE_HPP
#include <vector>
#include <string>

#include "frame_unit.hpp"

/**
* Class represents image as array of frame units.
*/
class Image {
	unsigned int m_width, m_height;
	std::vector<FrameUnit> m_frame_units;

	/**
	* Read image data
	*/
	void read(std::string path);

	/**
	* Returns true if file can opens false otherwise
	*/
	bool path_exists(std::string path);
public:

	/**
	* Create empty image
	*/
	Image();

	/**
	* Create new image instance from file path
	*/
	Image(std::string path);

	/**
	* Clear colors memory
	*/
	~Image();

	/**
	* Load image
	*/
	void load(std::string path);

	/**
	* Get frame units
	*/
	std::vector<FrameUnit> get_frame_units() const;

	/**
	* Get image width
	*/
	unsigned int get_width() const;

	/**
	* Get image height
	*/
	unsigned int get_height() const;
};
#endif //! IMAGE_HPP