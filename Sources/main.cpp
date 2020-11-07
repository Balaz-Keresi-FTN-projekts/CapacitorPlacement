#include <iostream>
#include <sstream>
#include <cstdlib>
#include "network.h"

using namespace std;

double Pdiag1[24];
double Qdiag1[24];
double Pdiag2[24];
double Qdiag2[24];
double Pdiag3[24];
double Qdiag3[24];

void diagram_initialization();
void export_diagram();

void setup(network& netw, int hour);

void scenario(int scNum, network& netw, int T, int i, double Qmax);
void scenario(int scNum, network& netw, int T, int i1, int i2, double Qmax);
void scenario_day(network& netw, int i, double Qmax);

void diagram_initialization()
{
	// Domacinstva
	Pdiag1[0] = 0.609;
	Pdiag1[1] = 0.476;
	Pdiag1[2] = 0.43;
	Pdiag1[3] = 0.3818;
	Pdiag1[4] = 0.344;
	Pdiag1[5] = 0.348;
	Pdiag1[6] = 0.387;
	Pdiag1[7] = 0.463;
	Pdiag1[8] = 0.601;
	Pdiag1[9] = 0.644;
	Pdiag1[10] = 0.705;
	Pdiag1[11] = 0.684;
	Pdiag1[12] = 0.749;
	Pdiag1[13] = 0.76;
	Pdiag1[14] = 0.722;
	Pdiag1[15] = 0.696;
	Pdiag1[16] = 0.67;
	Pdiag1[17] = 0.667;
	Pdiag1[18] = 0.665;
	Pdiag1[19] = 0.665;
	Pdiag1[20] = 0.701;
	Pdiag1[21] = 0.817;
	Pdiag1[22] = 0.922;
	Pdiag1[23] = 0.827;

	Qdiag1[0] = 0.429;
	Qdiag1[1] = 0.342;
	Qdiag1[2] = 0.255;
	Qdiag1[3] = 0.245;
	Qdiag1[4] = 0.258;
	Qdiag1[5] = 0.278;
	Qdiag1[6] = 0.264;
	Qdiag1[7] = 0.237;
	Qdiag1[8] = 0.273;
	Qdiag1[9] = 0.274;
	Qdiag1[10] = 0.256;
	Qdiag1[11] = 0.249;
	Qdiag1[12] = 0.218;
	Qdiag1[13] = 0.25;
	Qdiag1[14] = 0.234;
	Qdiag1[15] = 0.252;
	Qdiag1[16] = 0.246;
	Qdiag1[17] = 0.242;
	Qdiag1[18] = 0.218;
	Qdiag1[19] = 0.218;
	Qdiag1[20] = 0.204;
	Qdiag1[21] = 0.272;
	Qdiag1[22] = 0.269;
	Qdiag1[23] = 0.293;

	// Trgovacka-poslovna potrosnja
	Pdiag2[0] = 0.276;
	Pdiag2[1] = 0.265;
	Pdiag2[2] = 0.245;
	Pdiag2[3] = 0.272;
	Pdiag2[4] = 0.288;
	Pdiag2[5] = 0.326;
	Pdiag2[6] = 0.361;
	Pdiag2[7] = 0.446;
	Pdiag2[8] = 0.526;
	Pdiag2[9] = 0.6975;
	Pdiag2[10] = 0.855;
	Pdiag2[11] = 0.873;
	Pdiag2[12] = 0.891;
	Pdiag2[13] = 0.874;
	Pdiag2[14] = 0.856;
	Pdiag2[15] = 0.837;
	Pdiag2[16] = 0.722;
	Pdiag2[17] = 0.605;
	Pdiag2[18] = 0.543;
	Pdiag2[19] = 0.553;
	Pdiag2[20] = 0.588;
	Pdiag2[21] = 0.58;
	Pdiag2[22] = 0.509;
	Pdiag2[23] = 0.388;

	Qdiag2[0] = 0;
	Qdiag2[1] = 0.054;
	Qdiag2[2] = 0.05;
	Qdiag2[3] = 0.068;
	Qdiag2[4] = 0.073;
	Qdiag2[5] = 0.092;
	Qdiag2[6] = 0.119;
	Qdiag2[7] = 0.147;
	Qdiag2[8] = 0.194;
	Qdiag2[9] = 0.276;
	Qdiag2[10] = 0.414;
	Qdiag2[11] = 0.423;
	Qdiag2[12] = 0.431;
	Qdiag2[13] = 0.398;
	Qdiag2[14] = 0.368;
	Qdiag2[15] = 0.331;
	Qdiag2[16] = 0.237;
	Qdiag2[17] = 0.176;
	Qdiag2[18] = 0.136;
	Qdiag2[19] = 0.138;
	Qdiag2[20] = 0.119;
	Qdiag2[21] = 0.079;
	Qdiag2[22] = 0.103;
	Qdiag2[23] = 0.097;

	//Industrija
	Pdiag3[0] = 0.396;
	Pdiag3[1] = 0.396;
	Pdiag3[2] = 0.413;
	Pdiag3[3] = 0.416;
	Pdiag3[4] = 0.521;
	Pdiag3[5] = 0.672;
	Pdiag3[6] = 0.769;
	Pdiag3[7] = 0.8;
	Pdiag3[8] = 0.802;
	Pdiag3[9] = 0.81;
	Pdiag3[10] = 0.81;
	Pdiag3[11] = 0.805;
	Pdiag3[12] = 0.813;
	Pdiag3[13] = 0.816;
	Pdiag3[14] = 0.82;
	Pdiag3[15] = 0.794;
	Pdiag3[16] = 0.788;
	Pdiag3[17] = 0.787;
	Pdiag3[18] = 0.722;
	Pdiag3[19] = 0.598;
	Pdiag3[20] = 0.467;
	Pdiag3[21] = 0.421;
	Pdiag3[22] = 0.3915;
	Pdiag3[23] = 0.3956;

	Qdiag3[0] = 0.214;
	Qdiag3[1] = 0.235;
	Qdiag3[2] = 0.245;
	Qdiag3[3] = 0.258;
	Qdiag3[4] = 0.336;
	Qdiag3[5] = 0.469;
	Qdiag3[6] = 0.557;
	Qdiag3[7] = 0.6;
	Qdiag3[8] = 0.598;
	Qdiag3[9] = 0.586;
	Qdiag3[10] = 0.586;
	Qdiag3[11] = 0.593;
	Qdiag3[12] = 0.582;
	Qdiag3[13] = 0.578;
	Qdiag3[14] = 0.572;
	Qdiag3[15] = 0.588;
	Qdiag3[16] = 0.575;
	Qdiag3[17] = 0.549;
	Qdiag3[18] = 0.504;
	Qdiag3[19] = 0.386;
	Qdiag3[20] = 0.29;
	Qdiag3[21] = 0.245;
	Qdiag3[22] = 0.213;
	Qdiag3[23] = 0.226;

	cout<<"Diagrams are initailized"<<endl;
}

void export_diagram(const char* mfile, double* diagramArrey)
{
	ofstream os(mfile, ofstream::out);
	string title(mfile);
	title.erase( strlen(mfile) - 2, 2) ;
	title.append("_matrix");
	os<<title<<" = [..."<<endl;
	for (int i=0; i<24; i++ )
	{
		os<<"\t"<<i<<"\t"<<diagramArrey[i];
		if (i < 23)
			os<<";"<<endl;
		else
			os<<"];"<<endl;
	}
	cout<<title<<" exported"<<endl;
}

void setup (network& netw, int hour, bool DGplaced)
{
	hour %= 24;
	double* PdiagramPointer;
	double* QdiagramPointer;
	for (int i=0; i<netw.getNumONodes(); i++)
	{
		if ( netw.getLoadType(i) == 0 )
		{
			netw.setLoadPower(i,0,0);
			continue;
		}
		else if (netw.getLoadType(i) == 1 )
		{
			PdiagramPointer = Pdiag1;
			QdiagramPointer = Qdiag1;
		}
		else if (netw.getLoadType(i) == 2 )
		{
			PdiagramPointer = Pdiag1;
			QdiagramPointer = Qdiag1;
		}
		else if (netw.getLoadType(i) == 3 )
		{
			PdiagramPointer = Pdiag1;
			QdiagramPointer = Qdiag1;
		}
		else
		{
			cerr<<"Error: wrong loadtype initialization"<<endl;
			exit(EXIT_SUCCESS);
		}
		double P = *(PdiagramPointer + hour) * netw.getPmax(i);
		double Q = *(QdiagramPointer + hour) * netw.getPmax(i);
		netw.setLoadPower(i, P, Q);
	}
	double Pg = 0; // 3 MW distributivni generator
	double Qg = 0;
	if ( DGplaced )
	{
		Pg = -3.0;
		Qg = -1.0;
	}
	Pg /= netw.getSb();
	netw.setLoadPower(6, netw.getLoadActivePower(6) + Pg, netw.getLoadReactivePower(6) + Qg );
	netw.solvePowerFlow();
}


// Scenario 1:
// Proracun potrosnja cele distributivne mreze i gubitaka (aktivnih i reaktivnih)
// Proracun je izvrsena u datom vremenskom trenutku T, smesti se jedan kondenzator na cvoru i
// Vrednost kompenzovane reaktivne snage je data u MVAr-ima,
//      Vrednost reaktivne snage se povecavana stepenasto sa 0.5 MVAr
// Rezultati su eksportovani u matlab fajlu scenario1.m
void scenario(int scNum, network& netw, int T, int i, double Qmax, bool DGplaced)
{
	if(i < 1 || i >= netw.getNumONodes() )
	{
		cerr << "Error: got an illegal node number. Program stops..."<<endl;
		exit(EXIT_SUCCESS);
	}
	stringstream fname;
	fname<<"scenario"<<scNum<<".m";
	ofstream os(fname.str());
	os<<"% U ovom scenariju jedan kondenzator je smesten na cvoru "<<i<<endl;
	os<<"% Proracunate su aktivne i reaktivne snage korena mreze"<<endl;
	os<<"% \taktivne i reaktivne snage gubitaka"<<endl;
	os<<"% \tnapon na krajevima mreze"<<endl;
	os<<"% \tstruja korena"<<endl<<endl;

	os<<"Pdist"<<scNum<<" = [... "<<endl;
	for(double Qc = 0; Qc <= Qmax; Qc+=0.5) //Qc [MVAr]
	{
		double B = Qc*1e6/pow(netw.getVb(1), 2);
		netw.setCapacitorB(i, B);
		setup(netw, T, DGplaced);
		os<<"\t"<<Qc<<"\t"<<netw.getActiveConsumption();
		if (Qc != Qmax)
			os<<";"<<endl;
		else
			os<<"];"<<endl;
	}
	os<<endl<<endl;
	os<<"Qdist"<<scNum<<" = [... "<<endl;
	for(double Qc = 0; Qc <= Qmax; Qc+=0.5) //Qc [MVAr]
	{
		double B = Qc*1e6/pow(netw.getVb(1), 2);
		netw.setCapacitorB(i, B);
		setup(netw, T, DGplaced);
		os<<"\t"<<Qc<<"\t"<<netw.getReactiveConsumption();
		if (Qc != Qmax)
			os<<";"<<endl;
		else
			os<<"];"<<endl;
	}
	os<<endl<<endl;
	os<<"Ploss"<<scNum<<" = [... "<<endl;
	for(double Qc = 0; Qc <= Qmax; Qc+=0.5) //Qc [MVAr]
	{
		double B = Qc*1e6/pow(netw.getVb(1), 2);
		netw.setCapacitorB(i, B);
		setup(netw,T, DGplaced);
		os<<"\t"<<Qc<<"\t"<<netw.getActiveLosses();
		if (Qc != Qmax)
			os<<";"<<endl;
		else
			os<<"];"<<endl;
	}
	os<<endl<<endl;
	os<<"Qloss"<<scNum<<" = [... "<<endl;
	for(double Qc = 0; Qc <= Qmax; Qc+=0.5) //Qc [MVAr]
	{
		double B = Qc*1e6/pow(netw.getVb(1), 2);
		netw.setCapacitorB(i, B);
		setup(netw, T, DGplaced);
		os<<"\t"<<Qc<<"\t"<<netw.getReactiveLosses();
		if (Qc != Qmax)
			os<<";"<<endl;
		else
			os<<"];"<<endl;
	}
	os<<endl<<endl;
	os<<"Vendprim"<<scNum<<" = [..."<<endl;
	for(double Qc = 0; Qc <= Qmax; Qc+=0.5) //Qc [MVAr]
	{
		double B = Qc*1e6/pow(netw.getVb(1), 2);
		netw.setCapacitorB(i, B);
		setup(netw, T, DGplaced);
		os<<"\t"<<Qc<<"\t"<<netw.getVoltageMagnitude(6)*netw.getVb(1)/1e3;
		if (Qc != Qmax)
			os<<";"<<endl;
		else
			os<<"];"<<endl;
	}
	os<<endl<<endl;
	os<<"Vendsecond"<<scNum<<" = [... "<<endl;
	for(double Qc = 0; Qc <= Qmax; Qc+=0.5) //Qc [MVAr]
	{
		double B = Qc*1e6/pow(netw.getVb(1), 2);
		netw.setCapacitorB(i, B);
		setup(netw, T, DGplaced);
		os<<"\t"<<Qc<<"\t"<<netw.getVoltageMagnitude(7)*netw.getVb(1)/1e3;
		if (Qc != Qmax)
			os<<";"<<endl;
		else
			os<<"];"<<endl;
	}
	os<<endl<<endl;
	os<<"Iroot"<<scNum<<" = [... "<<endl;
	for(double Qc = 0; Qc <= Qmax; Qc+=0.5) //Qc [MVAr]
	{
		double B = Qc*1e6/pow(netw.getVb(1), 2);
		netw.setCapacitorB(i, B);
		setup(netw, T, DGplaced);
		os<<"\t"<<Qc<<"\t"<<netw.getRootCurrent();
		if (Qc != Qmax)
			os<<";"<<endl;
		else
			os<<"];"<<endl;
	}
	netw.removeCapacitor(i);
}

// Scenario 2:
// Proracun potrosnja cele distributivne mreze i gubitaka (aktivnih i reaktivnih)
// Proracun je izvrsena u datom vremenskom trenutku T, smesti se dva kondenzatora na cvorovima i1 i i2 (i1 != i2)
// Vrednost kompenzovane reaktivne snage je data u MVAr-ima
//      Vrednost reaktivne snage se povecavana stepenasto sa 0.5 MVAr
// Rezultati su eksportovani u matlab fajlu scenario#scNum.m
void scenario (int scNum, network &netw, int T, int i1, int i2, double Qmax, bool DGplaced)
{
	if(i1 < 1 || i1 >= netw.getNumONodes() || i2 < 1 || i2 > netw.getNumONodes() )
	{
		cerr << "Error: got an illegal node number. Program stops..."<<endl;
		exit(EXIT_SUCCESS);
	}
	if (i1 == i2)
	{
		cerr << "Error: scenario2: the arguments must be different. Program stops.."<<endl;
		exit(EXIT_SUCCESS);
	}
	stringstream fname;
	fname<<"scenario"<<scNum<<".m";
	ofstream os(fname.str(), ofstream::out);
	os<<"Pdist = [... "<<endl;
	for(double Qc1=0; Qc1<=Qmax; Qc1+=0.5) //Qc [MVAr]
		for(double Qc2=0; Qc2<=Qmax; Qc2+=0.5)
		{
			double B1 = Qc1*1e6/pow(netw.getVb(1), 2);
			double B2 = Qc2*1e6/pow(netw.getVb(1), 2);
			netw.setCapacitorB(i1, B1);
			netw.setCapacitorB(i2, B2);
			setup(netw, T, DGplaced);
			os<<"\t"<<netw.getActiveConsumption();
			if (Qc2 == Qmax && Qc1 != Qmax)
				os<<";"<<endl;
			else if(Qc2 == Qmax && Qc1 == Qmax)
				os<<"];"<<endl;
		}
	os<<endl<<endl;
	os<<"Qdist = [..."<<endl;
	for(double Qc1=0; Qc1<=Qmax; Qc1+=0.5) //Qc [MVAr]
		for(double Qc2=0; Qc2<=Qmax; Qc2+=0.5)
		{
			double B1 = Qc1*1e6/pow(netw.getVb(1), 2);
			double B2 = Qc2*1e6/pow(netw.getVb(1), 2);
			netw.setCapacitorB(i1, B1);
			netw.setCapacitorB(i2, B2);
			setup(netw, T, DGplaced);
			os<<"\t"<<netw.getReactiveConsumption();
			if (Qc2 == Qmax && Qc1 != Qmax)
				os<<";"<<endl;
			else if(Qc2 == Qmax && Qc1 == Qmax)
				os<<"];"<<endl;
		}
	os<<endl<<endl;
	os<<"Ploss = [..."<<endl;
	for(double Qc1=0; Qc1<=Qmax; Qc1+=0.5) //Qc [MVAr]
		for(double Qc2=0; Qc2<=Qmax; Qc2+=0.5)
		{
			double B1 = Qc1*1e6/pow(netw.getVb(1), 2);
			double B2 = Qc2*1e6/pow(netw.getVb(1), 2);
			netw.setCapacitorB(i1, B1);
			netw.setCapacitorB(i2, B2);
			setup(netw, T, DGplaced);
			os<<"\t"<<netw.getActiveLosses();
			if (Qc2 == Qmax && Qc1 != Qmax)
				os<<";"<<endl;
			else if(Qc2 == Qmax && Qc1 == Qmax)
				os<<"];"<<endl;
		}
	os<<endl<<endl;
	os<<"Qloss = [..."<<endl;
	for(double Qc1=0; Qc1<=Qmax; Qc1+=0.5) //Qc [MVAr]
		for(double Qc2=0; Qc2<=Qmax; Qc2+=0.5)
		{
			double B1 = Qc1*1e6/pow(netw.getVb(1), 2);
			double B2 = Qc2*1e6/pow(netw.getVb(1), 2);
			netw.setCapacitorB(i1, B1);
			netw.setCapacitorB(i2, B2);
			setup(netw, T, DGplaced);
			os<<"\t"<<netw.getReactiveLosses();
			if (Qc2 == Qmax && Qc1 != Qmax)
				os<<";"<<endl;
			else if(Qc2 == Qmax && Qc1 == Qmax)
				os<<"];"<<endl;
		}
	os<<"Iroot = [..."<<endl;
	for(double Qc1=0; Qc1<=Qmax; Qc1+=0.5) //Qc [MVAr]
		for(double Qc2=0; Qc2<=Qmax; Qc2+=0.5)
		{
			double B1 = Qc1*1e6/pow(netw.getVb(1), 2);
			double B2 = Qc2*1e6/pow(netw.getVb(1), 2);
			netw.setCapacitorB(i1, B1);
			netw.setCapacitorB(i2, B2);
			setup(netw, T, DGplaced);
			os<<"\t"<<netw.getRootCurrent();
			if (Qc2 == Qmax && Qc1 != Qmax)
				os<<";"<<endl;
			else if(Qc2 == Qmax && Qc1 == Qmax)
				os<<"];"<<endl;
		}
	os<<endl<<endl;
	os<<"Qc = [..."<<endl;
	for(double Qc = 0; Qc <= Qmax; Qc+=0.5) //Qc [MVAr]
	{
		os<<"\t"<<Qc;
		if (Qc != Qmax)
			os<<";"<<endl;
		else
			os<<"];"<<endl;
	}
	netw.removeCapacitor(i1);
	netw.removeCapacitor(i2);
}

// Scenario 3:
// Proracun potrosene energije distributivne mreze i gubitaka energije (aktivnih)
// Proracun je izvrsena u toku jednog dana, smesti se jedan kondenzator na cvoru i
// Vrednost kompenzovane reaktivne snage je data u MVAr-ima,
//      Vrednost reaktivne snage se povecavana stepenasto sa 0.5 MVAr
// Rezultati su eksportovani u matlab fajlu scenario3.m
void scenario_day(int scNum, network& netw, int i, double Qmax, bool DGplaced)
{
	if(i < 1 || i >= netw.getNumONodes() )
	{
		cerr << "Error: got an illegal node number. Program stops..."<<endl;
		exit(EXIT_SUCCESS);
	}
	stringstream fname;
	fname << "scenario" << scNum << ".m";
	ofstream os(fname.str());
	os<<"Wdist"<<scNum<<" = [... "<<endl;
	for(double Qc = 0; Qc <= Qmax; Qc+=0.5) //Qc [MVAr]
	{
		double Wdist = 0;
		for(int T=0; T<23; T++)
		{
			double B = Qc*1e6/pow(netw.getVb(1), 2);
			netw.setCapacitorB(i, B);
			setup(netw, T, DGplaced);
			Wdist += netw.getActiveConsumption();
		}
		os<<"\t"<<Qc<<"\t"<<Wdist;
		if (Qc != Qmax)
			os<<";"<<endl;
		else
			os<<"];"<<endl;
	}
	os<<endl<<endl;
	os<<"Loss"<<scNum<<" = [... "<<endl;
	for(double Qc = 0; Qc <= Qmax; Qc+=0.5) //Qc [MVAr]
	{
		double Wloss = 0;
		for(int T=0; T<23; T++)
		{
			double B = Qc*1e6/pow(netw.getVb(1), 2);
			netw.setCapacitorB(i, B);
			setup(netw, T, DGplaced);
			Wloss += netw.getActiveLosses();
		}
		os<<"\t"<<Qc<<"\t"<<Wloss;
		if (Qc != Qmax)
			os<<";"<<endl;
		else
			os<<"];"<<endl;
	}
	os<<endl<<endl;
	os<<"Iroot"<<scNum<<" = [... "<<endl;
	for(double Qc = 0; Qc <= Qmax; Qc+=0.5) //Qc [MVAr]
	{
		double Iroot = 0;
		for(int T=0; T<23; T++)
		{
			double B = Qc*1e6/pow(netw.getVb(1), 2);
			netw.setCapacitorB(i, B);
			setup(netw, T, DGplaced);
			Iroot += netw.getRootCurrent();
		}
		os<<"\t"<<Qc<<"\t"<<Iroot;
		if (Qc != Qmax)
			os<<";"<<endl;
		else
			os<<"];"<<endl;
	}
	netw.removeCapacitor(i);
}

void results (network& netw, ostream& os)
{
	os<<"Original active power consumption: "<<netw.getActiveConsumption()*netw.getSb()/1e6<<" MW"<<endl;
	os<<"Original reactive power consumption: "<<netw.getReactiveConsumption()*netw.getSb()/1e6 <<" MVAr"<<endl;
	os<<"Original active losses: "<<netw.getActiveLosses()*netw.getSb()/1e6<<" MW"<<endl;
	os<<"Original reactive losses: "<<netw.getReactiveLosses()*netw.getSb()/1e6<<" MVAr"<<endl;
	os<<endl;
}

int main()
{
	diagram_initialization();

	export_diagram("Pdiag1.m", Pdiag1) ;
	export_diagram("Qdiag1.m", Qdiag1) ;
	export_diagram("Pdiag2.m", Pdiag2) ;
	export_diagram("Qdiag2.m", Qdiag2) ;
	export_diagram("Pdiag3.m", Pdiag3) ;
	export_diagram("Qdiag3.m", Qdiag3) ;
	cout<<endl;

    network netw("input.txt");

	double Qmax = 10; // MVAr

	bool DGplaced = false;

	scenario(1, netw, 12, 3, Qmax, DGplaced);
	scenario(2, netw, 12, 5, Qmax, DGplaced);
	scenario(3, netw, 12, 7, Qmax, DGplaced);

	scenario(4, netw, 12, 4, 5, Qmax, DGplaced);


	system("pause");
    return 0;
}
