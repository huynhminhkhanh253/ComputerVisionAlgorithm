#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
    //Nhap va in ma tran ban dau
    Mat src = (Mat_<float>(6,8) << 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 1, 1, 0, 0, 0,
                                   0, 1, 1, 1, 1, 1, 1, 0,
                                   0, 0, 1, 1, 1, 0, 1, 0,
                                   0, 1, 1, 1, 1, 1, 1, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0);
    //Khoi tao kernel B
    int mor_size = 1;
    Mat kernel = getStructuringElement(MORPH_CROSS,                                           Size(2 * mor_size + 1, 2 * mor_size + 1), Point(1, 1));
    kernel.at<uchar>(1, 0) = 0;
    Mat output1, output2;

    //Tao ma tran flip cua B
    Mat kernel_flipped;
    flip(kernel, kernel_flipped, -1);

    //Ham morphologyEx
    //Tien hanh erode
    morphologyEx(src, output1, MORPH_ERODE, kernel, Point(0, 2), 1, BORDER_CONSTANT, 0);
    //Tien hanh dilate
    morphologyEx(output1, output2, MORPH_DILATE, kernel_flipped, Point(2, 0), 1, BORDER_CONSTANT, 0);

    //In ket qua
    cout << "Matrix after erosing" << endl;
    cout << output1 << endl;
    cout << "Opening using morphologyEx function" << endl;
    cout << output2 << endl;
    return 0;
}
