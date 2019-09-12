#pragma once

#include <iostream>
#include <fstream>
using namespace std;

template<typename T>
class Matrix
{
private:
	bool empty = true;
	int height = 0,width = 0;
	T** data = nullptr;

	void DeleteData();
	void MarkData(int height,int width);

public:
	Matrix() = default;
	Matrix(Matrix& M);
	Matrix(int height,int width);
	Matrix(int height,int width,T d);
	~Matrix();

	void Fill(T d);

	void Resize(const Matrix& matrix);
	void Resize(int height,int width);
	void Resize(int height,int width, T d);

	int Height() const;
	int Width() const;

	const bool IsEmpty() const;
	const Matrix CellProduct(const Matrix& matrix);
	const Matrix Abs();

	T*&     operator [] (int index) const { return data[index]; }
	Matrix& operator =  (const Matrix& right);

	Matrix  operator +  ();
	Matrix& operator += (const Matrix& right);
	Matrix& operator += (const T& right);

	Matrix  operator -  ();
	Matrix& operator -= (const Matrix& right);
	Matrix& operator -= (const T& right);

	template <typename T1> friend const Matrix<T1> operator + (const Matrix<T1>& left, const Matrix<T1>& right);
	template <typename T1> friend const Matrix<T1> operator - (const Matrix<T1>& left, const Matrix<T1>& right);
	template <typename T1> friend const Matrix<T1> operator * (const Matrix<T1>& left, const Matrix<T1>& right);

	template <typename T1> friend const Matrix<bool> operator == (const Matrix<T1>& left, const Matrix<T1>& right);
	template <typename T1> friend const Matrix<bool> operator != (const Matrix<T1>& left, const Matrix<T1>& right);
	template <typename T1> friend const Matrix<bool> operator < (const Matrix<T1>& left, const Matrix<T1>& right);
	template <typename T1> friend const Matrix<bool> operator > (const Matrix<T1>& left, const Matrix<T1>& right);
	template <typename T1> friend const Matrix<bool> operator >= (const Matrix<T1>& left, const Matrix<T1>& right);
	template <typename T1> friend const Matrix<bool> operator <= (const Matrix<T1>& left, const Matrix<T1>& right);

	template <typename T1> friend std::ostream& operator << (std::ostream& out,const Matrix<T1>& matrix);
	template <typename T1> friend std::istream& operator >> (std::istream& in,Matrix<T1>& matrix);

	template <typename T1> friend std::ofstream& operator << (std::ofstream& out,const Matrix<T1>& matrix);
	template <typename T1> friend std::ifstream& operator >> (std::ifstream& in,Matrix<T1>& matrix);
};