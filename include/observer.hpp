//
// Created by ark on 02.06.19.
//

#ifndef NUMBER_RECOGNITION_OBSERVER_HPP
#define NUMBER_RECOGNITION_OBSERVER_HPP

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

#include "nnw.hpp"

class Observer
{
	public:
	Matrix<number> preparedData;
	NeuralNetwork* brain;
	string answer;
	string dataFolder;

	int processAreaSize = 120;
	cv::Rect processArea;
	cv::Size reducedImageSize;
	cv::Size restoredImageSize = cv::Size(300,300);
	cv::VideoCapture capture;
	cv::Mat image;
	cv::Mat showImage;
	cv::Mat cutImage;
	cv::Mat reducedImage;
	cv::Mat filteredImage;
	cv::Mat restoredImage;

	bool OpenCapture();
	void ImageProcess();
	void SaveImage();

	void PrepareData();
	void Classify();
	void PrintResult();

	public:
	Observer(const string dataFolder);
	Observer();

	void StartObservation();
	void StartSaving(int numberOfPictures, const string dataFolder);

};

#endif //NUMBER_RECOGNITION_OBSERVER_HPP