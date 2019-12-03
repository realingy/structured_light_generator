#include "cv.h"
#include "core/core.hpp"
#include "imgproc/imgproc.hpp"
#include "highgui.h"
#include <opencv2/opencv.hpp>
#include "math.h"
#include "stdio.h"

using namespace cv;
using namespace std;

int main()
{
	//生产前两幅条纹图
	Mat img;
	img.create(1144, 1520, CV_8UC1);
	char filename[100];
	/*for (int n = 0; n < 8;n++)
	{
		sprintf_s(filename, ".//xiangyitiaowen//%d.jpg", n);
		cv::Mat image = imread(filename, 0);
		for (int i = 0; i < 60; i++)
		{
			uchar * const data = img.ptr<uchar>(i);
			for (int j = 0; j < img.cols; j++)
			{
				data[j] = 0;
			}
		}
		for (int i = 0; i < image.rows;i++)
		{
			uchar * const data = img.ptr<uchar>(i+60);
			uchar * const p = image.ptr<uchar>(i);
			for (int j = 0; j < image.cols; j++)
			{
				data[j+120] = p[j];
			}
		}
		for (int i = 0; i < image.rows; i++)
		{
			uchar * const data = img.ptr<uchar>(i+60);
			for (int j = 0; j < 120; j++)
			{
				data[j] = 0;
			}
			for (int j = 120+image.cols; j < img.cols; j++)
			{
				data[j] = 0;
			}
		}
		for (int i = image.rows+60; i < img.rows; i++)
		{
			uchar * const data = img.ptr<uchar>(i);
			for (int j = 0; j < img.cols; j++)
			{
				data[j] = 0;
			}
		}
		sprintf_s(filename, ".//xiangyitiaowen//%d.jpg", n);
		cv::imwrite(filename, img);
	}*/

	/*
	for (int i = 0; i < img.rows;i++)
	{
		uchar * const data = img.ptr<uchar>(i);
		int  m_begin = 0;
		int m_end = 10;
		for (int j = m_begin; j < m_end; j++)
		{
			data[j] = 255;
		}
		m_begin = m_end;
		m_end += 20;
		for (int j = m_begin; j < m_end; j++)
		{
			data[j] = 0;
		}
		for (int n = 1; n < 33;n++)
		{
			m_begin = m_end;
			m_end += 20;
			if (m_end>img.cols)
			{
				m_end = img.cols;
			}
			for (int j = m_begin; j < m_end; j++)
			{
				data[j] = 255;
			}
			m_begin = m_end;
			m_end += 20;
			if (m_end > img.cols)
			{
				m_end = img.cols;
			}
			for (int j = m_begin; j < m_end; j++)
			{
				data[j] = 0;
			}
		}
	}
	*/

	/*
	int m_begin = 0;
	int m_end = 8;
	for (int i = m_begin; i < m_end; i++)
	{
		uchar * const data = img.ptr<uchar>(i);
		for (int j = 0; j < img.cols; j++)
		{
			data[j] = 255;
		}
	}

	m_begin = m_end;
	m_end += 16;
	for (int i = m_begin; i < m_end; i++)
	{
		uchar * const data = img.ptr<uchar>(i);
		for (int j = 0; j < img.cols; j++)
		{
			data[j] = 0;
		}
	}

	for (int n = 0; n < 32;n++)
	{
		m_begin = m_end;
		m_end += 16;
		if (m_end>img.rows)
		{
			m_end = img.rows;
		}
		for (int i = m_begin; i < m_end;i++)
		{
			uchar * const data = img.ptr<uchar>(i);
			for (int j = 0; j < img.cols;j++)
			{
				data[j] = 255;
			}
		}
		m_begin = m_end;
		m_end += 16;
		if (m_end > img.rows)
		{
			m_end = img.rows;
		}
		for (int i = m_begin; i < m_end; i++)
		{
			uchar * const data = img.ptr<uchar>(i);
			for (int j = 0; j < img.cols; j++)
			{
				data[j] = 0;
			}
		}
	}
	*/

	/*
	//读入条纹图，生产反条纹图
	for(int k = 0; k < 8;k++)
	{
		Mat image;
		sprintf_s(filename, ".//%d.jpg", k);
		image = cv::imread(filename, 0);
		for (int i = 0; i < image.rows;i++)
		{
			for (int j = 0; j < image.cols;j++)
			{
				image.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);
			}
		}
		sprintf_s(filename, ".//%d.jpg", k + 8);
		cv::imwrite(filename, image);
	}
	*/

	
	//for (int i = 0; i < img.rows; i++)
	//{
	//	for (int j = 0; j < img.cols / 4; j++)
	//	{
	//		img.at<char>(i, j) = 255;
	//	}
	//	for (int j = img.cols / 4; j < img.cols*(0.75); j++)
	//	{
	//		img.at<char>(i, j) = 0;
	//	}
	//	for (int j = 0.75*img.cols; j < img.cols; j++)
	//	{
	//		img.at<char>(i, j) = 255;
	//	}
	//}			//数列结构光
	//for (int i = 0; i < img.rows / 4;i++)
	//{
	//	for (int j = 0; j < img.cols;j++)
	//	{
	//		img.at<char>(i, j) = 255;
	//	}
	//}
	//for (int i = img.rows / 4; i < 0.75*img.rows ; i++)
	//{
	//	for (int j = 0; j < img.cols; j++)
	//	{
	//		img.at<char>(i, j) = 0;
	//	}
	//}
	//for (int i = 0.75*img.rows ; i < img.rows; i++)
	//{
	//	for (int j = 0; j < img.cols; j++)
	//	{
	//		img.at<char>(i, j) = 255;
	//	}
	//}
	//imshow("dd", img);
	//imwrite(".//StructureLight//12.jpg", img);
	//waitKey(0);

	/* 压缩生产格雷条纹  */
	/*
	Mat result, roiImage1, roiImage2, roiImage3, roiImage4;
	char filename[100];
	for (int i = 2; i < 8;i++)
	{
		sprintf_s(filename, ".//%d.jpg", i);
		result = imread(".//template1.jpg");
		Mat img = imread(filename);

		pyrDown(img, img, Size(img.cols / 2, img.rows / 2));
		roiImage1 = result(cv::Rect(0, 0, img.cols, img.rows));
		roiImage2 = result(cv::Rect(img.cols, 0, img.cols, img.rows));
		roiImage3 = result(cv::Rect(0, img.rows, img.cols, img.rows));
		roiImage4 = result(cv::Rect(img.cols, img.rows, img.cols, img.rows));

		addWeighted(roiImage1, 0, img, 1, 0, roiImage1);
		addWeighted(roiImage2, 0, img, 1, 0, roiImage2);
		addWeighted(roiImage3, 0, img, 1, 0, roiImage3);
		addWeighted(roiImage4, 0, img, 1, 0, roiImage4);
		sprintf_s(filename, ".//tiaowentu//%d.jpg", i+1);
		imwrite(filename, result);
		waitKey(100);
	}
	*/

	return 0;

}