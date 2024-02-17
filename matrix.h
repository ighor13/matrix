#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

using namespace std;

typedef unsigned int Index;
template <typename Elem> class Matrix
{
    private:
	vector<vector<Elem>> data;

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
};

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

#endif