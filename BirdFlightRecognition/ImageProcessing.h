#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#pragma once

using namespace cv;
using namespace std;

class ImageProcessing
{
public:
	ImageProcessing(void);
	~ImageProcessing(void);

private:
	Mat current_frame;


public:
	vector<float> r_threshold_buffer;
	vector<float> g_threshold_buffer;
	vector<float> b_threshold_buffer;
	void DetectEdges(Mat, Mat &, Mat &, Mat &);
	Mat DetectHorizont(Mat);
	Mat DetectObjects(Mat);
	void CalculateHistogram(Mat, bool);
};

