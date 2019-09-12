#pragma once

#include <sstream>
#include <string>
#include <map>
#include <cmath>

#include "matrix.hpp"
#include "matrix.cpp"

using namespace std;

typedef double number;

class NeuralNetwork
{
	public:
		int sizeOfImage;
		int numberOfPixels;
		int numberOfNeurons;
		int numberOfOutputs;

	public:
		Matrix<number> bias1,bias2;
		Matrix<number> weights1,weights2;
		Matrix<number> ranges;
		Matrix<string> classifiers;

		Matrix<number> x;
		Matrix<number> answer;

		void NormaliseInput();
		void NormaliseAnswer();
		const Matrix<number> ActivationFunction(const Matrix<number>& input);    //Активационная функция
		int MakeDecision();    //По результатам вычислений принимает решение какой классификатор выбрать(0,1,2 ...) или не выбирать никакой(-1).

	public:
		NeuralNetwork(const string folderPath, const map<string,string> matrices_files);
		NeuralNetwork(const string learnFolderPath);
		NeuralNetwork();

		const Matrix<number> LastAnswer();
		const Matrix<number> LastInput();
		const Matrix<string> Classifiers();
		const string Info();

		const string Calculate(const Matrix<number>& input);    //Вычисляет значение выхода нейросети по заданному входу.

};