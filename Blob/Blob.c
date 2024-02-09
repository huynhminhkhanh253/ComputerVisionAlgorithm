//Khai báo thư viện
#include "opencv2/core/core.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  
#include "iostream"
#include "opencv2/opencv.hpp"
#include <math.h>

using namespace cv;
using namespace std;

int bai1(int argc, char** argv)
{
//Khai báo ma trận đầu vào 12x14
	Mat src = (Mat_<uchar>(12, 14) <<
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0,
		0, 0, 255, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0,
		0, 255, 0, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0,
		0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 0,
		0, 0, 255, 0, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0,
		0, 0, 0, 255, 0, 0, 0, 255, 0, 255, 255, 255, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0);
Thêm biên 0 cho ma trận
	copyMakeBorder(src, src, 1, 1, 1, 1, BORDER_CONSTANT, 0); 
	Mat thresh;
	vector<vector<Point>> contour;
	vector<Vec4i> hierachy;
//chuyển ma trận về ảnh nhị phân , tọa độ tâm thì set về giá trị 150
	threshold(src, thresh, 150, 1, THRESH_BINARY);
// Tìm viền cho ma trận đầu vào
	findContours(thresh, contour, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	vector<Moments> mu(contour.size());
	vector<float> theta(contour.size());
	//Tìm moment 
	for (int i = 0; i < contour.size(); i++)
	{
		mu[i] = moments(contour[i], false);
	}
	vector<Point2f> mc(contour.size());
	//Tính trọng tâm và đánh dấu trọng tâm ( set về giá trị 150 ), còn lại giữ nguyên 
	for (int i = 0; i < contour.size(); i++)
	{
		mc[i] = Point2f(mu[i].m10 / (mu[i].m00), mu[i].m01 / (mu[i].m00));
		src.at<uchar>(mc[i]) = 150;
		double u11, u20, u02;
		u11 = mu[i].m11 / (mu[i].m00) - mu[i].m10 * mu[i].m01 / (mu[i].m00 * mu[i].m00);
		u20 = mu[i].m20 / (mu[i].m00) - mu[i].m10 * mu[i].m10 / (mu[i].m00 * mu[i].m00);
		u02 = mu[i].m02 / (mu[i].m00) - mu[i].m01 * mu[i].m01 / (mu[i].m00 * mu[i].m00);
		theta[i] = 0.5 * atan(2.0 * u11 / (u20 - u02)) * 180 / CV_PI;
		cout << "Tam blob " << i << ": " << mc[i] << endl
			<< "Goc blod " << i << ": " << theta[i] << " degree" << endl;
	}

	//Gọi hàm tính chu vi và diện tích
	for (int i = 0; i < contour.size(); i++)
	{
		cout << "Contour: " << i << " Area: " << contourArea(contour[i]) << " Length: " << arcLength(contour[i], true) << endl;
	}
	cout << endl << src << endl;
	namedWindow("Result", WINDOW_NORMAL);
//Hiện thị ma trận kết quả
	imshow("Result", src);
	waitKey(0);
}

int bai2()
{
	//ANH SAU KHI CANNY
	Mat src = (Mat_<uchar>(6, 4) << 255, 0, 0, 255,
					0, 255, 0, 255,
					0, 0, 255, 0,
					0, 0, 0, 255,
					255, 255, 255, 0,
					255, 0, 0, 0);
	cout << "SOURCE:" << endl << src << endl;

	//HAM HoughLinesP
	vector<Vec4i> linesP;
	HoughLinesP(src, linesP, 1, CV_PI / 180.0, 150, 2, 20);
	//VE DUONG THANG
	for (size_t i = 0; i < linesP.size(); i++)
	{
		cout << linesP[i] << endl;
		Vec4i d = linesP[i];
		line(src, Point(d[0], d[1]), Point(d[2], d[3]), Scalar(0, 0, 100), 1, LINE_AA);
	}

	resize(src, src, Size(), 100, 100, INTER_NEAREST);
	imshow("Result", src);
	waitKey(0);
	return 0;
}

int bai3(int argc, char** argv)
{
	Mat src = (Mat_<uint8_t>(5, 6) <<
		0, 0, 255, 0, 0, 0,
		0, 0, 255, 0, 255, 0,
		255, 255, 0, 255, 255, 255,
		0, 0, 255, 0, 255, 0,
		0, 0, 255, 0, 0, 0 );
	//Phan nguong Otsu
	Mat dst2;
	threshold(src, dst2, 0, 255, THRESH_OTSU);
	cout << "dst2 = " << endl << " " << dst2 << endl << endl;
	Mat origin2;
	resize(dst2, origin2, Size(), 50, 50, INTER_NEAREST);
	imshow("Origin2", origin2);
	//Tim duong tron sau phan nguong va ve duong tron
	vector <Vec3f> circles;
	HoughCircles(dst2, circles, HOUGH_GRADIENT, 1.0, 1, 200.0, 2.0, 1, 3);
	for (size_t i = 0; i < circles.size(); i++)
	{
		printf("circle(%d) = ", i);
		cout << "["<< cvRound(circles[i][0])<< "," << cvRound(circles[i][1]) << "," << cvRound(circles[i][2]) << "]" << endl << endl; //Xuat toa do tam , ban kinh
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		circle(dst2, center, radius, Scalar(0, 0, 255), 1, LINE_AA);
	}
	//Show results
	resize(dst2, dst2, Size(), 50, 50, INTER_NEAREST);
	imshow("Houghcircle", dst2);

	waitKey(0);

}


