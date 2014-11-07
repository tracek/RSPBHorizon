#include "ImageProcessing.h"



ImageProcessing::ImageProcessing(void)
{
	Mat current_frame;
	r_threshold_buffer;
	g_threshold_buffer;
	b_threshold_buffer;
}


ImageProcessing::~ImageProcessing(void)
{
}

void ImageProcessing::DetectEdges(Mat frame,
								 Mat &edges_1, 
								 Mat &edges_2, 
								 Mat &edges_3)
{
	Mat blurred;
	cvtColor(frame, blurred, CV_BGR2GRAY);
    GaussianBlur(blurred, blurred, Size(7,7), 1.5, 1.5);
    Canny(blurred, edges_1, 0, 30, 3);
	Canny(blurred, edges_2, 30, 70, 3);
	Canny(blurred, edges_3, 60, 90, 3);

	edges_1 = abs(edges_1 - edges_3);
	edges_2 = abs(edges_2 - edges_3);
	
}

Mat ImageProcessing::DetectHorizont(Mat frame)
{
	return frame;
}

Mat ImageProcessing::DetectObjects(Mat frame)
{
	return frame;
}

void ImageProcessing::CalculateHistogram(Mat frame, bool show_plot)
{
  vector<Mat> bgr_planes;
  split( frame, bgr_planes );

  vector<float> r_thresholds, b_thresholds, g_thresholds;  // for diagnostics
  float mean_r, mean_g, mean_b;
  mean_r = 0;
  mean_g = 0;
  mean_b = 0;

  /// Establish the number of bins
  int histSize = 256;

  /// Set the ranges ( for B,G,R) )
  float range[] = { 0, 256 } ;
  const float* histRange = { range };

  bool uniform = true; bool accumulate = false;

  Mat b_hist, g_hist, r_hist;

  /// Compute the histograms:
  calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
  calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
  calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

  for( int i = 1; i < histSize; i++ )
  {
	  r_thresholds.push_back(cvRound(r_hist.at<float>(i))); 
	  g_thresholds.push_back(cvRound(g_hist.at<float>(i)));
	  b_thresholds.push_back(cvRound(b_hist.at<float>(i)));	
	  mean_r += r_hist.at<float>(i);
	  mean_g += g_hist.at<float>(i);
	  mean_b += b_hist.at<float>(i);
  }

  mean_r = mean_r / histSize;
  mean_g = mean_g / histSize;
  mean_b = mean_b / histSize;

  r_threshold_buffer.push_back(mean_r);
  g_threshold_buffer.push_back(mean_g);
  b_threshold_buffer.push_back(mean_b);

  if (show_plot)
  {
	  // Draw the histograms for B, G and R
	  int hist_w = 512; int hist_h = 400;
	  int bin_w = cvRound( (double) hist_w/histSize );

	  Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

	  /// Normalize the result to [ 0, histImage.rows ]
	  normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	  normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	  normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

	  /// Draw for each channel
	  for( int i = 1; i < histSize; i++ )
	  {
		  line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
						   Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
						   Scalar( 255, 0, 0), 2, 8, 0  );
		  line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
						   Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
						   Scalar( 0, 255, 0), 2, 8, 0  );
		  line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
						   Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
						   Scalar( 0, 0, 255), 2, 8, 0  );
	  }

	  /// Display
	  namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
	  imshow("calcHist Demo", histImage );

	  waitKey(33);
  }
}