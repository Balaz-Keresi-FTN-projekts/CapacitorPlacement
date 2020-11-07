#include "node.h"
#include <cmath>
#include <iostream>

using namespace std;

int node::numONodes = 0;


node::node()
{
	num = numONodes++;
    shuntAdmitanse = complex<double> (0,0);
    voltage = complex<double> (1,0);
    loadPower = complex<double> (0,0);
    loadCurrent = complex<double> (0,0);
    capacitor = 0;
	capacitorSwitchPos = false;
	Pmax = 0;
	loadType = 0;
}

node::node(complex<double> adm)
{
    num = numONodes++;
    shuntAdmitanse = adm;
    voltage = complex<double>(1,0);
    loadPower = complex<double>(0,0);
    loadCurrent = complex<double> (0,0);
	Pmax = 0;

	loadType = 0;
    capacitor = 0;
	capacitorSwitchPos = false;
}

node::node(double G, double B)
{
    num = numONodes++;
    shuntAdmitanse = complex<double>(G, B);
    voltage = polar(1,0);
    loadPower = complex<double> (0,0);
    loadCurrent = complex<double> (0,0);
	Pmax = 0;

    capacitor = 0;
	capacitorSwitchPos = false;
	loadType = 0;
}

node::node(const node &n)
{
	num = n.num;
    shuntAdmitanse = n.shuntAdmitanse;
    voltage = n.voltage;
    loadPower = n.loadPower;
    loadCurrent = n.loadCurrent;
    capacitor = n.capacitor;
	capacitorSwitchPos = n.capacitorSwitchPos;
	Pmax = n.Pmax;
	loadType = n.loadType;
}



void node::setCapacitorC(double C)
{
	if ( capacitor==0 && C!=0)
	{
		//cout<<"Capacitor placed at node: "<<num<<endl;
		//cout<<"New Value: "<<C<<endl;
	}
	else if ( capacitor!=0 && C!=0)
	{
		//cout<<"Capacitor set at node: "<<num<<endl;
		//cout<<"New Value: "<<C<<endl;
	}
	else
	{
		//cout<<"Capacitor removed at node: "<<num<<endl;
	}
    shuntAdmitanse -= complex<double> (0, 100*M_PI*capacitor);
    shuntAdmitanse += complex<double> (0, 100*M_PI*C);
    capacitor = C;
	capacitorSwitchPos = true;
}

void node::setCapacitorB(double B)
{
	double C = B / 100/M_PI ;
	if ( capacitor==0 && C!=0)
	{
		//cout<<"Capacitor placed at node: "<<num<<endl;
		//cout<<"New Value: "<<C<<endl;
	}
	else if ( capacitor!=0 && C!=0)
	{
		//cout<<"Capacitor set at node: "<<num<<endl;
		//cout<<"New Value: "<<C<<endl;
	}
	else
	{
		//cout<<"Capacitor removed at node: "<<num<<endl;
	}
    shuntAdmitanse -= complex<double> (0, 100*M_PI*capacitor);
    shuntAdmitanse += complex<double> (0, B);
    capacitor = C;
	capacitorSwitchPos = true;
}

void node::removeCapacitor()
{
	//cout<<"Capacitor removed at node: "<<num<<endl;
    shuntAdmitanse -= complex<double> (0, 100*M_PI*capacitor);
    capacitor = 0;
	capacitorSwitchPos = false;
}

void node::turnCapacitorOFF()
{
	if (capacitor == 0)
	{
		cerr<<"You cannat switch the capacitor at node "<<num<<" because it has no capacitor"<<endl;
		return;
	}
	if ( capacitorSwitchPos == false )
	{
		cerr<<"Capacitor switch at node "<<num<<" is already turned off. You cannot turn it off again"<<endl;
		return;
	}
	capacitorSwitchPos = false;
	shuntAdmitanse -= complex<double> (0, 100*M_PI*capacitor);
}

void node::turnCapacitorON()
{
	if (capacitor == 0)
	{
		cerr<<"You cannat switch the capacitor at node "<<num<<" because it has no capacitor"<<endl;
		return;
	}
	if ( capacitorSwitchPos == true )
	{
		cerr<<"Capacitor switch at node "<<num<<" is already turned on. You cannot turn it on again"<<endl;
		return;
	}
	capacitorSwitchPos = true;
	shuntAdmitanse += complex<double> (0, 100*M_PI*capacitor);
}

ostream& operator<< (ostream& os, node& n)
{
	os<<"[ "<<n.num<<", "<<n.shuntAdmitanse<<", "<<n.voltage<<", "<<n.loadPower<<", "<<n.loadCurrent<<", "<<n.loadType<<" ] ";
	return os;
}
