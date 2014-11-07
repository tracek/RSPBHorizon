#include "Classifier.h"


Classifier::Classifier(void)
{
}


Classifier::~Classifier(void)
{
}

bool Classifier::IsABird(Mat object)
{
	return true;
}

Mat Classifier::PlotHorizontFluctuation(Mat *horiziont_buffer)
{
	Mat plot;
	return plot;
}

int Classifier::RecognizeFlightType(Mat* horizont_buffer)
{
	return 0;
}



int Classifier::DetectAttitude(int* treshold_buffer)
{
	return 0;
}

int Classifier::FilterOutVideo(vector<float> r_buffer, vector<float> g_buffer, vector<float> b_buffer )
{
	float mean_r, mean_g, mean_b;
	mean_r = 0;
	mean_g = 0; 
	mean_b = 0;
	int out = -1;
	for (int i = 1; i <= r_buffer.max_size() ; i++)
	{
		mean_r += r_buffer[i];
		mean_g += g_buffer[i];
		mean_b += b_buffer[i];
	}

	mean_r = mean_r / r_buffer.max_size();
	mean_g = mean_g / g_buffer.max_size();
	mean_b = mean_b / b_buffer.max_size();

	if (mean_r > 220 && mean_g > 220 && mean_b > 220)
	{
		out = 0;
	}
	else
	{
		out = 1;
	}
	return out;
}