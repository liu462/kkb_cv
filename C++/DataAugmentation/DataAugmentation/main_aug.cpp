#include "Augmentator.h"
// C++
#include <stdio.h>
#include <Windows.h>
#include <iostream>
//OpenCV mybuild
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

int main() 
{
	cv::Mat src_img = cv::imread("lenna.png", cv::IMREAD_COLOR);
	
	Augmentator my_augtor;
	
	cv::Mat dst_crop, dst_color_shift, dst_simi_trans, dst_affine_trans, dst_persp_trans, dst_noise;
	
	my_augtor.Crop(src_img, dst_crop, cv::Rect(10, 10, 244, 244), cv::Size(256, 256));

	my_augtor.ColorShift(src_img, dst_color_shift, 50);

	my_augtor.SimilarityTransform(src_img, dst_affine_trans, cv::Point2f(src_img.cols*0.5, src_img.rows*0.5), 30, 0.5);

	my_augtor.AffineTransform(src_img, dst_affine_trans);

	my_augtor.PerspectiveTransform(src_img, dst_persp_trans);

	my_augtor.NoiseAdd(src_img, dst_noise);

	cv::imshow("anyAug", dst_noise);
}