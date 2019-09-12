#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <cassert>

#include "observer.hpp"

using namespace std;

bool MatrixIsTrue(const Matrix<bool>& m)
{
	if(m.IsEmpty())
	{
		return false;
	}

	for(int i=0;i<m.Height();i++)
	{
		for(int j=0;j<m.Width();j++)
		{
            if(!m[i][j])
            {

                return false;
            }
		}
	}

	return true;
}

int main(void)
{
	Observer obs("/home/ark/CLionProjects/number recognition/data/learn/");

	string questionsPath = "/home/ark/CLionProjects/number recognition/tests/representation/test_data/questions/";
	string answersPath = "/home/ark/CLionProjects/number recognition/tests/representation/test_data/answers/";

	int n=100;
	int numberOfOuts=obs.brain->classifiers.Height();
	Matrix<number> calc,ans,err,delta(numberOfOuts,1,1e-10);
	string name;
	ifstream ansFile;

	for(int i=0;i<n;i++)
	{
		obs.filteredImage=cv::imread((questionsPath+to_string(i)+".png"),cv::COLOR_RGB2GRAY);
		obs.PrepareData();
		obs.Classify();
		calc=obs.brain->answer;

		ansFile.open((answersPath+to_string(i)+".txt"));
		ansFile >> ans;
		ansFile.close();

		err=ans-calc;
		err=err.Abs();
		assert(MatrixIsTrue(err < delta));
	}

	return 0;
}