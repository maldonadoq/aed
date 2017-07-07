#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <unistd.h>
#include <sys/time.h>
#include <utility>
#include <thread>

using namespace cv;
using namespace std;

static int th = 4;

class pixel{
public:
	Vec3b b;
	queue<pair<int,int>> q;
	bool ** rs;
	Mat src;
	pixel(Mat x){	
		this->src = x;
		this->rs = new bool*[src.rows];
		for(int i=0; i<src.rows; i++)	rs[i] = new bool[src.cols];
	}

	void print(){
		cout << "rows:	" << src.rows << endl;
		cout << "cols:	" << src.cols << endl;
		cout << "pixel:	" << src.cols*src.rows << endl;
	}

	void find(){
		for(int i=0; i<src.rows; i++)
			for(int j=0; j<src.cols; j++){
				if((int)(src.at<Vec3b>(i, j))[0]==0){
					q.push(make_pair(i,j));
					rs[i][j] = true;
					continue;
				}
				rs[i][j] = false;
			}
	}

	void cmp(pair<int,int> &tm, Vec3b a){
		if(tm.first<=src.rows-2 and !rs[tm.first+1][tm.second]){
			src.at<Vec3b>(tm.first+1,tm.second) = a;
			rs[tm.first+1][tm.second] = true;
			q.push(make_pair(tm.first+1,tm.second));
		}
		if(tm.first>=1 and !rs[tm.first-1][tm.second]){
			rs[tm.first-1][tm.second] = true;
			src.at<Vec3b>(tm.first-1,tm.second) = a;
			q.push(make_pair(tm.first-1,tm.second));
		}
		if(tm.second<=src.cols-2 and !rs[tm.first][tm.second+1]){
			rs[tm.first][tm.second+1] = true;
			src.at<Vec3b>(tm.first,tm.second+1) = a;
			q.push(make_pair(tm.first,tm.second+1));
		}
		if(tm.second>=1 and !rs[tm.first][tm.second-1]){
			rs[tm.first][tm.second-1] = true;
			src.at<Vec3b>(tm.first,tm.second-1) = a;
			q.push(make_pair(tm.first,tm.second-1));
		}
	}

	void bfs(){
		queue<pair<int, int>> tr;
		namedWindow("window_color", WINDOW_NORMAL); //window name 
     	
     	struct timeval ti, tf;
    	double tiempo;
    	gettimeofday(&ti, NULL);

    	thread h[th];
		Vec3b a;
		unsigned t;
		while(!q.empty()){
			for(int j=0; j<3; j++)	a[j] = rand()%256;
			t = q.size();
			/*for(unsigned i=0; i<t; i++){
				for(int k=0; k<th; k++){	h[k]=thread(&pixel::cmp,q.front(),a);	q.pop();	}
				for(int k=0; k<th; k++)	h[k].join();
			}
			unsigned ew = t/th;
			for(unsigned k=0+(ew*th); k<t; k++){	cmp(q.front(),a); q.pop();	}*/
			for(unsigned i=0; i<t; i++){	cmp(q.front(),a);	q.pop();	}
		}
		gettimeofday(&tf, NULL);
    	tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
    	printf("time dfs: %.8lf\n",tiempo/1000);

		imshow("window_color",src); //show image store in img
     	waitKey(0);
     	destroyWindow("window_color");
	}

	~pixel(){	}
};

int main(int argc, char const *argv[]){
	Mat src = imread("../images/h.png", CV_LOAD_IMAGE_UNCHANGED);
    if(src.empty()){
        cout << "Error : Image cannot be loaded..!!" << endl;
        return 0;
    }
   	namedWindow("window", WINDOW_NORMAL); //window name 
    imshow("window",src); //show image store in img

    pixel *a = new pixel(src);
    a->print();	a->find();	a->bfs();
    waitKey(0);
    destroyWindow("window");
   	delete a;
	return 0;
}

/*	
	134217728
	44510000 	15.08800000
	80840000	21.53200000
	320000000	38.77000000
*/

/*
https://lihuen.linti.unlp.edu.ar/index.php/C%C3%B3mo_usar_GDB
	gdb a.out
	(gdb) list or l
	(gdb) run
	(gdb) backtrace
	(gdb)
	(gdb)

t's easy to simply copy and paste this:

$ sudo add-apt-repository "deb http://dl.google.com/linux/chrome/deb/ stable main"
$ wget -q -O - https://dl-ssl.google.com/linux/linux_signing_key.pub | sudo apt-key add -
$ sudo apt-get update
$ sudo aptitude install google-chrome-stable

And finally, lunch Google Chrome
$ google-chrome
sudo swapoff -a ; sudo swapon -a
*/