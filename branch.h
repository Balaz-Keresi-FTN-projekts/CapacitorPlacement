#ifndef BRANCH_H_INCLUDED
#define BRANCH_H_INCLUDED

#include <complex>

using namespace std;


class branch
{
        static int numOBranches;
        int beginpoint;
        int endpoint;
        complex<double> impedance;
        complex<double> current;
        bool isRTR;
        int tapChanger;
        int tapMaxPos;
        double du;
    public:
        branch();
        branch(const branch&);
		branch(int beginpoint, complex<double> imp, int tapMax, double du);
		branch(int beginpoint, complex<double> imp);
		branch(int beginpoint, double R, double X, int tapMax, double du);
		branch(int beginpoint, double R, double X);

		int getNumOBranches()const {return numOBranches; }
		int getBeginPoint()const {return beginpoint; }
		int getEndPoint()const {return endpoint; }

        complex<double> getImpedance()const {return impedance;}
        complex<double> getCurrent()const {return current;}
        
        double getResistance()const {return impedance.real();}
        double getReaktance()const {return impedance.imag();}
        double getCurrentMagnitude()const {return abs(current);}
        double getCurrentAngle()const {return arg(current);}

		bool isRegulative()const {return isRTR;}
		int getTapChangerPos()const {return tapChanger;}
		int getTapMaximum()const {return tapMaxPos; }
		double getDeltaU()const {return du; }

		void setCurrent(complex<double> cur) {current = cur; }
		void setZ(complex<double> imp) {impedance = imp; }
		void setZ(double R, double X) {impedance = complex<double>(R,X); }
		void setTapChanger(int pos);
		void resetTapChanger() {tapChanger = 0;}

		friend ostream& operator<< (ostream&, branch&);
};

#endif // BRANCH_H_INCLUDED
