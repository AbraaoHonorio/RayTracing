#include "image.h"

TImage::TImage()
{
	width = 512;
	height = 512;
	color_channels = 3;
	int size = width * height * color_channels;
	buffer = new float[size];
	for (int i=0; i<size; i+=3)
		buffer[i] = buffer[i+1] = buffer[i+2] = 0.0f;
}

TImage::TImage(int w, int h)
{
	width = w;
	height = h;
	color_channels = 3;
	int size = width * height * color_channels;
	buffer = new float[size];
	for (int i=0; i<size; i+=3)
		buffer[i] = buffer[i+1] = buffer[i+2] = 0.0f;
}

TImage::~TImage()
{
	delete [] buffer;
}

void TImage::writePixel(int x, int y, float val)
{
	long int index = x * color_channels + y * width * color_channels;
	buffer[index] = buffer[index + 1] = buffer[index + 2] = val;
}

int TImage::toInt(float val)
{
	return int(val*255+.5);
}

void TImage::save(char* filename)
{
	float dmin, dmax;
	int size = width * height * color_channels;
	bool first = true;

	FILE *f = fopen(filename, "w");         // Write image to PPM file.
	fprintf(f, "P3\n%d %d\n%d\n", width, height, 255);

	for (int i=0; i<size; i+=3)
		if (buffer[i] != 0.0f)
			if (first)
			{
				first = false;
				dmin = dmax = buffer[i];
			}
			else
			{
				dmin = (buffer[i] < dmin)?buffer[i]:dmin;
				dmax = (buffer[i] > dmax)?buffer[i]:dmax;
			}

	for (int i=0; i<size; i+=3)
		if (buffer[i] != 0.0f)
			buffer[i+2] = buffer[i+1] = buffer[i] = (buffer[i] - dmin) / (dmax - dmin);

	for (int i=0; i<size; i+=3)
		fprintf(f,"%d %d %d ", toInt(buffer[i]), toInt(buffer[i+1]), toInt(buffer[i+2]));
}

