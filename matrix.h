#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

using namespace std;

typedef unsigned int Index;
template <typename elemT> class Matrix
{
    private:
	vector<vector<elemT>> data;

    public:
	Matrix();
	Matrix(Index m,Index n);
	Matrix(Index m,Index n, elemT*);
	~Matrix();
	Index m();
	Index n();
	Index m(Index);
	Index n(Index);
	elemT& at(const Index,const Index); // element at (m,n) with index checking, throw(char*) in out of range
	vector<elemT>& operator [] (const Index); // element at [m][n] without index checking
};

template<typename elemT> Matrix<elemT>::Matrix()
{
    ;
}

template<typename elemT> Matrix<elemT>::Matrix(Index newm, Index newn)
{
    this->m(newm);
    this->n(newn);
}

template<typename elemT> Matrix<elemT>::Matrix(Index newm, Index newn, elemT* init)
{
    this->m(newm);
    this->n(newn);

    for(Index i=0;i<this->m();i++)
        for(Index j=0;j<this->n();j++)
    	    (this->at(i,j)=*(init+this->n()*i+j));
}

template<typename elemT> Matrix<elemT>::~Matrix()
{
    ;
}

template<typename elemT> Index Matrix<elemT>::m()
{
    return data.size();
}

template<typename elemT> Index Matrix<elemT>::n()
{
    Index max=0;
    for(typename vector<vector<elemT>>::iterator i=data.begin();i!=data.end();i++)
        if(max<i->size())
            max=i->size();
    return max;
}

template<typename elemT> Index Matrix<elemT>::m(Index newm)
{
    data.resize(newm);
    return this->m();
}

template<typename elemT> Index Matrix<elemT>::n(Index newn)
{
    for(typename vector<vector<elemT>>::iterator i=data.begin();i!=data.end();i++)
        i->resize(newn);
    return this->n();
}

inline template<typename elemT> elemT& Matrix<elemT>::at(const Index m, const Index n)
{
    if(m<this->m()&&n<this->n())
        return data[m][n];
    else
	throw (char*) "Matrix index out of range\n";
}

inline template<typename elemT> vector<elemT>& Matrix<elemT>::operator[](const Index k)
{
    return this->data[k]; 
}

#endif