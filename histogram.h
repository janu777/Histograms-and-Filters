#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
using namespace std;
using namespace cv;
void histograms(Mat original)
{
	Mat bgr[3];
	Mat gray,equigray,equigray2;
	cvtColor(original,gray,COLOR_BGR2GRAY);
	equalizeHist(gray, equigray);
	equalizeHist(equigray, equigray2);
	split(original,bgr); // split the RGB image into 3 channel
	int bins = 255; // number of histogram bins is 256
	float range[] = {0,255}; // range of each RGB channel
	const float* histRange ={range};
	int hist_w = 720; int hist_h = 400;
	Mat bhist,ghist,rhist,grayhist,grayhist2,grayhist3;
	//calulate histograms
	calcHist(&bgr[0],1,0,Mat(),bhist,1,&bins,&histRange);
	calcHist(&bgr[1],1,0,Mat(),ghist,1,&bins,&histRange);
	calcHist(&bgr[2],1,0,Mat(),rhist,1,&bins,&histRange);
	calcHist(&gray,1,0,Mat(),grayhist,1,&bins,&histRange);
	calcHist(&equigray,1,0,Mat(),grayhist2,1,&bins,&histRange);
	calcHist(&equigray2,1,0,Mat(),grayhist3,1,&bins,&histRange);
	Mat histImage(hist_h, hist_w,CV_8UC3,Scalar(0,0,0));
	int binw = cvRound( (double) hist_w/bins);
	//Normalize
	normalize(bhist,bhist,0,histImage.rows,NORM_MINMAX,-1,Mat()); // blue channel
	normalize(ghist,ghist,0,histImage.rows,NORM_MINMAX,-1,Mat()); // green channel
	normalize(rhist,rhist,0,histImage.rows,NORM_MINMAX,-1,Mat()); // red channel
	normalize(grayhist,grayhist,0,histImage.rows,NORM_MINMAX,-1,Mat()); // gray channel (calculated by using luminousity method) 
	normalize(grayhist2,grayhist2,0,histImage.rows,NORM_MINMAX,-1,Mat());
	normalize(grayhist3,grayhist3,0,histImage.rows,NORM_MINMAX,-1,Mat());
	// Lightness Method: Gray_Intensity = (Max(R+G+B)+Min(R+G+B))/2;
	// Average Method: Gray_Intensity = (R+G+B)/3;
	// Luminousity Method: Gray_Intensity = (0.21R+ 0.72G + 0.07B)
	for( int i = 1; i < bins; i++ )
  	{
      line( histImage, Point( binw*(i-1), hist_h - cvRound(bhist.at<float>(i-1)) ) ,
                       Point( binw*(i), hist_h - cvRound(bhist.at<float>(i)) ),
                       Scalar( 255, 0, 0), 2, 8, 0  );
      line( histImage, Point( binw*(i-1), hist_h - cvRound(ghist.at<float>(i-1)) ) ,
                       Point( binw*(i), hist_h - cvRound(ghist.at<float>(i)) ),
                       Scalar( 0, 255, 0), 2, 8, 0  );
      line( histImage, Point( binw*(i-1), hist_h - cvRound(rhist.at<float>(i-1)) ) ,
                       Point( binw*(i), hist_h - cvRound(rhist.at<float>(i)) ),
                       Scalar( 0, 0, 255), 2, 8, 0  );
      //histogram for the gray scale image                 
      line( histImage, Point( binw*(i-1), hist_h - cvRound(grayhist.at<float>(i-1)) ) ,
                       Point( binw*(i), hist_h - cvRound(grayhist.at<float>(i)) ),
                       Scalar( 0, 255, 255), 2, 8, 0  );
      //equialised histogram
      line( histImage, Point( binw*(i-1), hist_h - cvRound(grayhist2.at<float>(i-1)) ) ,
                       Point( binw*(i), hist_h - cvRound(grayhist2.at<float>(i)) ),
                       Scalar( 255, 0, 255), 2, 8, 0  );
      //when histogram equivalisation is applied agian it will still produce the same effect.
      line( histImage, Point( binw*(i-1), hist_h - cvRound(grayhist3.at<float>(i-1)) ) ,
                       Point( binw*(i), hist_h - cvRound(grayhist3.at<float>(i)) ),
                       Scalar( 255, 255, 255), 2, 8, 0  );
  	}
  	/// Display
  	namedWindow("calcHist Demo", CV_WINDOW_NORMAL );
  	imshow("calcHist Demo", histImage );
  	imshow("gray",gray);
  	imshow("equigray",equigray);
  	imshow("equigray2",equigray2);
  	waitKey(0);
}