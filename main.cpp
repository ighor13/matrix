#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "matrix.h"

using namespace std;

typedef long double elem;

const unsigned dimm=3;
const unsigned dimn=4;

int main(int argc, char* argv[])
{
    elem M[dimm][dimn]=
    {
	{6,		2,		-10,		4	},
	{-5,		-7,		-4,		1	},
	{2,		4,		-2,		-6	},
//	{3,		0,		-5,		4	},
    }
    ;

    Matrix<elem> m1(dimm,dimn,(elem*)M);

    cout<<"-m1--------------------------------------------------------------------------------------"<<endl;
    for(unsigned i=0;i<m1.m();i++)
    {
	for(unsigned j=0;j<m1.n();j++)
	    cout<<setw(10)<<setprecision(7)<<m1.at(i,j);
	cout<<endl;
    }
    cout<<"----------------------------------------------------------------------------------------"<<endl;
    
    Matrix<elem> m2=m1.Transpose();

    cout<<"-m2--------------------------------------------------------------------------------------"<<endl;
    for(unsigned i=0;i<m2.m();i++)
    {
	for(unsigned j=0;j<m2.n();j++)
	    cout<<setw(10)<<setprecision(7)<<m2.at(i,j);
	cout<<endl;
    }
    cout<<"----------------------------------------------------------------------------------------"<<endl;

    Matrix<elem> p=m1*m2;
    

//    cout.setf(ios::scientific);
    
    cout<<"-p--------------------------------------------------------------------------------------"<<endl;
    for(unsigned i=0;i<p.m();i++)
    {
	for(unsigned j=0;j<p.n();j++)
	    cout<<setw(10)<<setprecision(7)<<p.at(i,j);
	cout<<endl;
    }
    cout<<"----------------------------------------------------------------------------------------"<<endl;

    Matrix<elem> s=p+p;//=m2+m1;
    s=(elem)2*s;
    cout<<"-s--------------------------------------------------------------------------------------"<<endl;
    for(unsigned i=0;i<s.m();i++)
    {
	for(unsigned j=0;j<s.n();j++)
	    cout<<setw(10)<<setprecision(7)<<s.at(i,j);
	cout<<endl;
    }
    cout<<"----------------------------------------------------------------------------------------"<<endl;


    try
    {
        cout<<"det(A)="<<s.Determinant()<<endl;
    }
    catch(char* err)
    {
	cerr<<"Error: "<<err<<endl;
    }

    return 0;
}