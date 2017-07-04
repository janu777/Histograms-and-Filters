#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
using namespace std;
using namespace cv;
/*Noises and Filters:
	The most common types of noise include :
	Salt and Pepper Noise: Random occurance of pixels with intensities 1 and 0 
	Impulse Noise: Random occurance of pixels with intensity 1.
	Gaussian Noise: variations in intensities drawn form gaussian normal distribution.  
	The most commonly used Filters to remove such noises are:
	Median Filter - sorts the intensity values and replaces it with the mid value. Removes sudden spikes effectively.
	Box Filter - Also known as averaging filter. Takes average of values around and the mean value is replaced.
				 Used to remove gaussian Noise. Since the assumption is that the mean of the noise is zero.
	Gaussian Filter - smoothens the image. The filter values look like circularly symmetric blob. 	*/		
	  
void filters(Mat original)
{
 //Median filter
  Mat Median;
  Mat box; 
  Mat Gauss;
  float boxdata[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
  float Gaussdata[9] = { 1, 2, 1, 2, 4, 2, 1, 2, 1 }; 
  original.copyTo(Median);
  original.copyTo(box);
  original.copyTo(Gauss);
  int c = original.cols;
  int r = original.rows;
  for(int x = 1; x<r-1 ; x++)
  {
  	for(int y = 1; y<c-1 ; y++)
  	{
  		vector <int> i;
  		int  o = 0;
  		int boxval = 0;
  		int gaussval = 0;
  		//convolution operation
  		for(int j = -1; j<=1 ; j++)
  		{
  			for(int k = -1; k<=1 ; k++)
  			{
  				int p = x - j;
  				int q = y - k;
  				i.push_back(original.at<uchar>(p,q));
  				boxval = boxval+original.at<uchar>(p,q)*boxdata[o];
  				gaussval = gaussval+original.at<uchar>(p,q)*Gaussdata[o];
  				o++;
  			}
  		}
  		std::sort(i.begin(), i.end());
  		int median = i[4];
  		//normalize the box and gaussian filter orelse it will result in brighter or drarker image
  		boxval = boxval/9;
  		gaussval = gaussval/16;
  		Median.at<uchar>(x,y) = median;
  		box.at<uchar>(x,y) = boxval;
  		Gauss.at<uchar>(x,y) = gaussval;
  	}
  }	
  namedWindow("median_filter", CV_WINDOW_NORMAL );
  namedWindow("box_filter", CV_WINDOW_NORMAL );
  namedWindow("Gaussian_filter", CV_WINDOW_NORMAL );
  namedWindow("original", CV_WINDOW_NORMAL );
  imshow("median_filter",Median);
  imshow("box_filter",box);
  imshow("Gaussian_filter",Gauss);
  imshow("original",original);
  waitKey(0);
}