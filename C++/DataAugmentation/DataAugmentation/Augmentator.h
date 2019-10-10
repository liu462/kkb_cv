#pragma once
// C++
#include <stdio.h>
#include <Windows.h>
#include <iostream>
//OpenCV mybuild
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

class Augmentator
{
public:
	Augmentator();
	virtual ~Augmentator();

	int Crop(cv::Mat& src, cv::Mat& dst, cv::Size win_size, cv::Size target_win_size, int crop_mode);
	int ColorShift();
	int Rotation();
	int PerspectiveTransform();
	int NoiseAdd();


};
