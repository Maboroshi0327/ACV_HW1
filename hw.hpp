#ifndef _HW_
#define _HW_

#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

class ImageSize
{
public:
	int rows;
	int columns;
	ImageSize();
	ImageSize(int rows, int columns);
	ImageSize(const ImageSize& other);
	ImageSize operator=(const ImageSize& other);
	ImageSize operator*(const double& other);
	ImageSize operator/(const double& other);
};

class Coordinate
{
public:
	int row;
	int column;
	Coordinate();
	Coordinate(int row, int column);
	Coordinate operator=(const Coordinate& other);
	bool operator==(const Coordinate& other);
	bool operator!=(const Coordinate& other);
};

class Image
{
public:
	ImageSize size;
	vector<vector<uint8_t>> R;
	vector<vector<uint8_t>> G;
	vector<vector<uint8_t>> B;

	Image();
	Image(ImageSize size, uint8_t value);
	Image(vector<vector<uint8_t>>& R, vector<vector<uint8_t>>& G, vector<vector<uint8_t>>& B);
	void set_image(vector<vector<uint8_t>>& R, vector<vector<uint8_t>>& G, vector<vector<uint8_t>>& B);
	void set_pixel(Coordinate coord, uint8_t r, uint8_t g, uint8_t b);
	Image operator=(const Image& other);
};

void Rotation_270(Image& img);
void nearest(const Image& img_in, Image& img_out, ImageSize size_out);

#endif /* _HW_ */