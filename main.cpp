#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "matrix.h"

using namespace std;

typedef long double elem;

const unsigned dimm=4;
const unsigned dimn=4;

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

    cout<<"----------------------------------------------------------------------------------------"<<endl;
    
    Matrix<elem> m(dimm,dimn,(elem*)M);

//    cout.setf(ios::scientific);
    
    for(unsigned i=0;i<m.m();i++)
    {
	for(unsigned j=0;j<m.n();j++)
	    cout<<setw(10)<<setprecision(7)<<m.at(i,j);
	cout<<endl;
    }
    cout<<"----------------------------------------------------------------------------------------"<<endl;
    cout<<"det(A)="<<m.Determinant()<<endl;

    return 0;
}