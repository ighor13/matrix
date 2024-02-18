#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

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
	Elem Minor(Index, Index);
	Elem Determinant();
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

inline template<typename Elem> Matrix<Elem>::~Matrix()
{
    ;
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
    if(this->m()==this->n())
	if(this->m()==1)
	    return this->at(0,0);
	else
	{
	    Elem d=0;
	    Index k=0;
	    for(Index i=0;i<this->m();i++)
		d+=this->pow(-1,i+1+k+1)*this->at(k,i)*this->Minor(k,i);
	    return d;
	}
    else
	throw(char*) "Еhe matrix must be square for Determinant()";
}

#endif