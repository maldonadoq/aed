#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char const *argv[]){
    namedWindow("road", WINDOW_NORMAL); //window name 
    Mat src(200, 200, CV_8UC3, Scalar(255,255,255));
    line(src,Point(20,20),Point(180,180),Scalar(110,220,0),2,8);
    line(src,Point(20,180),Point(180,20),Scalar(110,220,0),2,8);
    circle(src, Point(100,100),115,Scalar(0,0,250),1,8,0);
    imshow("road",src); //show image store in img
    waitKey(0);
    destroyWindow("road");
    return 0;
}