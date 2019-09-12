#include "observer.hpp"

using namespace cv;

Observer::Observer(const string dataFolder):
dataFolder(dataFolder)
{
	brain=new NeuralNetwork(dataFolder);
	preparedData.Resize(brain->x);
	int n=brain->sizeOfImage;
	reducedImageSize=Size(n,n);
}

bool Observer::OpenCapture()
{
	capture.open(0);
	if(capture.isOpened())
	{
		return true;
	}
	else
	{
		cerr <<"ERROR: Can't open video capture" << endl;
		return false;
	}
}

void Observer::ImageProcess()
{
	image.copyTo(showImage);

	int a = processAreaSize;
	processArea = Rect(image.cols/2-a,image.rows/2-a,2*a,2*a);
	rectangle(showImage,processArea,Scalar(0,127,0),4,0);//рисуем прямоугольник
	image(processArea).copyTo(cutImage);
	resize(cutImage,reducedImage,reducedImageSize);

	cvtColor(reducedImage,filteredImage,COLOR_RGB2GRAY);
	resize(filteredImage,restoredImage,restoredImageSize,INTER_LINEAR);
	threshold(filteredImage,filteredImage, 200, 255, THRESH_TRUNC);
}

void Observer::PrepareData()
{
	int n = reducedImageSize.width;
	int iter=0;
	for(int i = 0 ; i < reducedImageSize.height ; i++)
	{
		for (int j = 0; j < reducedImageSize.width; j++)
		{
			preparedData[iter++][0] = filteredImage.at<Vec3b>(i, j)[0];
		}
	}
}

void Observer::Classify()
{
	PrepareData();
	answer = brain->Calculate(preparedData);
}

void Observer::PrintResult()
{
	cout<<"---"<<endl;
	for(int i=0;i<brain->numberOfOutputs;i++)
	{
		cout << i << ") " << brain->answer[i][0] << endl;
	}
	cout<<"---"<<endl;
	cout << answer << endl;
	cout<<endl;
}

void Observer::StartObservation()
{
	if(!OpenCapture())
	{
		return;
	}

	char key = 'a';

	while(key != 27)
	{
		capture >> image;
		if(image.empty())
		{
			cerr << "ERROR: Capture failed" << endl;
			break;
		}
		ImageProcess();
		imshow("Origin",showImage);

		key = waitKey(1);
		if(key == ' ')
		{
			imshow("Pause",cutImage);
			imshow("Filtered",filteredImage);
			imshow("Restored",restoredImage);
			Classify();
			PrintResult();
		}
	}
}
void Observer::StartSaving(int numberOfPictures, const string dataFolder)
{
	string name;

	if(!OpenCapture())
	{
		return;
	}

	for(int i=0;i<numberOfPictures;i++)
	{
		name=to_string(i)+".png";
		capture >> image;
		if(image.empty())
		{
			cerr << "ERROR: Capture failed" << endl;
			break;
		}

		waitKey(1);
		ImageProcess();
		imwrite(dataFolder+name, filteredImage);

		imshow("Origin",showImage);
		imshow("Filtered",filteredImage);
	}
}