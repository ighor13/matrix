#include <iostream>
#include <iomanip>
#include "matrix.h"

using namespace std;

typedef long double elem;

const unsigned dimm=5;
const unsigned dimn=5;

void print(Matrix<elem> m, unsigned precision=7)
{
    for(unsigned i=0;i<m.m();i++)
    {
	for(unsigned j=0;j<m.n();j++)
	    cout<<setw(15)<<setprecision(precision)<<m.at(i,j);
	cout<<endl;
    }
}

int main(int argc, char* argv[])
{
    elem M0[dimm][dimm]=
    {
	{1,		2,		3,		4,		5	},
	{5,		4,		3,		2,		2	},
	{-1,		-1,		0,		-3,		-2	},
	{6,		3,		4,		8,		-3	},
	{1,		3,		7,		1,		-2	},
    };

//    cout.setf(ios::scientific);

    Matrix<elem> m(dimm,dimm,(elem*)M0);
    cout<<"----------------------------------------------------------------------------------------"<<endl;
    try
    {
        cout<<"det(m)="<<setprecision(7)<<m.Determinant()<<endl;
    }
    catch(char* err)
    {
	cerr<<"Error: "<<err<<endl;
    }
    cout<<"----------------------------------------------------------------------------------------"<<endl;
    cout<<"-Trianhular(m)--------------------------------------------------------------------------"<<endl;
    try
    {
	print(m.Triangular(),4);
    }
    catch(char* err)
    {
	cerr<<"Error: "<<err<<endl;
    }
    cout<<"----------------------------------------------------------------------------------------"<<endl;

    cout<<"-m*m----------------------------------------------------------------------------------"<<endl;
    try
    {
        print(m*m);
    }
    catch(char* err)
    {
	cerr<<"Error: "<<err<<endl;
    }

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

    cout<<"-m.Triangular()-------------------------------------------------------------------------"<<endl;
    print(m.Triangular(),2);
    cout<<"----------------------------------------------------------------------------------------"<<endl;
    cout<<"det(Triangular)="<<setprecision(7)<<m.Triangular().Determinant()<<endl;
    cout<<".at(1,3)="<<setprecision(20)<<m.Triangular()[1][3]<<endl;
    cout<<"----------------------------------------------------------------------------------------"<<endl;

    cout<<"-m.Triangular().Transpose()-------------------------------------------------------------"<<endl;
    print(m.Triangular().Transpose(),2);
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

    return 0;
}