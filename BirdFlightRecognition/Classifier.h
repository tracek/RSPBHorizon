#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#pragma once

using namespace cv;
using namespace std;

class Classifier
{
public:
	Classifier(void);
	~Classifier(void);
	bool IsABird(Mat);
	Mat PlotHorizontFluctuation(Mat*);
	int RecognizeFlightType(Mat*);
	int DetectAttitude(int* treshold_buffer);
	int Classifier::FilterOutVideo(vector<float>, vector<float>, vector<float> );
};

