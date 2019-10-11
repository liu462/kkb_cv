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
