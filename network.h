#ifndef NETWORK_H_INCLUDED
#define NETWORK_H_INCLUDED

#include "node.h"
#include "branch.h"
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

class network
{
		vector<node> nodes;
		vector<branch> branches;

		double Sb;
		vector<double> Vb;

		char* filename;
		ifstream inputstream;

		char* word;
		void readTR();
		void readSection();
		void readNode();
		void readBase();
		void error(const char*)const;

	public:
		network();
		network(network&);
		network(const char* filename);
		~network();

		double getSb()const {return Sb; }
		double getVb(int i)const;
		double getNumONodes()const {return nodes.size(); }
		double getNumOBranches()const {return branches.size(); }
		void printFileName();
		void printNode(int i);
		void printBranch(int i);

		int getTapChangerPos()const {return branches[0].getTapChangerPos(); }
		double getCapacitorC(int i)const {return nodes[i].getCapacitor(); }
		double getCapacitorB(int i)const {return nodes[i].getCapacitor()*100*M_PI; }
		complex<double> getVoltage(int i)const {return nodes[i].getVoltage(); }
		double getVoltageMagnitude(int i)const {return nodes[i].getVoltageMagnitude(); }
		double getVoltagePhase (int i)const {return nodes[i].getVoltagePhase(); }
		double getLoadActivePower( int i)const {return nodes[i].getActivePowerInjection(); }
		double getLoadReactivePower( int i)const {return nodes[i].getReactivePowerInjection(); }

		double getPmax (int i)const {return nodes[i].getPmax(); }
		int getLoadType (int i)const {return nodes[i].getLoadType(); }
		double getRootCurrent()const {return branches[0].getCurrentMagnitude()*Sb/Vb[1]/sqrt(3.0); }

		complex<double> getConsumption() {return nodes[0].getVoltage()*conj(branches[0].getCurrent() ); }
		double getActiveConsumption() ;
		double getReactiveConsumption() ;

		double getActiveLosses() ;
		double getReactiveLosses();

		complex<double> getComplexVoltage (int i) {return nodes[i].getVoltage(); }
		double getVoltageMagnitude(int i) {return nodes[i].getVoltageMagnitude(); }
		void getVoltagePNode(ostream& os);
		void getLoadPowerPNode(ostream& os);

		void setTapChanger(int tPos) {branches[0].setTapChanger(tPos); }
		void setCapacitorC(int i, double value);
		void setCapacitorB(int i, double value);
		void switchCapacitorOn(int i) {nodes[i].turnCapacitorON(); }
		void switchCapacitorOFF(int i) {nodes[i].turnCapacitorOFF(); }
		void removeCapacitor(int i) {nodes[i].removeCapacitor(); }

		void setLoadPower (int i, complex<double> value) {  nodes[i].setLoadPower(value); }
		void setLoadPower (int i, double P, double Q) {nodes[i].setLoadPower(P, Q); }
		void setLoadActivePower (int i, double P) { nodes[i].setLoadActivePower(P); }
		void setLoadReactivePower (int i, double Q) { nodes[i].setLoadReactivePower(Q); }

		void solvePowerFlow() ;

		friend ostream& operator<< (ostream& os, network n);
};

#endif // NETWORK_H_INCLUDED
