#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "matrix.h"

using namespace std;

typedef long double elem;

const unsigned dimm=4;
const unsigned dimn=4;

void print(Matrix<elem> m, unsigned precision=7)
{
    for(unsigned i=0;i<m.m();i++)
    {
	for(unsigned j=0;j<m.n();j++)
	    cout<<setw(10)<<setprecision(precision)<<m.at(i,j);
	cout<<endl;
    }
}

int main(int argc, char* argv[])
{
    elem M[dimm][dimn]=
    {
	{6,		2,		-10,		4	},
	{-5,		-7,		-4,		1	},
	{2,		4,		-2,		-6	},
	{3,		0,		-5,		4	},
    }
    ;

//    cout.setf(ios::scientific);

    Matrix<elem> m(dimm,dimn,(elem*)M);
    cout<<"-m--------------------------------------------------------------------------------------"<<endl;
    print(m);
    cout<<"----------------------------------------------------------------------------------------"<<endl;

    cout<<"-m.Transpose()--------------------------------------------------------------------------"<<endl;
    print(m.Transpose());
    cout<<"----------------------------------------------------------------------------------------"<<endl;

    cout<<"-m.Inverse()----------------------------------------------------------------------------"<<endl;
    print(m.Inverse());
    cout<<"----------------------------------------------------------------------------------------"<<endl;

    cout<<"-m*m.Inverse()--------------------------------------------------------------------------"<<endl;
    print(m*m.Inverse(),2);
    cout<<"----------------------------------------------------------------------------------------"<<endl;

    try
    {
        cout<<"det(m)="<<setprecision(7)<<m.Determinant()<<endl;
    }
    catch(char* err)
    {
	cerr<<"Error: "<<err<<endl;
    }

    return 0;
}