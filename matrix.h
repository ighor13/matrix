#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

// copyright (c) 2024 Ighor Poteryakhin ighor@ighor.ru

using namespace std;

typedef unsigned int Index;
template <typename Elem> class Matrix
{
    public:
	Matrix();
	Matrix(Index m,Index n);
	Matrix(Index m,Index n, Elem*);
	~Matrix();
	Index m();
	Index n();
	Index m(Index);
	Index n(Index);
	Elem& at(const Index,const Index); // element at (m,n) with index checking, throw(char*) in out of range
	vector<Elem>& operator [] (const Index); // element at [m][n] without index checking
	Matrix& DeleteRow(Index);
	Matrix& DeleteColumn(Index);
	Elem Determinant();
	Elem Minor(Index, Index);
	Matrix<Elem> Transpose();
	Matrix<Elem> Inverse();
	Matrix<Elem> Triangular();
	Matrix<Elem> AddRow(Index,Index,Elem); //row1+=row2*k
	Matrix<Elem> AddColumn(Index,Index,Elem); //col1+=col2*k
	Matrix<Elem> AddRow(Index,Index); // the same k=1
	Matrix<Elem> AddColumn(Index,Index); //the same k=1
	vector<Elem> Row(Index);
	vector<Elem> Column(Index);
    private:
	int pow (int, Index);
	vector<vector<Elem>> data;
};

inline template<typename Elem> int Matrix<Elem>::pow(int x,Index n)
{
    Elem p=1;
    for(Index i=0;i<n;i++)
	p*=x;
    return p;
}

inline template<typename Elem> Matrix<Elem>::Matrix()
{
    ;
}

inline template<typename Elem> Matrix<Elem>::~Matrix()
{
    ;
}

inline template<typename Elem> Matrix<Elem>::Matrix(Index newm, Index newn)
{
    this->m(newm);
    this->n(newn);
}

inline template<typename Elem> Matrix<Elem>::Matrix(Index newm, Index newn, Elem* init)
{
    this->m(newm);
    this->n(newn);

    for(Index i=0;i<this->m();i++)
        for(Index j=0;j<this->n();j++)
    	    (this->at(i,j)=*(init+this->n()*i+j));
}

inline template<typename Elem> Index Matrix<Elem>::m()
{
    return data.size();
}

inline template<typename Elem> Index Matrix<Elem>::n()
{
    Index max=0;
    for(typename vector<vector<Elem>>::iterator i=data.begin();i!=data.end();i++)
        if(max<i->size())
            max=i->size();
    return max;
}

inline template<typename Elem> Index Matrix<Elem>::m(Index newm)
{
    data.resize(newm);
    return this->m();
}

inline template<typename Elem> Index Matrix<Elem>::n(Index newn)
{
    for(typename vector<vector<Elem>>::iterator i=data.begin();i!=data.end();i++)
        i->resize(newn);
    return this->n();
}

inline template<typename Elem> Elem& Matrix<Elem>::at(const Index m, const Index n)
{
    if(m<this->m()&&n<this->n())
        return data[m][n];
    else
	throw (char*) "Matrix index out of range\n";
}

inline template<typename Elem> vector<Elem>& Matrix<Elem>::operator[](const Index k)
{
    return this->data[k]; 
}

inline template<typename Elem> Matrix<Elem>& Matrix<Elem>::DeleteRow(Index k)
{
    data.erase(data.begin()+k);
    return *this;
}

inline template<typename Elem> Matrix<Elem>& Matrix<Elem>::DeleteColumn(Index k)
{
    for(typename vector<vector<Elem>>::iterator i=data.begin();i!=data.end();i++)
	i->erase(i->begin()+k);
    return *this;
}

template<typename Elem> Elem Matrix<Elem>::Minor(Index m, Index n)
{
    Matrix<Elem> minor=*this;
    minor.DeleteRow(m);
    minor.DeleteColumn(n);
    return minor.Determinant();
}

template<typename Elem> Elem Matrix<Elem>::Determinant()
{
    if(this->m()!=0&&this->n()!=0)
    {
	if(this->m()==this->n())
	    if(this->m()==1&&this->n()==1)
		return this->at(0,0);
	    else
	    {
		Elem d=0;
		Index k=0;
		unsigned nonzerocount=data[0].size();
		for(Index i=0;i<this->m();i++)
		{
		    unsigned c=0;
		    for(Index j=0;j<this->m();j++)
			if(this->at(i,j)!=0)
			    c++;
		    if(c<nonzerocount)
			nonzerocount=c; k=i;
		}
		for(Index i=0;i<this->m();i++)
		    d+=this->pow(-1,i+1+k+1)*this->at(k,i)*this->Minor(k,i);
		return d;
	    }
	else
	    throw(char*) "Еhe matrix must be square for Determinant()";
    }
    else
	throw(char*) "Еhe matrix must not be zero";
}

template <typename Elem> Matrix<Elem> Matrix<Elem>::Transpose()
{
    Matrix<Elem> result(this->n(),this->m()); // MxN->NxM
    for(Index i=0;i<result.m();i++)
        for(Index j=0;j<result.n();j++)
	    result[i][j]=data[j][i];
    return result;
}

template <typename Elem> Matrix<Elem> Matrix<Elem>::Inverse()
{
    Matrix<Elem> result(this->m(),this->n()); // MxN->MxN and M=N, otherwise exception will be thrown in Determinant()
    for(Index i=0;i<result.m();i++)
        for(Index j=0;j<result.n();j++)
	    result[i][j]=this->pow(-1,i+1+j+1)*this->Minor(i,j);;
    result=result.Transpose();
    result=(1/this->Determinant())*result;
    return result;
}

template <typename Elem> Matrix<Elem> Matrix<Elem>::Triangular()
{
    Matrix<Elem> result=*this;
    
    for(Index i=1;i<result.n();i++)
	for(Index j=0;j<i;j++)
	{
	    if(result.at(j,j)!=0)
		result=result.AddRow(i,j,-(result.at(i,j)/result.at(j,j)));
	    else
		if(result.at(i,j)!=0)
		{
		    vector<Elem> I=result.Row(i);
		    vector<Elem> J=result.Row(j);
		    for(typename vector<Elem>::iterator k=I.begin();k!=I.end();k++)
			*k=-*k;
		    for(Index k=0;k<result.n();k++)
		    {
			result.at(j,k)=I[k];
			result.at(i,k)=J[k];
		    }
		}
	}
    return result;
}

template <typename Elem> Matrix<Elem> Matrix<Elem>::AddRow(Index first, Index second, Elem k)
{
    Matrix<Elem> result=*this;
    for(Index i=0;i<this->n();i++)
	result.at(first,i)+=k*result.at(second,i);
    return result;
}

template <typename Elem> Matrix<Elem> Matrix<Elem>::AddColumn(Index first, Index second, Elem k)
{
    Matrix<Elem> result=*this;
    for(Index i=0;i<this->m();i++)
	result.at(i,first)+=k*result.at(i,second);
    return result;
}

template <typename Elem> Matrix<Elem> Matrix<Elem>::AddRow(Index first, Index second)
{
    return this->AddRow(first,second,1);
}

template <typename Elem> Matrix<Elem> Matrix<Elem>::AddColumn(Index first, Index second)
{
    return this->AddColumn(first,second,1);
}

template <typename Elem> vector<Elem> Matrix<Elem>::Row(Index k)
{
    vector<Elem> result;
    for(Index i=0;i<this->n();i++)
	result.push_back(this->at(k,i));
    return result;
}

template <typename Elem> vector<Elem> Matrix<Elem>::Column(Index k)
{
    vector<Elem> result;
    for(Index i=0;i<this->m();i++)
	result.push_back(this->at(i,k));
    return result;
}

template<typename Elem> Matrix<Elem> operator+ (Matrix<Elem> first, Matrix<Elem> second)
{
    if(first.m()==second.m()&&first.n()==second.n())
    {
	Matrix <Elem> result(first.m(),first.n());
	for(Index i=0;i<result.m();i++)
	    for(Index j=0;j<result.n();j++)
		result[i][j]=first[i][j]+second[i][j];
	return result;
    }
    else
	throw(char*) "Added matrices must have equal sizes";
}

template<typename Elem> Matrix<Elem> operator- (Matrix<Elem> first, Matrix<Elem> second)
{
    return first+(Elem)-1*second;
}

template<typename Elem> Matrix<Elem> operator* (Elem lambda, Matrix<Elem> M)
{
    Matrix <Elem> result(M.m(),M.n());
    for(Index i=0;i<M.m();i++)
        for(Index j=0;j<M.n();j++)
	    result[i][j]=lambda*M[i][j];
    return result;
}

template<typename Elem> Matrix<Elem> operator* (Matrix<Elem> M, Elem lambda)
{
    return lambda*M;
}

template<typename Elem> Matrix<Elem> operator* (Matrix<Elem> first, Matrix<Elem> second)
{
    if(first.m()==second.n())
    {
	Matrix <Elem> result(first.m(),second.n());
	for(Index i=0;i<result.m();i++)
	    for(Index j=0;j<result.n();j++)
		for(Index k=0;k<first.n();k++)
			result[i][j]+=first[i][k]*second[k][j];
	return result;
    }
    else
	throw(char*) "First matrix m() must have equal to second matrix n(n)";
}

#endif