#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

#include "ImageProcessing.h"
#include "Classifier.h"
#include "FileIO.h"

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
	String file_to_load = "C:\\Users\\kasia_000\\Documents\\Bird flight\\Frigate Cam 3\\Frigate Cam 3\\Ascension_Frigate_Cam.avi";
    VideoCapture flight_video(file_to_load);

	ImageProcessing img_processing;
	Classifier classfier;
    if(!flight_video.isOpened())  
        return -1;

    Mat video_file;
    for(;;)
    {
        Mat frame;
		Mat edges_1, edges_2, edges_3;
        flight_video >> frame; 
		if (!frame.data)
		{
			break;
		}
		img_processing.CalculateHistogram(frame, true);
		img_processing.DetectEdges(frame, edges_1, edges_2, edges_3);
        imshow("Video", frame);
		imshow("Edges 1", edges_1);
		imshow("Edges 2", edges_2);
		imshow("Edges 3", edges_3);
        waitKey(33);

    }

	/*int out = classfier.FilterOutVideo(img_processing.r_threshold_buffer, img_processing.g_threshold_buffer, img_processing.b_threshold_buffer);
	
	if (out == 0)
	{
		cvNamedWindow("Zero");
	}
	else
	{
		cvNamedWindow("One");
	}*/
    return 0;
}