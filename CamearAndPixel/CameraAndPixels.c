#include <opencv2/opencv.hpp>
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include <stdint.h>

using namespace cv;
using namespace std;

void histogram(string const& name, Mat const& Image)
{
	int bin = 256;
	int histsize[] = { bin };
	float range[] = { 0, 255 };
	const float* ranges[] = { range };
	Mat hist;

	int chanel[] = { 0 };
	int hist_heigt = 256;
	Mat hist_image = Mat::zeros(hist_heigt, bin, CV_8SC3);

	calcHist(&Image, 1, chanel, Mat(), hist, 1, histsize, ranges, true, false);

	double max_val = 0;
	minMaxLoc(hist, 0, &max_val);

	for (int i = 0; i < bin; i++)
	{
		float binV = hist.at<float>(i);
		int a = binV * hist_heigt;
		int height = cvRound(a / max_val);
		line(hist_image, Point(i, hist_heigt - height), Point(i, hist_heigt), Scalar::all(255));
	}

	imshow(name, hist_image);
}


int bai1(int argv, char** argc)
{
	float anh[25] = { 20, 30, 40, 10, 20,
			  10, 80, 90, 100, 60,
			 50, 150, 160, 170, 30,
			30, 220, 230, 240, 50,
			40, 60, 30, 40, 20 };

	Mat gray_anh = Mat(5, 5, CV_32F, anh);
	Mat gray_anh_his;

	gray_anh.convertTo(gray_anh, CV_8UC1);

	equalizeHist(gray_anh, gray_anh_his);

	cout << "matrix = " << endl << "" << gray_anh << endl << endl;
	cout << "Matrix_hist_256 = " << endl << "" << gray_anh_his << endl << endl;
	cout << "Matrix_hist_50 = " << endl << "" << gray_anh_his *49/255 << endl << endl;

	histogram("Hist_old", gray_anh);
	histogram("Hist_new", gray_anh_his);

	waitKey(0);
}

int bai2(int argc, char** argv)
{
// Load 2 hình, một hình không có cánh tay và một hình có:
	Mat nohand = imread("nohand.png");
	Mat hand = imread("hand.png");
// Tạo ma trận zero
	Mat m0 = Mat::zeros(nohand.rows, nohand.cols, CV_8UC1); 
// Resize 2 hình:
	resize(hand, hand, Size(nohand.size().width, nohand.size().height));				
	int hang = nohand.rows;
	int cot = nohand.cols;
	float euclid_dis;									
// Tính khoảng cánh Euclid		
	for (int i = 0; i < hang; i++) {
		for (int j = 0; j < cot; j++) {
			Vec3b a = nohand.at<Vec3b>(i, j);
			Vec3b b = hand.at<Vec3b>(i, j);
			euclid_dis = sqrt(((a[0] - b[0]) * (a[0] - b[0])) + ((a[1] - b[1]) * (a[1] - b[1])) + ((a[2] - b[2]) * (a[2] - b[2])));
			m0.at<uint8_t>(i, j) = euclid_dis;
		}
	}
// Show 3 ảnh:
	imshow("nohand", nohand);
	imshow("hand", hand);
	imshow("m0", m0);
	waitKey(0);
	return 0;
}

int bai3(int argc, char** argv)
{
// Load 2 hình, một hình không có cánh tay và một hình có:
	Mat nohand = imread("nohand.png");
	Mat hand = imread("hand.png");
// Tạo ma trận zero:
	Mat m0 = Mat::zeros(nohand.rows, nohand.cols, CV_8UC1);
// Resize 2 hình:
	resize(hand, hand, Size(nohand.size().width, nohand.size().height));
	int hang = nohand.rows;
	int cot = nohand.cols;
	float euclid_dis;
//Set giá trị threshold để thấy cánh tay:
	float threshold = 47;
//Tính khoảng cách euclid

	for (int i = 0; i < hang; i++) {
		for (int j = 0; j < cot; j++) {
			Vec3b a = nohand.at<Vec3b>(i, j);				
			Vec3b b = hand.at<Vec3b>(i, j);
			euclid_dis = sqrt(((a[0] - b[0]) * (a[0] - b[0])) + ((a[1] - b[1]) * (a[1] - b[1])) + ((a[2] - b[2]) * (a[2] - b[2])));
//Lưu điểm ảnh được tăng sáng vào ma trận zero:	
			if (euclid_dis > threshold)
			{
				m0.at<unsigned char>(i, j) = 255;
			}
		}
	}
//Hiển thị hình ảnh cánh tay:
	imshow("result", m0);
	waitKey(0);
	return 0;
}

enum {
	CV_ADAPTIVE_THRESH_MEAN_C = 0,
	CV_ADAPTIVE_THRESH_GAUSSIAN_C = 1,
	CV_BGR2GRAY = 6
};

void bai4() {
	//Input data as a 2D integer matrix
	int data[6][7] = { {1,2,7,40,5,6,7}, {8,7,9,11,40,13,14},{11,40,40,40,6,40,9}, { 8,7,40,10,7,10,15}, {10,2,4,40,10,7,8}, {1,2,7,4,5,7,7} };
	//Initialize 2D integer matrix
	cv::Mat dst(6,7, CV_8UC1), src(6,7, CV_8UC1);
	int i, j;
	//Input data from 2D int matrix to Mat
	for (i = 0; i < src.rows; i++) {
		for (j = 0; j < src.cols; j++) {
			src.at<uchar>(i, j) = data[i][j];
		}
	}
	//Print Mat data to screen
	std::cout << src << endl<<endl;
	//Threshold Mat's data
	cv::adaptiveThreshold(src, dst, 1, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, 0);
	//Print Threshold matrix to screen
	std::cout << dst << endl;
	waitKey(0);
}


int bai5(){
	//KHOI TAO MA TRAN
	int mtr[5][5] ={{20,30,40,10,20},
					{10,80,90,100,60},
					{50,150,160,170,30},
					{30,220,230,240,50},
					{40,60,30,40,20}};
	Mat src(5, 5, CV_8UC1);
	int i, j;
	cout << "MA TRAN BAN DAU:" << endl;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			src.at<uint8_t>(i, j) = mtr[i][j];
		}
	}
	//IN MA TRAN RA MAN HINH
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			cout << "\t" << (int)src.at<uint8_t>(i, j);
		}
		cout << endl;
	}
	//TINH T THEO PHUONG PHAP OTSU
	Mat dst;
	double thresh = 0;
	double maxValue = 255;
	long double thres = threshold(src, dst, thresh, maxValue, THRESH_OTSU);
	cout << "T = " << thres << endl;
	//THUC HIEN THRESHOLD
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (src.at<uint8_t>(i, j) > thres)
				src.at<uint8_t>(i, j) = 255;
			else
				src.at<uint8_t>(i, j) = 0;
		}
	}
	//KET QUA THRESHOLD
	cout << "MA TRAN SAU KHI THRESHOLD THEO PP OTSU:" << endl;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			cout << "\t" << (int)src.at<uint8_t>(i, j);
		}
		cout << endl;
	}
	return 0;
}





