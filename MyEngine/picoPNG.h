#pragma once
#include <vector>

namespace MyEngine{
	extern int decodePNG(std::vector<unsigned char>& out_image,// a char of RGB color 
		unsigned long& image_width, //Dimension
		unsigned long& image_height, //Dimension
		const unsigned char* in_png, //ptr to the PNG file in memory.
		size_t in_size, //size of char * buffer
		bool convert_to_rgba32 = true); //if we need to convert to rgba32.
}