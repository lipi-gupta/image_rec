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
Mat Sharpen(Mat img)
{
    int i,j;
    Mat result;
    cvtColor(img,img,CV_BGR2GRAY);
    namedWindow("grayscale",1);
    imshow("grayscale",img);
    waitKey(2000);
    result.create(img.size(),img.type());
    for(j=1;j<img.rows-1;j++){
    uchar* previous=img.ptr<uchar>(j-1);
    uchar* current=img.ptr<uchar>(j);
    uchar* next=img.ptr<uchar>(j+1);
    uchar* output=result.ptr<uchar>(j);
    for(i=1;i<img.cols-1;i++)
    {
        *output++=cv::saturate_cast<uchar>(5*current[i]-current[i-1]-current[i+1]-previous[i]-next[i]);//saturate_cast makes resuting negative
                                                                                                  // pixel value 0 nd values above 255 255
    }
    }
    result.row(0).setTo(cv::Scalar(0));
    result.col(0).setTo(cv::Scalar(0));
    result.row(result.rows-1).setTo(cv::Scalar(0));
    result.col(result.cols-1).setTo(cv::Scalar(0));
    return result;

}
int main()
{
    Mat A;
    Mat B,C;
    A=imread("terry_fox.png",1);
    namedWindow("original",1);
    imshow("original",A);
    waitKey(3000);
    namedWindow("sharpened",1);
    B=Sharpen(A);
    imshow("sharpened",B);
    waitKey(5000);
    return 0;
}
