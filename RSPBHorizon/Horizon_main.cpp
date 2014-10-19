#include <iostream>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
	Mat im = imread("c:\\lena.jpg", CV_LOAD_IMAGE_COLOR);
	namedWindow("Lena");
	imshow("Lena", im);

	cout << (Scalar)im.at<uchar>(20, 20) << endl;

	cout << "Press 'q' to quit" << endl;
	while (char(waitKey(1)) != 'q') {}
}