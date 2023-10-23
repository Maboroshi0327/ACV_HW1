#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

#include <opencv2\opencv.hpp>
using namespace cv;

#include "bmp.hpp"
#include "hw.hpp"

int main()
{
#pragma region 1
	vector<vector<uint8_t>> R, G, B;
	BMP bmp;
	bmp.open_img("lena1024.bmp", R, G, B);
	bmp.save_img("1.bmp", R, G, B);
	Image img(R, G, B);
#pragma endregion 1

#pragma region 1 OpenCV
	Mat im = imread("lena1024.bmp");
	imwrite("1_opencv.bmp", im);
#pragma endregion 1 OpenCV

#pragma region 2
	Image img_rot(img);
	Rotation_270(img_rot);
	bmp.save_img("2.bmp", img_rot.R, img_rot.G, img_rot.B);
#pragma endregion 2

#pragma region 2 OpenCV
	Mat im_rot;
	Point2d center((im.cols - 1) / 2.0, (im.rows - 1) / 2.0);
	Mat rotation_matix = getRotationMatrix2D(center, 90, 1.0);
	warpAffine(im, im_rot, rotation_matix, im.size());
	imwrite("2_opencv.bmp", im_rot);
#pragma endregion 2 OpenCV

#pragma region 3
	bmp.save_img("3.bmp", img_rot.B, img_rot.R, img_rot.G);
#pragma endregion 3

#pragma region 3 OpenCV
	Mat im_grb(im.size(), CV_8UC3);
	for (int r = 0; r < im.rows; r++)
		for (int c = 0; c < im.cols; c++)
		{
			im_grb.at<Vec3b>(r, c)[0] = im_rot.at<Vec3b>(r, c)[1];	// G -> B
			im_grb.at<Vec3b>(r, c)[1] = im_rot.at<Vec3b>(r, c)[2];	// R -> G
			im_grb.at<Vec3b>(r, c)[2] = im_rot.at<Vec3b>(r, c)[0];	// B -> R
		}
	imwrite("3_opencv.bmp", im_grb);
#pragma endregion 3 OpenCV

#pragma region Bonus 1-1
	Image img_x2, img_half;
	nearest(img, img_x2, img.size * 2);
	nearest(img, img_half, img.size / 2);
	bmp.save_img("Bonus_1_1_x2.bmp", img_x2.R, img_x2.G, img_x2.B);
	bmp.save_img("Bonus_1_1_half.bmp", img_half.R, img_half.G, img_half.B);
#pragma endregion Bonus 1-1

#pragma region Bonus 1-1 OpenCV
	Mat im_x2, im_half;
	resize(im, im_x2, Size(im.cols * 2, im.rows * 2), 0, 0, INTER_NEAREST);
	resize(im, im_half, Size(im.cols / 2, im.rows / 2), 0, 0, INTER_NEAREST);
	imwrite("Bonus_1_1_x2_opencv.bmp", im_x2);
	imwrite("Bonus_1_1_half_opencv.bmp", im_half);
#pragma endregion Bonus 1-1 OpenCV

#pragma region Bonus 1-2
	Rotation_270(img_x2);
	Rotation_270(img_half);
	bmp.save_img("Bonus_1_2_x2.bmp", img_x2.R, img_x2.G, img_x2.B);
	bmp.save_img("Bonus_1_2_half.bmp", img_half.R, img_half.G, img_half.B);
#pragma endregion Bonus 1-2

#pragma region Bonus 1-2 OpenCV
	Mat im_rot_x2, im_rot_half;
	center = Point2d((im_x2.cols - 1) / 2.0, (im_x2.rows - 1) / 2.0);
	rotation_matix = getRotationMatrix2D(center, 90, 1.0);
	warpAffine(im_x2, im_rot_x2, rotation_matix, im_x2.size());
	imwrite("Bonus_1_2_x2_opencv.bmp", im_rot_x2);
	center = Point2d((im_half.cols - 1) / 2.0, (im_half.rows - 1) / 2.0);
	rotation_matix = getRotationMatrix2D(center, 90, 1.0);
	warpAffine(im_half, im_rot_half, rotation_matix, im_half.size());
	imwrite("Bonus_1_2_half_opencv.bmp", im_rot_half);
#pragma endregion Bonus 1-2 OpenCV

#pragma region Bonus 1-3
	bmp.save_img("Bonus_1_3_x2.bmp", img_x2.B, img_x2.R, img_x2.G);
	bmp.save_img("Bonus_1_3_half.bmp", img_half.B, img_half.R, img_half.G);
#pragma endregion Bonus 1-3

#pragma region Bonus 1-3 OpenCV
	Mat im_grb_x2(im_rot_x2.size(), CV_8UC3);
	Mat im_grb_half(im_rot_half.size(), CV_8UC3);
	for (int r = 0; r < im_x2.rows; r++)
		for (int c = 0; c < im_x2.cols; c++)
		{
			im_grb_x2.at<Vec3b>(r, c)[0] = im_rot_x2.at<Vec3b>(r, c)[1];	// G -> B
			im_grb_x2.at<Vec3b>(r, c)[1] = im_rot_x2.at<Vec3b>(r, c)[2];	// R -> G
			im_grb_x2.at<Vec3b>(r, c)[2] = im_rot_x2.at<Vec3b>(r, c)[0];	// B -> R
		}
	for (int r = 0; r < im_half.rows; r++)
		for (int c = 0; c < im_half.cols; c++)
		{
			im_grb_half.at<Vec3b>(r, c)[0] = im_rot_half.at<Vec3b>(r, c)[1];	// G -> B
			im_grb_half.at<Vec3b>(r, c)[1] = im_rot_half.at<Vec3b>(r, c)[2];	// R -> G
			im_grb_half.at<Vec3b>(r, c)[2] = im_rot_half.at<Vec3b>(r, c)[0];	// B -> R
		}
	imwrite("Bonus_1_3_x2_opencv.bmp", im_grb_x2);
	imwrite("Bonus_1_3_half_opencv.bmp", im_grb_half);
#pragma endregion Bonus 1-3 OpenCV

#pragma region Bonus 2-1
	Image img_3072;
	nearest(img, img_3072, img.size * 3);
	bmp.save_img("Bonus_2_1_3072.bmp", img_3072.R, img_3072.G, img_3072.B);
#pragma endregion Bonus 2-1

#pragma region Bonus 2-1 OpenCV
	Mat im_3072;
	resize(im, im_3072, Size(im.cols * 3, im.rows * 3), 0, 0, INTER_NEAREST);
	imwrite("Bonus_2_1_3072_opencv.bmp", im_3072);
#pragma endregion Bonus 2-1 OpenCV

#pragma region Bonus 2-2
	Rotation_270(img_3072);
	bmp.save_img("Bonus_2_2_3072.bmp", img_3072.R, img_3072.G, img_3072.B);
#pragma endregion Bonus 2-2

#pragma region Bonus 2-2 OpenCV
	Mat im_rot_3072;
	center = Point2d((im_3072.cols - 1) / 2.0, (im_3072.rows - 1) / 2.0);
	rotation_matix = getRotationMatrix2D(center, 90, 1.0);
	warpAffine(im_3072, im_rot_3072, rotation_matix, im_3072.size());
	imwrite("Bonus_2_2_3072_opencv.bmp", im_rot_3072);
#pragma endregion Bonus 2-2 OpenCV

#pragma region Bonus 2-3
	bmp.save_img("Bonus_2_3_3072.bmp", img_3072.B, img_3072.R, img_3072.G);
#pragma endregion Bonus 2-3

#pragma region Bonus 2-3 OpenCV
	Mat im_grb_3072(im_rot_3072.size(), CV_8UC3);
	for (int r = 0; r < im_rot_3072.rows; r++)
		for (int c = 0; c < im_rot_3072.cols; c++)
		{
			im_grb_3072.at<Vec3b>(r, c)[0] = im_rot_3072.at<Vec3b>(r, c)[1];	// G -> B
			im_grb_3072.at<Vec3b>(r, c)[1] = im_rot_3072.at<Vec3b>(r, c)[2];	// R -> G
			im_grb_3072.at<Vec3b>(r, c)[2] = im_rot_3072.at<Vec3b>(r, c)[0];	// B -> R
		}
	imwrite("Bonus_2_3_3072_opencv.bmp", im_grb_3072);
#pragma endregion Bonus 2-3 OpenCV
}
