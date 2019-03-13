#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, const char** argv ){
     Mat src = imread("../images/a.png", CV_LOAD_IMAGE_UNCHANGED);
     if (src.empty()){
          cout << "Error : Image cannot be loaded..!!" << endl;
          return 0;
     }

    //BGR 
    Vec3b a;
    a[0] = 0;
    a[1] = 0;
    a[2] = 0;
    cout << "rows: " << src.rows << endl;
    cout << "cols: " << src.cols << endl;
    for(int i=0; i<src.rows; i++){
        for(int j=0; j<src.cols; j++){
            //if((int)(src.at<Vec3b>(i, j))[0]==0)
            (src.at<Vec3b>(i, j)) = a;
        }
     }
     
     namedWindow("window", CV_WINDOW_NORMAL); //window name 
     imshow("window", src); //show image store in img
     waitKey(0);
     destroyWindow("window");
     return 0;
}