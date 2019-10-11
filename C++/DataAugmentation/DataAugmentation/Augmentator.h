#pragma once

//OpenCV mybuild
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

class Augmentator
{
public:
	Augmentator();
	virtual ~Augmentator();

	int Crop(cv::Mat& src, cv::Mat& dst, cv::Rect win_rect, cv::Size target_size = cv::Size());

	int ColorShift(cv::Mat& src, cv::Mat & dst, int range);
	
	int SimilarityTransform(cv::Mat& src, cv::Mat & dst, cv::Point2f center, double angle, double scale);
	
	int AffineTransform(cv::Mat& src, cv::Mat & dst);
	
	int PerspectiveTransform(cv::Mat& src, cv::Mat & dst);
	
	int NoiseAdd(cv::Mat& src, cv::Mat& dst);


};

