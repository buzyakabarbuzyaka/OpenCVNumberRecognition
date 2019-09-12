#include "nnw.hpp"

NeuralNetwork::NeuralNetwork()
{
	ifstream in;

	in.open("../data/learn/bias1.txt");
	in>>bias1;
	in.close();

	in.open("../data/learn/bias2.txt");
	in>>bias2;
	in.close();

	in.open("../data/learn/weights1.txt");
	in>>weights1;
	in.close();

	in.open("../data/learn/weights2.txt");
	in>>weights2;
	in.close();

	in.open("../data/learn/ranges.txt");
	in>>ranges;
	in.close();

	in.open("../data/learn/classifiers.txt");
	in>>classifiers;
	in.close();


	numberOfNeurons=bias1.Height();
	numberOfOutputs=bias2.Height();
	numberOfPixels=ranges.Height();
	sizeOfImage=sqrt(numberOfPixels);

	x.Resize(numberOfPixels,1);
}

NeuralNetwork::NeuralNetwork(const string folderPath, const map<string,string> matrices_files)
{
	ifstream in;

	in.open(folderPath+matrices_files.at("bias1"));
	in>>bias1;
	in.close();

	in.open(folderPath+matrices_files.at("bias2"));
	in>>bias2;
	in.close();

	in.open(folderPath+matrices_files.at("weights1"));
	in>>weights1;
	in.close();

	in.open(folderPath+matrices_files.at("weights2"));
	in>>weights2;
	in.close();

	in.open(folderPath+matrices_files.at("ranges"));
	in>>ranges;
	in.close();

	in.open(folderPath+matrices_files.at("classifiers"));
	in>>classifiers;
	in.close();


	numberOfNeurons=bias1.Height();
	numberOfOutputs=bias2.Height();
	numberOfPixels=ranges.Height();
	sizeOfImage=sqrt(numberOfPixels);

	x.Resize(numberOfPixels,1);
}

NeuralNetwork::NeuralNetwork(const string learnFolderPath)
{
	ifstream in;

	in.open(learnFolderPath+"bias1.txt");
	in>>bias1;
	in.close();

	in.open(learnFolderPath+"bias2.txt");
	in>>bias2;
	in.close();

	in.open(learnFolderPath+"weights1.txt");
	in>>weights1;
	in.close();

	in.open(learnFolderPath+"weights2.txt");
	in>>weights2;
	in.close();

	in.open(learnFolderPath+"ranges.txt");
	in>>ranges;
	in.close();

	in.open(learnFolderPath+"classifiers.txt");
	in>>classifiers;
	in.close();

	numberOfNeurons=bias1.Height();
	numberOfOutputs=bias2.Height();
	numberOfPixels=ranges.Height();
	sizeOfImage=sqrt(numberOfPixels);

	x.Resize(numberOfPixels,1);
}

const Matrix<number> NeuralNetwork::LastAnswer()
{
	return answer;
}

const Matrix<number> NeuralNetwork::LastInput()
{
	return x;
}

const Matrix<string> NeuralNetwork::Classifiers()
{
	return classifiers;
}

const Matrix<number> NeuralNetwork::ActivationFunction(const Matrix<number>& input)
{
	Matrix<number> tmp(input.Height(),input.Width());

	for(int i = 0 ; i < tmp.Height(); i++)
	{
		for (int j = 0; j < tmp.Width(); j++)
		{
			tmp[i][j]=2.0/(1.0+exp(-2.0*input[i][j]))-1.0;
		}
	}

	return tmp;
}

void NeuralNetwork::NormaliseInput()
{
	for(int i=0;i<numberOfPixels;i++)
	{
		if(ranges[i][0] != ranges[i][1])
		{
			x[i][0]=2.0*(x[i][0]-ranges[i][0])/(ranges[i][1]-ranges[i][0])-1.0;
		}
		else
		{
			//x[i][0]=0;
		}
	}
}

void NeuralNetwork::NormaliseAnswer()
{
	for(int i=0;i<numberOfOutputs;i++)
	{
		answer[i][0]=(answer[i][0]+1.0)/2.0;
	}
}

int FindMax(const Matrix<number>& vector)
{
	int index=0;
	for(int i=1;i<vector.Height();i++)
	{
		if(vector[i][0]<vector[index][0])
		{
			index=i;
		}
	}

	return index;
}

int NeuralNetwork::MakeDecision()
{
	return FindMax(answer);
}

const string NeuralNetwork::Calculate(const Matrix<number>& input)
{
	x=input;

	NormaliseInput();

	answer=ActivationFunction(weights1*x+bias1);
	answer=(weights2*answer+bias2);

	NormaliseAnswer();

	int decision=MakeDecision();

	if(decision == -1)
	{
		return "NONE";
	}

	return classifiers[decision][0];
}