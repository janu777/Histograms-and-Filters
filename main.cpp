#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "histogram.h"
#include "filters.h"
using namespace std;
using namespace cv;

int main()
{
	Mat test = imread("/home/linux/Image processing/Pictures/lena.jpg");
	Size Resolution = test.size(); // gives resolution of the image
	//histograms(test);
	cvtColor(test,test,COLOR_BGR2GRAY);
	filters(test);
	imshow("original",test);
	//waitKey(0); 
	//cout<<"Hello World"<<endl;
	return 0;
}