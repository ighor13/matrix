#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

using namespace std;

typedef unsigned int typeD;

template <typename elemT> class Matrix
{
    private:
	vector<vector<elemT>> data;

    public:
	Matrix();
	Matrix(typeD m,typeD n);
	Matrix(typeD m,typeD n, elemT*);
	~Matrix();
	typeD m();
	typeD n();
	typeD m(typeD);
	typeD n(typeD);
	elemT& at(const typeD m,const typeD n); // with index checking, throw(char*) in out of range
	vector<elemT>& operator [] (const typeD); // without index checking
};

template<typename elemT> Matrix<elemT>::Matrix()
{
     ;
}

template<typename elemT> Matrix<elemT>::Matrix(typeD newm, typeD newn)
{
    this->m(newm);
    this->n(newn);
}

template<typename elemT> Matrix<elemT>::Matrix(typeD newm, typeD newn, elemT* init)
{
    this->m(newm);
    this->n(newn);

    for(typeD i=0;i<this->m();i++)
        for(typeD j=0;j<this->n();j++)
    	    (this->at(i,j)=*(init+this->n()*i+j));
}

template<typename elemT> Matrix<elemT>::~Matrix()
{
    ;
}

template<typename elemT> typeD Matrix<elemT>::m()
{
    return data.size();
}

template<typename elemT> typeD Matrix<elemT>::n()
{
    typeD max=0;
    for(typename vector<vector<elemT>>::iterator i=data.begin();i!=data.end();i++)
        if(max<i->size())
            max=i->size();
    return max;
}

template<typename elemT> typeD Matrix<elemT>::m(typeD newm)
{
    data.resize(newm);
    return this->m();
}

template<typename elemT> typeD Matrix<elemT>::n(typeD newn)
{
    for(typename vector<vector<elemT>>::iterator i=data.begin();i!=data.end();i++)
        i->resize(newn);
    return this->n();
}

inline template<typename elemT> elemT& Matrix<elemT>::at(const typeD m, const typeD n)
{
    if(m<this->m()&&n<this->n())
        return data[m][n];
    else
	throw (char*) "Matrix index out of range\n";
}

inline template<typename elemT> vector<elemT>& Matrix<elemT>::operator[](const typeD k)
{
    return this->data[k]; 
}

#endif