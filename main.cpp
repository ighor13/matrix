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

    cout<<"-col1+=col2*2---------------------------------------------------------------------------"<<endl;
    print(m.AddColumn(1,2,2));
    cout<<"----------------------------------------------------------------------------------------"<<endl;

    cout<<"-row1+=row2*1---------------------------------------------------------------------------"<<endl;
    print(m.AddRow(1,2));
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
    
    vector<elem> r=m.Row(1);
    cout<<"-row1-of-m------------------------------------------------------------------------------"<<endl;
    for(vector<elem>::iterator i=r.begin();i!=r.end();i++)
        cout<<setw(10)<<setprecision(2)<<*i;
    cout<<endl;
    cout<<"----------------------------------------------------------------------------------------"<<endl;

    vector<elem> c=m.Transpose().Column(2);
    cout<<"-col2-of-m.Transpose()------------------------------------------------------------------"<<endl;
    for(vector<elem>::iterator i=c.begin();i!=c.end();i++)
        cout<<setw(10)<<setprecision(2)<<*i;
    cout<<endl;
    cout<<"----------------------------------------------------------------------------------------"<<endl;

    vector<elem> d=m.Inverse().Column(3);
    cout<<"-col3-of-m.Inverse()--------------------------------------------------------------------"<<endl;
    for(vector<elem>::iterator i=d.begin();i!=d.end();i++)
        cout<<setw(10)<<setprecision(4)<<*i;
    cout<<endl;
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