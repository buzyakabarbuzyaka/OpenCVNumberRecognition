#include "matrix.hpp"

/*template <typename T>
Vector<T>::Vector(int length)
{
	n=length;
	data= new T[n];
}

template<typename T>
Vector<T>::Vector(int length,T d)
{
	n=length;
	data= new T [n];
	Fill(d);
}

template<typename T>
Vector<T>::~Vector()
{
	delete[] data;
}

template<typename T>
void Vector<T>::Fill(T d)
{
	for(int i=0;i<n;i++)
		data[i]=d;
}

template<typename T>
int Vector<T>::Size()
{
	return n;
}*/

template<typename T>
void Matrix<T>::DeleteData()
{
	if(!empty)
	{
		for (int i = 0; i < height; i++)
		{
			delete[] data[i];
		}

		delete[] data;

		data=nullptr;
		empty=true;
	}
}

template<typename T>
void Matrix<T>::MarkData(int height_,int width_)
{
	if(height_>0 && width_>0)
	{
		empty = false;

		height = height_;
		width = width_;

		data = new T *[height];
		for (int i = 0; i < height; i++)
		{
			data[i] = new T[width];
		}
	}
}

template<typename T>
Matrix<T>::Matrix(Matrix<T>& M)
{
	MarkData(M.Height(),M.Width());

	for(int i=0;i<M.Height();i++)
	{
		for (int j=0;j<M.Width();j++)
		{
			(*this)[i][j]=M[i][j];
		}
	}
}

template<typename T>
Matrix<T>::Matrix(int height_,int width_)
{
	MarkData(height_,width_);
}

template<typename T>
Matrix<T>::Matrix(int height_,int width_,T d)
{
	MarkData(height_,width_);
	Fill(d);
}

template<typename T>
Matrix<T>::~Matrix()
{
	DeleteData();
}

template<typename T>
void Matrix<T>::Fill(T d)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			data[i][j] = d;
		}
	}
}

template<typename T>
void Matrix<T>::Resize(const Matrix<T>& matrix)
{
	DeleteData();
	MarkData(matrix.height,matrix.width);
}

template<typename T>
void Matrix<T>::Resize(int height_,int width_)
{
	DeleteData();
	MarkData(height_,width_);
}

template<typename T>
void Matrix<T>::Resize(int height_,int width_,T d)
{
	DeleteData();
	MarkData(height_,width_);
	Fill(d);
}

template<typename T>
int Matrix<T>::Height() const
{
	return height;
}

template<typename T>
int Matrix<T>::Width() const
{
	return width;
}

template <typename T>
Matrix<T>& Matrix<T>::operator= (const Matrix<T> &right)
{
	if(this!=&right)
	{
		this->DeleteData();
		this->MarkData(right.Height(),right.Width());

		if(empty)
		{
			return (*this);
		}

		for (int i = 0; i < right.Height(); i++)
		{
			for (int j = 0; j < right.Width(); j++)
			{
				data[i][j] = right[i][j];
			}
		}
	}

	return (*this);
}

template <typename T>
Matrix<T> Matrix<T>::operator + ()
{
	return Matrix(*this);
}

template <typename T>
Matrix<T>& Matrix<T>::operator += (const Matrix& right)
{
	if(((*this).Height()==right.Height()) && ((*this).Width()==right.Width()))
	{
		if(empty)
		{
			return (*this);
		}

		for(int i=0;i<right.Height();i++)
		{
			for(int j=0;j<right.Width();j++)
			{
				(*this)[i][j]+=right[i][j];
			}
		}
	}
	else
	{
		std::cerr<<"+: Matrices must be same size"<<std::endl;
	}

	return (*this);
}

template <typename T>
Matrix<T>& Matrix<T>::operator += (const T& right)
{
	if(empty)
	{
		return (*this);
	}

	for(int i=0;i<(*this).Height();i++)
	{
		for(int j=0;j<(*this).Width();j++)
		{
			(*this)[i][j]+=right;
		}
	}

	return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator - ()
{
	return Matrix(*this);
}

template <typename T>
Matrix<T>& Matrix<T>::operator -= (const Matrix& right)
{
	if(((*this).Height()==right.Height()) && ((*this).Width()==right.Width()))
	{
		if(empty)
		{
			return (*this);
		}

		for(int i=0;i<right.Height();i++)
		{
			for(int j=0;j<right.Width();j++)
			{
				(*this)[i][j]-=right[i][j];
			}
		}
	}
	else
	{
		std::cerr<<"-: Matrices must be same size"<<std::endl;
	}

	return (*this);
}

template <typename T>
Matrix<T>& Matrix<T>::operator -= (const T& right)
{
	if(empty)
	{
		return (*this);
	}

	for(int i=0;i<(*this).Height();i++)
	{
		for(int j=0;j<(*this).Width();j++)
		{
			(*this)[i][j]-=right;
		}
	}

	return *this;
}

template<typename T1>
std::ostream& operator << (std::ostream &out,const Matrix<T1> &matrix)
{
	if(matrix.data != nullptr)
	{
		for (int i = 0; i < matrix.Height(); i++)
		{
			for (int j = 0; j < matrix.Width(); j++)
			{
				out << matrix[i][j] << " ";
			}
			out << std::endl;
		}
	}
	return out;
}

template<typename T1>
std::istream& operator >> (std::istream &in,Matrix<T1> &matrix)
{
	int height_,width_;
	in >> height_ >> width_;
	matrix.Resize(height_,width_);

	for(int i=0;i < matrix.Height();i++)
	{
		for(int j=0;j < matrix.Width();j++)
		{
			in >> matrix[i][j];
		}
	}

	return in;
}

template<typename T1>
std::ofstream& operator << (std::ofstream &out,const Matrix<T1> &matrix)
{
	out << matrix.Height() << " " << matrix.Width() << std::endl;

	if(!matrix.empty)
	{
		for (int i = 0; i < matrix.Height(); i++)
		{
			for (int j = 0; j < matrix.Width(); j++)
			{
				out << matrix[i][j] << " ";
			}
			out<<std::endl;
		}
	}
	return out;
}

template<typename T1>
std::ifstream& operator >> (std::ifstream &in,Matrix<T1> &matrix)
{
	int height_,width_;
	in >> height_ >> width_;
	matrix.Resize(height_,width_);

	if(!matrix.empty)
	{
		for (int i = 0; i < matrix.Height(); i++)
		{
			for (int j = 0; j < matrix.Width(); j++)
			{
				in >> matrix[i][j];
			}
		}
	}

	return in;
}

template <typename T1>
const Matrix<T1> operator + (const Matrix<T1>& left, const Matrix<T1>& right)
{
	Matrix<T1> tmp;

	if((left.Height()==right.Height()) && (left.Width()==right.Width()))
	{
		tmp.Resize(left.Height(),left.Width());

		for(int i=0;i<left.Height();i++)
		{
			for(int j=0;j<left.Width();j++)
			{
				tmp[i][j]=left[i][j]+right[i][j];
			}
		}
	}
	else
	{
		std::cerr<<"+: Matrices must be same size"<<std::endl;
	}
	return tmp;
}

template <typename T1>
const Matrix<T1> operator - (const Matrix<T1>& left, const Matrix<T1>& right)
{
	Matrix<T1> tmp;

	if((left.Height()==right.Height()) && (left.Width()==right.Width()))
	{
		tmp.Resize(left.Height(),left.Width());

		for(int i=0;i<left.Height();i++)
		{
			for(int j=0;j<left.Width();j++)
			{
				tmp[i][j]=left[i][j]-right[i][j];
			}
		}
	}
	else
	{
		std::cerr<<"-: Matrices must be same size"<<std::endl;
	}
	return tmp;
}

template <typename T1>
const Matrix<T1> operator * (const Matrix<T1>& left, const Matrix<T1>& right)
{
	Matrix<T1> tmp;

	if(left.Width()==right.Height())
	{
		tmp.Resize(left.Height(),right.Width());

		for(int i=0;i<tmp.Height();i++)
		{
			for(int j=0;j<tmp.Width();j++)
			{
				T1 sum=0;
				for(int k=0;k<left.Width();k++)
				{
					sum+=left[i][k]*right[k][j];
				}
				tmp[i][j]=sum;
			}
		}
	}
	else
	{
		std::cerr<<"*: Error in Matrices sizes"<<std::endl;
	}
	return tmp;
}

template <typename T>
const Matrix<T> Matrix<T>::CellProduct(const Matrix<T>& matrix)
{
	Matrix<T> tmp;

	if((this->Height()==matrix.Height()) && (this->Width()==matrix.Width()))
	{
		if(this->empty)
		{
			return tmp;
		}

		tmp.Resize(matrix.Height(),matrix.Width());

		for(int i=0;i<matrix.Height();i++)
		{
			for(int j=0;j<matrix.Width();j++)
			{
				tmp[i][j]=(*this)[i][j]*matrix[i][j];
			}
		}
	}
	else
	{
		std::cerr<<".*: Matrices must be same size"<<std::endl;
	}

	return tmp;
}

template <typename T>
const Matrix<T> Matrix<T>::Abs()
{
	Matrix<T> tmp;

	if(this->empty)
	{
		return tmp;
	}

	tmp.Resize(this->Height(),this->Width());

	for(int i=0;i<this->Height();i++)
	{
		for(int j=0;j<this->Width();j++)
		{
			tmp[i][j]=((*this)[i][j]<0)?-(*this)[i][j]:(*this)[i][j];
		}
	}

	return tmp;
}


template <typename T1>
const Matrix<bool> operator < (const Matrix<T1>& left, const Matrix<T1>& right)
{
	Matrix<bool> tmp;

	if((left.Height()==right.Height()) && (left.Width()==right.Width()))
	{
		if(left.empty)
		{
			return tmp;
		}

		tmp.Resize(right.Height(),right.Width());

		for(int i=0;i<right.Height();i++)
		{
			for(int j=0;j<right.Width();j++)
			{
				tmp[i][j]=left[i][j]<right[i][j];
			}
		}
	}
	else
	{
		std::cerr<<".*: Matrices must be same size"<<std::endl;
	}

	return tmp;
}

template <typename T>
const bool Matrix<T>::IsEmpty() const
{
	return this->empty;
}