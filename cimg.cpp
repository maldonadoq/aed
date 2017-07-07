#include "CImg.h"

using namespace cimg_library;

int main() {
    CImg<unsigned char> image("../images/b.png");
    image.display("asd");
    //CImgDisplay main_disp(image,"sws");
    //while (!main_disp.is_closed()) {    main_disp.wait();   }
    return 0;
}