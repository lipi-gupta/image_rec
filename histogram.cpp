//calculates histogram and and shows graph for histogram and thresholds image on analysis of histogram graph
#include "opencv2/calib3d.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include<iostream>
using namespace std;
using namespace cv;
class Histogram1D
{
private:
    int histSize[1];//no. of bins ex.256
    float hranges[2];//min and max values of pixels
    const float* ranges[1];//pointer to hranges
    int channels[1];// flag for channel
public:
    Histogram1D()   //constructor for class
    {
        histSize[0]=256;
        hranges[0]=0;
        hranges[1]=255;
        ranges[0]=hranges;
        channels[0]=0;
    }
    MatND getHistogram(const Mat &image)//returns 1d array
    {
        MatND hist;
        calcHist(&image,1,channels,Mat(),hist,1,histSize,ranges);
        return hist;      // hist is 1d array which shows no. of pixel corresponding to each shade
    }
    Mat getHistogramImage(const Mat &image)  //returns graph image
    {
    MatND hist=getHistogram(image);
    double maxval=0;  //maximum no. of pixels corresponding to a single value
    double minval=0;  //minimum no.of pixels corresponding to a single value
    minMaxLoc(hist, &minval, &maxval, 0, 0);
    Mat histImg(histSize[0],histSize[0],CV_8U,Scalar(255)); //Mat for graph image
    int hpt=static_cast<int>(.9*histSize[0]); //hpt=230 in this case
    for(int h=0;h<histSize[0];h++)   //draws line for each value in histImg
    {
        float binVal=hist.at<float>(h);
        int intensity= static_cast<int>(binVal*hpt/maxval);
        line(histImg,Point(h,histSize[0]),Point(h,histSize[0]-intensity),Scalar::all(0));// draws line between two points

    }
    return histImg;
    }
};
int main()
{
    Mat A,C,thresholded;
    MatND B;
    int i;
    Histogram1D histo;
    A=imread("bts.png",0);
    namedWindow("original",1);
    imshow("original",A);
    waitKey(2000);
    B=histo.getHistogram(A);
    for(i=0;i<256;i++)
    {
        cout<<"value "<<i<<" "<<B.at<float>(i)<<'\n';
    }
    C=histo.getHistogramImage(A);
    namedWindow("histograph",1);
    imshow("histograph",C);
    waitKey(2000);
    threshold(A,thresholded,95,255,THRESH_BINARY);
    namedWindow("threshold",1);
    imshow("threshold",thresholded);
    waitKey(0);
    return 0;
}
