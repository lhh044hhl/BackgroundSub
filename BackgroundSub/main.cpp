#include<opencv.hpp>;
using namespace std;
using namespace cv;
//Text1
/*int main() {
	VideoCapture cap(0);
	int cnt=0;
	Mat frame,bgMat,subMat, bny_submat;
	while (1) {
		cap >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);

		if (cnt == 0) {
			frame.copyTo(bgMat);
		}
		else {
			absdiff(frame, bgMat, subMat);
			threshold(subMat, bny_submat, 50, 255, CV_THRESH_BINARY);

			imshow("b_subMat", bny_submat);
			imshow("subMat", subMat);
			imshow("subMat", frame);
			waitKey(30);
		}
		cnt++;
	}
}*/

//Text2
int main() {
	VideoCapture cap(0);

	vector<Mat> srcMat;

	int n = 200;
	float r = 2.8;
	int cnt = 0;
	Mat frame, meanMat, varMat, dstMat;

	while (1) {
	
		cap >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);

		if (cnt < n) {
			srcMat.push_back(frame);

			if (cnt == 0) {
				cout << "ÕýÔÚ¶ÁÈ¡" << endl;
			}
		}
	
		else if (cnt == n) {
			meanMat.create(frame.size(), CV_8UC1);
			varMat.create(frame.size(), CV_32FC1);
			calcGaussianB(srcMat,meanMat,varMat);
		}
		else {
			dstMat.create(frame.size(), CV_8UC1);
			gaussianThreshold(frame, meanMat, varMat, r, dstMat);
			imshow("result", dstMat);
			imshow("frame", frame);
			waitKey(0);

		}
		cnt++;
	}


}
int calcGaussianB(vector<Mat> srcMat, Mat&meanMat, Mat&varMat) {
	int cols = srcMat[0].cols;
	int rows = srcMat[0].rows;
	int sum = 0;
	float var = 0;

	for (int n = 0; n < rows; n++) {
		for (int m = 0; m < cols; m++) {
			for (int i = 0; i < srcMat.size(); i++) {
				sum += srcMat[i].at<uchar>(n, m);
			}
			meanMat.at<uchar>(n, m) = sum / srcMat.size();
			for (int i = 0; i < srcMat.size(); i++) {
				var += pow((srcMat[i].at<uchar>(n, m) - meanMat.at<uchar>(n, m)), 2);
			}
			varMat.at<float>(n, m) = var / srcMat.size();
		}
	
	}
	return 0;
}

int gaussianThreshold(Mat srcMat, Mat meanMat, Mat varMat, float weight, Mat&dstMat) {
	int src, mean, dst;
	int cols = srcMat.cols;
	int rows = srcMat.rows;

	for (int n = 0; n < rows; n++) {
		for (int m = 0; m < cols; m++) {
			src = srcMat.at<uchar>(n, m);
			mean = meanMat.at<uchar>(n, m);
			int dif = abs(src - mean);
			int th = weight * varMat.at<float>(n, m);

			if (dif > th) {
				dstMat.at<uchar>(n, m) = 255;
			}
			else {
				dstMat.at<uchar>(n, m) = 0;
			};
		}
	}
}