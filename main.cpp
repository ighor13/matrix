#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "matrix.h"

using namespace std;

typedef long double elem;

const unsigned m=4;
const unsigned n=4;

int main(int argc, char* argv[])
{

    elem M[m][n]=
    {
	{6,		2,		-10,		4.1111111111	},
	{-5,		-7.77777777777,	-4,		1		},
	{2,		4,		-2,		-6		},
	{3,		0,		-5,		4		},
    }
    ;

    cout<<"----------------------------------------------------------------------------------------"<<endl;
    
    Matrix<elem> m(4,4,(elem*)M);

    m.m(5);
    m.n(5);
    
//    cout.setf(ios::scientific);
    
    for(unsigned i=0;i<m.m();i++)
    {
	for(unsigned j=0;j<m.n();j++)
	    cout<<setw(10)<<setprecision(7)<<m.at(i,j);

	printf("\n");
    }

    cout<<"----------------------------------------------------------------------------------------"<<endl;
    cout<<setprecision(5)<<m[1][1]<<endl;
    m[1][1]=(elem)-199.1333333;
    cout<<setprecision(10)<<m[1][1]<<endl;

    return 0;
}