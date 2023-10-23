#include "hw.hpp"

ImageSize::ImageSize()
{
	ImageSize::rows = 0;
	ImageSize::columns = 0;
}

ImageSize::ImageSize(int rows, int columns)
{
	ImageSize::rows = rows;
	ImageSize::columns = columns;
}

ImageSize::ImageSize(const ImageSize& other)
{
	ImageSize::rows = other.rows;
	ImageSize::columns = other.columns;
}

ImageSize ImageSize::operator=(const ImageSize& other)
{
	ImageSize::rows = other.rows;
	ImageSize::columns = other.columns;
	return *this;
}

ImageSize ImageSize::operator*(const double& other)
{
	return ImageSize(ImageSize::rows * other, ImageSize::columns * other);
}

ImageSize ImageSize::operator/(const double& other)
{
	return ImageSize(ImageSize::rows / other, ImageSize::columns / other);
}

Coordinate::Coordinate()
{
	Coordinate::row = 0;
	Coordinate::column = 0;
}

Coordinate::Coordinate(int row, int column)
{
	Coordinate::row = row;
	Coordinate::column = column;
}

Coordinate Coordinate::operator=(const Coordinate& other)
{
	Coordinate::row = other.row;
	Coordinate::column = other.column;
	return *this;
}

bool Coordinate::operator==(const Coordinate& other)
{
	bool result = Coordinate::row == other.row;
	result &= Coordinate::column == other.column;
	return result;
}

bool Coordinate::operator!=(const Coordinate& other)
{
	bool result = Coordinate::row != other.row;
	result |= Coordinate::column != other.column;
	return result;
}

Image::Image()
{
	Image::size = ImageSize(0, 0);
}

Image::Image(ImageSize size, uint8_t value)
{
	Image::size = size;
	Image::R = vector<vector<uint8_t>>(size.rows, vector<uint8_t>(size.columns, value));
	Image::G = vector<vector<uint8_t>>(size.rows, vector<uint8_t>(size.columns, value));
	Image::B = vector<vector<uint8_t>>(size.rows, vector<uint8_t>(size.columns, value));
}

Image::Image(vector<vector<uint8_t>>& R, vector<vector<uint8_t>>& G, vector<vector<uint8_t>>& B)
{
	Image::size.rows = (int)R.size();
	Image::size.columns = (int)R[0].size();
	Image::R = R;
	Image::G = G;
	Image::B = B;
}

void Image::set_image(vector<vector<uint8_t>>& R, vector<vector<uint8_t>>& G, vector<vector<uint8_t>>& B)
{
	Image::size.rows = (int)R.size();
	Image::size.columns = (int)R[0].size();
	Image::R = R;
	Image::G = G;
	Image::B = B;
}

void Image::set_pixel(Coordinate coord, uint8_t r, uint8_t g, uint8_t b)
{
	int row = coord.row;
	int column = coord.column;
	Image::R[row][column] = r;
	Image::G[row][column] = g;
	Image::B[row][column] = b;
}

Image Image::operator=(const Image& other)
{
	Image::size = other.size;
	Image::R = other.R;
	Image::G = other.G;
	Image::B = other.B;
	return *this;
}

void Rotation_270(Image& img)
{
	Image img_temp(img.size, 0);

	int rows = img.size.rows;
	int columns = img.size.columns;
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < columns; c++)
		{
			img_temp.R[columns - 1 - c][r] = img.R[r][c];
			img_temp.G[columns - 1 - c][r] = img.G[r][c];
			img_temp.B[columns - 1 - c][r] = img.B[r][c];
		}
	}

	img = img_temp;
}

void nearest(const Image& img_in, Image& img_out, ImageSize size_out)
{
	ImageSize size_in(img_in.size);
	Image img_temp(size_out, 0);

	for (int r = 0; r < size_out.rows; r++)
	{
		for (int c = 0; c < size_out.columns; c++)
		{
			double r_mapping = (double)r / (size_out.rows - 1) * (size_in.rows - 1);
			double c_mapping = (double)c / (size_out.columns - 1) * (size_in.columns - 1);
			img_temp.R[r][c] = img_in.R[(int)round(r_mapping)][(int)round(c_mapping)];
			img_temp.G[r][c] = img_in.G[(int)round(r_mapping)][(int)round(c_mapping)];
			img_temp.B[r][c] = img_in.B[(int)round(r_mapping)][(int)round(c_mapping)];
		}
	}

	img_out = img_temp;
}
