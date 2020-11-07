#include "branch.h"
#include <iostream>

int branch::numOBranches = 0;

branch::branch()
{
    beginpoint = numOBranches++;
    endpoint = numOBranches;

    impedance = complex<double>(0,0);
    current = complex<double>(0,0);

    isRTR = false;
    tapChanger = 0;
    tapMaxPos = 0;
    du = 0;
}

branch::branch(const branch& b)
{
	beginpoint = b.beginpoint;
	endpoint = b.endpoint;

    impedance = b.impedance;
    current = b.current;

    isRTR = b.isRTR;
    tapChanger = b.tapChanger;
    tapMaxPos = b.tapMaxPos;
    du = b.du;
}

branch::branch(int beginpoint, complex<double> imp, int tapMax, double du)
{
	numOBranches++;
	endpoint = numOBranches;
	this->beginpoint = beginpoint;

	impedance = imp;
	current = complex<double>(0,0);

	isRTR = true;
	tapChanger = 0;
	tapMaxPos = tapMax;
	this->du = du;
}

branch::branch(int beginpoint, complex<double> imp)
{
	numOBranches++;
	endpoint = numOBranches;
	this->beginpoint = beginpoint;

	impedance = imp;
	current = complex<double> (0,0);

	isRTR = false;
	tapChanger = 0;
	tapMaxPos = 0;
	du = 0;
}

branch::branch(int beginpoint, double R, double X, int tapMax, double du)
{
	numOBranches++;
	endpoint = numOBranches;
	this->beginpoint = beginpoint;

	impedance = complex<double> (R,X);
	current = polar(0, 0);

	isRTR = true;
	tapChanger = 0;
	tapMaxPos = tapMax;
	this->du = du;
}

branch::branch(int beginpoint, double R, double X)
{
	numOBranches++;
	endpoint = numOBranches;
	this->beginpoint = beginpoint;

	impedance = complex<double> (R,X);
	current = polar(0, 0);

	isRTR = false;
	tapChanger = 0;
	tapMaxPos = 0;
	this->du = 0;
}



void branch::setTapChanger(int pos)
{
	if (!isRTR)
		cerr<<"Error: This branch has no tap changer. No action was taken"<<endl;
	else if (pos > tapMaxPos || pos < -tapMaxPos)
		cerr<<"Error: Tap changer has not got a position "<<pos<<" No action was taken"<<endl;
	else
	{
		tapChanger = pos;
		cout<<"Tap changer position changed to: "<<pos<<endl;
	}
}

ostream& operator<< (ostream& os, branch& b)
{
    os<<"[ "<<b.beginpoint<<", "<<b.endpoint<<", "<<b.impedance<<", "<<b.current<<", "<<b.tapChanger<<", "<<b.du<<"] ";
	return os;
}
