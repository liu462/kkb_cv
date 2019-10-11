#include "Augmentator.h"



Augmentator::Augmentator()
{
}


Augmentator::~Augmentator()
{
}

int Augmentator::Crop(cv::Mat & src, cv::Mat & dst, cv::Rect win_rect, cv::Size target_size)
{
	//win size should be smaller than src size
	//target size is supposed to be bigger than win_size
	if (src.empty() ) return -1;
	cv::Mat crop_img;

	int src_h = src.rows;
	int src_w = src.cols;
	
	if (!(win_rect.br().x < src_w && win_rect.br().y < src_h && win_rect.tl().x > 0 && win_rect.tl().y > 0)) 
		return -1;
		
	int long_side = std::max(src_h, src_w);

	//crop
	crop_img = src(win_rect);

	//padding
	//centre padding?
	int padding_top, padding_bottom, padding_left, padding_right;
	padding_top = (target_size.height - win_rect.height) * 0.5;
	padding_bottom = padding_top;
	padding_left = (target_size.width - win_rect.width) * 0.5;
	padding_right = padding_left;

	//handle even/odd width/height
	if (padding_top * 2 + win_rect.height < target_size.height)
		padding_bottom++;
	if (padding_left * 2 + win_rect.width < target_size.width)
		padding_right++;

	//padding mode can be changed according to different images.
	cv::copyMakeBorder(crop_img, dst, padding_top, padding_bottom, padding_left, padding_right,cv::BORDER_REPLICATE);
	
	return 0;
}

int Augmentator::ColorShift(cv::Mat& src, cv::Mat & dst, int range)
{
	if (src.empty()) return -1;
	if (range < 0 || range >255) return -1;

	cv::Mat color_mod_img = src.clone();

	std::vector<cv::Mat> color_mod_channels;
	cv::split(color_mod_img, color_mod_channels);

	cv::RNG rng(0xFFFFFFFF);
	
	if (0 == range) dst = color_mod_img;

	std::vector<int> rng_vals;
	for (int i = 0; i < 3; i++) 
	{
		rng_vals.push_back(rng.uniform(-1 * range, range));
	}

	
	for (cv::Mat& cur_channel : color_mod_channels) 
	{
		for (int i = 0; i < cur_channel.rows; i++)
		{
			for (int j = 0; j < cur_channel.cols; j++)
			{
				int cur_val = (int)cur_channel.at<uchar>(i, j);
				cur_val += rng_vals[i];

				if (cur_val < 0) cur_val = 0;
				else if (cur_val > 255) cur_val = 255;
				cur_channel.at<uchar>(i, j) = cur_val;
			}
		}
		
	}

	cv::merge(color_mod_channels, dst);

	return 0;
}

int Augmentator::SimilarityTransform(cv::Mat & src, cv::Mat & dst, cv::Point2f center, double angle, double scale)
{
	if (src.empty()) return -1;
	if (center.x<0 || center.x>src.cols - 1) return -1;
	if (center.y<0 || center.y>src.rows - 1) return -1;

	cv::Mat simi_mat = cv::getRotationMatrix2D(center, angle, scale);
	cv::warpAffine(src, dst, simi_mat, cv::Size(src.cols, src.rows));
	
	return 0;
}

int Augmentator::AffineTransform(cv::Mat & src, cv::Mat & dst)
{
	if (src.empty()) return -1;

	std::vector<cv::Point> src_pts, dst_pts;
	src_pts.push_back(cv::Point(0, 0));
	src_pts.push_back(cv::Point(src.cols - 1, 0));
	src_pts.push_back(cv::Point(0, src.rows - 1));

	dst_pts.push_back(cv::Point(src.cols * 0.2, src.rows * 0.1));
	dst_pts.push_back(cv::Point(src.cols * 0.9, src.rows * 0.2));
	dst_pts.push_back(cv::Point(src.cols * 0.1, src.rows * 0.9));

	cv::Mat affine_mat = cv::getAffineTransform(src_pts, dst_pts);
	cv::warpAffine(src, dst, affine_mat, cv::Size(src.cols, src.rows));

	return 0;
}

int Augmentator::PerspectiveTransform(cv::Mat & src, cv::Mat & dst)
{
	if (src.empty()) return -1;
	
	int random_margin = 60;

	cv::RNG rng(0xFFFFFFFF);
	std::vector<cv::Point> src_pts, dst_pts;
	
	int x1 = rng.uniform(-random_margin, random_margin);
	int y1 = rng.uniform(-random_margin, random_margin);
	src_pts.push_back(cv::Point(x1, y1));
	int x2 = rng.uniform(src.cols - random_margin - 1, src.cols - 1);
	int y2 = rng.uniform(-random_margin, random_margin);
	src_pts.push_back(cv::Point(x2, y2));
	int x3 = rng.uniform(src.cols - random_margin - 1, src.cols - 1);
	int y3 = rng.uniform(src.rows - random_margin - 1, src.rows - 1);
	src_pts.push_back(cv::Point(x3, y3));
	int x4 = rng.uniform(-random_margin, random_margin);
	int y4 = rng.uniform(src.rows - random_margin - 1, src.rows - 1);
	src_pts.push_back(cv::Point(x4, y4));


	int dx1 = rng.uniform(-random_margin, random_margin);
	int dy1 = rng.uniform(-random_margin, random_margin);
	dst_pts.push_back(cv::Point(dx1, dy1));
	int dx2 = rng.uniform(src.cols - random_margin - 1, src.cols - 1);
	int dy2 = rng.uniform(-random_margin, random_margin);
	dst_pts.push_back(cv::Point(dx2, dy2));
	int dx3 = rng.uniform(src.cols - random_margin - 1, src.cols - 1);
	int dy3 = rng.uniform(src.rows - random_margin - 1, src.rows - 1);
	dst_pts.push_back(cv::Point(dx3, dy3));
	int dx4 = rng.uniform(-random_margin, random_margin);
	int dy4 = rng.uniform(src.rows - random_margin - 1, src.rows - 1);
	dst_pts.push_back(cv::Point(dx4, dy4));

	cv::Mat perspective_mat = cv::getPerspectiveTransform(src_pts, dst_pts);
	cv::warpPerspective(src, dst, perspective_mat, cv::Size(src.cols, src.rows));

	return 0;
}
