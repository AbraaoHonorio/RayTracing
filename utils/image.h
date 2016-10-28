/*
 * image.h
 *
 *  Created on: Oct 28, 2014
 *      Author: Christian A. Pagot
 */

#ifndef IMAGE_IMAGE_H_
#define IMAGE_IMAGE_H_

#include <string>
#include <fstream>

class TImage
{
private:
	int width;
	int height;
	int color_channels;
	float* buffer;
	int toInt(float val);

public:
	TImage();
	TImage(int w, int h);
	~TImage();
	void save(char* filename);
	void writePixel(int x, int y, float d);
};

#endif /* IMAGE_IMAGE_H_ */
