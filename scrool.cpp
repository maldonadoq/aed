#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void CallBackFunc(int event, int x, int y, int flags, void* userdata){
	if(event==EVENT_LBUTTONDOWN)
		cout << "Left button (" << x << "," << y << ")" << endl;
	else if(event == EVENT_RBUTTONDOWN)
		cout << "Right button (" << x << "," << y << ")" << endl;
}

int main(int argc, char** argv){
	Mat img = imread("../images/a.png");
	if(img.empty()) { 
		cout << "Error loading the image" << endl;
		return -1; 
    }
	namedWindow("My Window", 1);
	while(true){
		setMouseCallback("My Window", CallBackFunc, NULL);
		//pyrUp(img, img, Size(img.cols * 2, img.rows * 2));
		imshow("My Window", img);
		char key = (char)waitKey();
        if(key==27 || key=='q' || key =='Q')	break;
	}
	//waitKey(0);

	return 0;

}