#include "network.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>


// CONSTRUCTORS
network::network()
{
	node firstNode;
	branch Branch;
	node secondNode;

	nodes.push_back(firstNode);
	nodes.push_back(secondNode);
	branches.push_back(Branch);

	Sb = 1.0;
	double Vb1 = 1.0;

	Vb.push_back(Vb1);
	Vb.push_back(Vb1);

	filename = NULL;
}

network::network(network& n)
{
	branches = n.branches;
	nodes = n.nodes;

	Sb = n.Sb;
	Vb = n.Vb;

	filename = new char[strlen(n.filename)];
	strcpy (filename, n.filename);
}

network::~network()
{
	branches.clear();
	nodes.clear();
	Vb.clear();

}

network::network(const char* fname) : inputstream(fname, ifstream::in)
{
	cout<<"Initializing..."<<endl;
	filename = new char[strlen(fname)];
	strcpy(filename, fname);

	char ch;
	node firstNode;
	nodes.push_back(firstNode);

	word = new char[50] ;
	inputstream.getline(word, 50);
	bool got_Base = false ;
	bool got_Element = false;
	while( (ch = inputstream.get()) != -1 )
	{
		if ( !strncmp(word, "BASExx", 4 ) )
		{
			readBase();
			got_Base = true;
		}
		else if (!strncmp(word, "TRxx", 2 ) )
		{
			readTR();
			got_Element = true;
		}
		else if ( !strncmp(word, "VODxx", 3 ) )
		{
			readSection();
			got_Element = true;
		}
		else if ( !strncmp(word, "NODExx", 4 ) )
		{
			readNode();
		}
		else
		{
			inputstream.getline(word, 50);
		}
	}
	if ( !got_Base )
		error("Error: There are no base values added. Program stops...");

	if (nodes.size() == branches.size() + 1 )
	{
		cout<<"\tInitialized network is radial"<<endl;
	}
	else error("Error: The given network is not radial. Program stops..");

	bool consistent = true; // Consistent means, the node index in class is equal with the vector index
	for(int i=0; i<nodes.size(); i++ )
		consistent *= (nodes[i].getNodeNum() == i);
	for(int i=0; i<branches.size(); i++ )
		consistent *= (branches[i].getEndPoint() == i+1);

	if (consistent)
		cout<<"\tNodes are consistently initialized"<<endl;
	else error("Error: The network is not consistent. Program stops..");

	bool numedByLayers = true;
	int lastIndex = 0;
	for(int i=0; i<branches.size(); i++ )
	{
		 numedByLayers *= (branches[i].getBeginPoint() >= lastIndex);
		 lastIndex = branches[i].getBeginPoint() ;
	}
	if (numedByLayers)
		cout<<"\tNodes are numed by layers"<<endl;
	else error("Error: Nodes are not numed by layers. Program stops..");
	cout<<endl;

	for (int i=0; i<nodes.size(); i++)
	{
		if (i == 0)
			nodes[i].setShuntAdmitance( nodes[i].getShuntAdmitanse()/( Sb/pow(Vb[0], 2) )) ;
		else
			nodes[i].setShuntAdmitance( nodes[i].getShuntAdmitanse()/( Sb/pow(Vb[1], 2) )) ;
		nodes[i].setLoadPower( nodes[i].getLoadPower() / Sb );
		nodes[i].setPmax( nodes[i].getPmax() / Sb );
	}
	for (int i=0; i<branches.size(); i++)
	{
		if (i == 0)
			branches[i].setZ( branches[i].getImpedance()/( pow(Vb[0], 2)/ Sb ) ) ;
		else
			branches[i].setZ( branches[i].getImpedance()/( pow(Vb[1], 2)/ Sb ) ) ;
	}
}

//*** READ-HELPER FUNCTIONS
void network::readBase()
{
	char ch;
	int num;

	double Vb;

	bool got_Sb = false;
	bool got_Vb = false;

	while (true)
	{
		while ( !isalpha(ch = inputstream.get() ) && ch != -1 && !inputstream.eof() )
			;
		inputstream.putback(ch);
		inputstream>>word;

		double* pointer;
		bool* got_flag;

		if ( ch != -1 && !inputstream.eof() && !strcmp(word, "Sb") )
		{
			pointer = &Sb;
			got_flag = &got_Sb;
		}
		else if ( ch != -1 && !inputstream.eof() && !strncmp(word, "Vbx", 2) )
		{
			pointer = &Vb;
			got_flag = &got_Vb;
		}
		else if ( ch == -1 || inputstream.eof() || !strcmp(word, "BASE") || !strncmp(word, "VODxx", 3) || !strncmp(word, "TRxx", 2) || !strncmp(word, "NODExx", 4) )
		{
			break;
		}
		else
		{
			continue;
		}

		*got_flag = true;
		while ( !isdigit(ch = inputstream.get() )  && ch != -1 && !inputstream.eof())
			;
		inputstream.putback(ch);
		inputstream>>*pointer;
		while ( isspace(ch = inputstream.get() ) &&  ch != -1 && !inputstream.eof() )
			;
		inputstream.putback(ch);
		inputstream>>word;
		if (!strncmp(word,"kxx",1) )
			*pointer *= 1e3;
		else if (!strncmp(word,"Mxx",1) )
			*pointer *= 1e6;
		if (pointer == &Vb)
			this->Vb.push_back(Vb);
	}
	if (!got_Sb || !got_Vb)
		error("Error: Some base parameters are missing");
}

void network::readTR()
{
	char ch;

	double beginpoint;
	double Sn;
	double Vn1;
	double uk;
	double Pcu;
	double X;
	double R;
	double tmax;
	double du;

	bool got_begpoint = false;
	bool got_Sn = false;
	bool got_Vn1 = false;
	bool got_uk = false;
	bool got_Pcu = false;
	bool got_tmax = false;
	bool got_du = false;

	while (true)
	{
		while ( !isalpha(ch = inputstream.get() )  && ch != -1 && !inputstream.eof() )
			;
		inputstream.putback(ch);
		inputstream>>word;

		double* pointer;
		bool* got_flag;

		if ( ch != -1 && !inputstream.eof() && !strcmp(word, "beginpoint") )
		{
			pointer = &beginpoint;
			got_flag = &got_begpoint;
		}
		else if ( ch != -1 && !inputstream.eof() && !strcmp(word, "Sn") )
		{
			pointer = &Sn;
			got_flag = &got_Sn;
		}
		else if ( ch != -1 && !inputstream.eof() && !strcmp(word, "Vn1") )
		{
			pointer = &Vn1;
			got_flag = &got_Vn1;
		}

		else if (  ch != -1 && !inputstream.eof() && !strcmp(word, "uk") )
		{
			pointer = &uk;
			got_flag = &got_uk;
		}
		else if (  ch != -1 && !inputstream.eof() && !strcmp(word, "Pcu") )
		{
			pointer = &Pcu;
			got_flag = &got_Pcu;
		}
		else if (  ch != -1 && !inputstream.eof() && !strcmp(word, "tmax") )
		{
			pointer = &tmax;
			got_flag = &got_tmax;
		}
		else if (  ch != -1 && !inputstream.eof() && !strcmp(word, "du") )
		{
			pointer = &du;
			got_flag = &got_du;
		}
		else if (  ch == -1 && inputstream.eof() || !strcmp(word, "BASE") || !strncmp(word, "VODxx", 3) || !strncmp(word, "TRxx", 2) || !strncmp(word, "NODExx", 4) )
		{
			break;
		}
		else
			continue;

		if ( *got_flag )
			error("Error: Transformer parameter cannot be initialized twice. Program stops..");
		*got_flag = true;
		while ( !isdigit(ch = inputstream.get() ) &&  ch != -1 && !inputstream.eof() )
			;
		inputstream.putback(ch);
		inputstream>>*pointer;
		if ( !strcmp(word, "Sn") || !strcmp(word, "Vn1") || !strcmp(word, "uk") || !strcmp(word, "Pcu") ||  !strcmp(word, "du"))
		{
			while ( isspace(ch = inputstream.get() ) &&  ch != -1 && !inputstream.eof() )
				;
			inputstream.putback(ch);
			inputstream>>word;
			if (!strncmp(word,"kxx", 1) )
				*pointer *= 1e3;
			else if (!strncmp(word,"Mxx", 1) )
				*pointer *= 1e6;
		}
	}

	if ( !got_begpoint || !got_Sn || !got_Vn1 || !got_uk )
		error("Error: Transformer: a vital parameter is missing");
	if ( (got_tmax && !got_du) || (!got_tmax && got_du) )
		error("Error: some transformer regulation parameter is missing" );

	X = uk*pow(Vn1,2) / (100*Sn);
	R = 0;
	if (got_Pcu)
	{
		R = Pcu*pow(Vn1,2) / (3*pow(Sn,2)) ;
		X = sqrt( pow(X,2) - pow(R,2) );
	}
	if (got_tmax && got_du)
	{
		branch trbranch(beginpoint, R, X, tmax, du);
		branches.push_back(trbranch);
	}
	else
	{
		branch trbranch(beginpoint, R, X);
		branches.push_back(trbranch);
	}
	node endNode;
	nodes.push_back(endNode);
}

void network::readSection()
{
	char ch;

	double beginpoint;
	double r=0;
	double x=0;
	double g=0;
	double b=0;
	double l=0;

	bool got_begpoint = false;
	bool got_r = false;
	bool got_x = false;
	bool got_g = false;
	bool got_b = false;
	bool got_l = false;

	while (true)
	{
		while ( !isalpha(ch = inputstream.get() ) &&  ch != -1 && !inputstream.eof() )
			;
		inputstream.putback(ch);
		inputstream>>word;

		double* pointer;
		bool* got_flag;

		if (  ch != -1 && !inputstream.eof() && !strcmp(word, "beginpoint") )
		{
			pointer = &beginpoint;
			got_flag = &got_begpoint;
		}
		else if (  ch != -1 && !inputstream.eof() && !strcmp(word, "x") )
		{
			pointer = &x;
			got_flag = &got_x;
		}
		else if (  ch != -1 && !inputstream.eof() && !strcmp(word, "r") )
		{
			pointer = &r;
			got_flag = &got_r;
		}
		else if (  ch != -1 && !inputstream.eof() && !strcmp(word, "b") )
		{
			pointer = &b;
			got_flag = &got_b;
		}
		else if (  ch != -1 && !inputstream.eof() && !strcmp(word, "g") )
		{
			pointer = &g;
			got_flag = &got_g;
		}
		else if (  ch != -1 && !inputstream.eof() && !strcmp(word, "l") )
		{
			pointer = &l;
			got_flag = &got_l;
		}
		else if (  ch == -1 && inputstream.eof() || !strcmp(word, "BASE") || !strncmp(word, "VODxx", 3) || !strncmp(word, "TRxx", 2) || !strncmp(word, "NODExx", 4) )
		{
			break;
		}
		else
			continue;

		if ( *got_flag )
			error("Error: A section cannot be initialized twice. Program stops..");
		*got_flag = true;
		while ( !isdigit(ch = inputstream.get() ) &&  ch != -1 && !inputstream.eof() )
			;
		inputstream.putback(ch);
		inputstream>>*pointer;
		if ( !strcmp(word, "b") || !strcmp(word, "g") )
		{
			while ( isspace(ch = inputstream.get() ) &&  ch != -1 && !inputstream.eof() )
				;
			inputstream.putback(ch);
			inputstream>>word;
			if (!strncmp(word,"m_xx", 1) )
				*pointer *= 1e-3;
		}
	}
	if ( !got_l || !got_x)
		error("Error: Section: a vital parameter is missing");

	nodes[beginpoint].setShuntAdmitance(nodes[beginpoint].getG() + g*l/2, nodes[beginpoint].getB() + b*l/2);

	branch lineBranch(beginpoint, r*l, x*l);
	branches.push_back(lineBranch);

	node endNode(g*l/2, b*l/2);
	nodes.push_back(endNode);
}

void network::readNode()
{
	char ch;

	double num = 0;
	double Pp = 0;
	double Qp = 0;
	double Pmax = 0;
	double loadType = 0;

	bool got_Num = false;
	bool got_Pp = false;
	bool got_Qp = false;
	bool got_Pmax = false;
	bool got_LoadType = false;

	while (true)
	{
		while ( !isalpha(ch = inputstream.get() ) && !inputstream.eof() )
			;
		inputstream.putback(ch);
		inputstream>>word;

		double* pointer;
		bool* got_flag;
		if ( ch != -1 && !inputstream.eof() && !strcmp(word, "nodeNum") )
		{
			pointer = &num;
			got_flag = &got_Num;
		}
		else if ( ch != -1 && !inputstream.eof() && !strcmp(word, "Pp"))
		{
			pointer = &Pp;
			got_flag = &got_Pp;
		}
		else if ( ch != -1 && !inputstream.eof() && !strcmp(word, "Qp") )
		{
			pointer = &Qp;
			got_flag = &got_Qp;
		}
		else if ( ch != -1 && !inputstream.eof() && !strcmp(word, "Pmax") )
		{
			pointer = &Pmax;
			got_flag = &got_Pmax;
		}
		else if ( ch != -1 && !inputstream.eof() && !strcmp(word, "loadtype") )
		{
			pointer = &loadType;
			got_flag = &got_LoadType;
		}
		else if ( !strcmp(word, "BASE") || !strncmp(word, "VODxx", 3) || !strncmp(word, "TRxx", 2) || !strncmp(word, "NODExx", 4) || inputstream.eof() || ch == -1)
		{
			break;
		}
		else
		{
			continue;
		}

		if ( *got_flag )
			error("Error: A node parameter cannot be initialized twice. Program stops..");
		*got_flag = true;

		while ( !isdigit(ch = inputstream.get() ) && ch != -1 && !inputstream.eof()  && ch != '-')
			;

		inputstream.putback(ch);
		inputstream>>*pointer;
		if( !strcmp(word, "Pp") || !strcmp(word, "Qp") || !strcmp(word, "Pmax") )
		{
			while ( isspace(ch = inputstream.get() ) && ch != -1 && !inputstream.eof() && ch != '-')
				;
			inputstream.putback(ch);
			inputstream>>word;
			if (!strncmp(word,"kxx", 1) )
				*pointer *= 1e3;
			else if (!strncmp(word,"Mxx", 1) )
				*pointer *= 1e6;
		}
	}
	if (!got_Num )
		error("Error: Node: a vital parameter is missing");

	nodes[num].setPmax(Pmax);
	nodes[num].setLoadPower(Pp, Qp);
	nodes[num].setLoadType(loadType);
}

void network::error(const char* errorstring)const
{
	cerr<<errorstring<<endl;
	exit(EXIT_SUCCESS);
}


double network::getVb(int i)const
{
	if (i>=0 && i<Vb.size() )
	{
		return Vb[i];
	}
	error("Error: Wrong indexparameter in getVb()");
	return 0;
}

double network::getActiveConsumption()
{
	complex<double> S = getConsumption();
	return S.real();
}

double network::getReactiveConsumption()
{
	complex<double> S = getConsumption();
	return S.imag();
}

double network::getActiveLosses()
{
	double Pp = 0;
	for (int i=0; i<nodes.size(); i++)
		Pp += nodes[i].getActivePowerInjection();
	return getActiveConsumption() - Pp;
}

double network::getReactiveLosses()
{
	double Qp = 0;
	for (int i=0; i<nodes.size(); i++)
		Qp += nodes[i].getReactivePowerInjection();
	return getReactiveConsumption() - Qp;
}



void network::getVoltagePNode(ostream& os)
{
	for (int i=0; i<nodes.size(); i++)
		os<<nodes[i].getVoltageMagnitude()<<"\t"<<nodes[i].getVoltagePhase()<<endl;
}

void network::getLoadPowerPNode(ostream& os)
{
	for (int i=0; i<nodes.size(); i++)
		os<<nodes[i].getActivePowerInjection()<<"\t"<<nodes[i].getReactivePowerInjection()<<endl;
}

void network::printFileName ()
{
	if (strlen(filename) != 0)
		cout<<filename<<endl;
	else
		cout<<"A network has no initializer file"<<endl;
}

void network::printNode (int i)
{
	if (i>=0 && i<nodes.size() )
		cout<<nodes[i]<<endl;
	else
		error("Error: printNode(): Wrong indexing");
}

void network::printBranch (int i)
{
	if (i>=0 && i<nodes.size() )
		cout<<nodes[i]<<endl;
	else
		error("Error: printBranch(): Wrong indexing");
}


void network::setCapacitorC(int i, double value)
{
	double Vbase;
	if (i == 0)
		Vbase = Vb[0];
	else
		Vbase = Vb[1];
	value /= Sb / pow(Vbase,2);
	nodes[i].setCapacitorC(value);
}

void network::setCapacitorB(int i, double value)
{
	double Vbase;
	if (i == 0)
		Vbase = Vb[0];
	else
		Vbase = Vb[1];
	value /= Sb/pow(Vbase,2);
	nodes[i].setCapacitorB(value);
}


void network::solvePowerFlow()
{
	// Shirmohammadi algorithm
	int f = 0;
	double epsilon = 1e-3; // 3.15 kW

	while(true)
	{
		// Calculate injection currents
		for (int i=0; i<nodes.size(); i++)
		{
			nodes[i].setLoadCurrent (
				conj( nodes[i].getLoadPower() / nodes[i].getVoltage() ) + nodes[i].getVoltage()*nodes[i].getShuntAdmitanse() );
		}

		// Calculate branch currents
		for (int i=branches.size(); i>0; i--)
		{
			branches[i-1].setCurrent( nodes[i].getLoadCurrent() );
			for (int j=i; j<branches.size(); j++)
				if (branches[j].getBeginPoint() == branches[i-1].getEndPoint() )
				{
					complex<double> surplus = branches[i-1].getCurrent();
					surplus += branches[j].getCurrent();
					branches[i-1].setCurrent(surplus);
				}
		}

		// Calculate voltage drops
		for (int i=1; i<nodes.size(); i++)
		{
			nodes[i].setVoltage(
				nodes[ branches[i-1].getBeginPoint()].getVoltage() - branches[i-1].getImpedance()* branches[i-1].getCurrent() );
			if ( branches[i-1].isRegulative() )
			{
				double a = 1 + branches[i-1].getTapChangerPos() * branches[i-1].getDeltaU()/100 ;
				nodes[i].setVoltage( nodes[i].getVoltage() / a) ;
			}
		}

		//Testing delta
		bool pass = true;
		for (int i=0; i<nodes.size(); i++)
		{
			complex<double> S = nodes[i].getVoltage()*conj(nodes[i].getLoadCurrent()) - conj(nodes[i].getShuntAdmitanse())*pow(
				nodes[i].getVoltageMagnitude(), 2) ;
			complex<double> dS = (S - nodes[i].getLoadPower()) ;

			if ( abs(dS.real()) > epsilon || abs(dS.imag()) > epsilon )
			{
				pass = false;
				break;
			}
		}
		f++;
		if (pass )
			break;
		if (f >= 1000)
			error("Error: The power flow failed to convergate");
	}
}


ostream& operator<< (ostream& os, network n)
{
	os<<"Network from file: "<<n.filename<<endl<<endl;
	os<<"Sb = "<<n.Sb<<" W"<<endl;
	for (int i=0; i<n.Vb.size(); i++)
		os<<"Vb["<<i<<"] = "<<n.Vb[i]<<" V"<<endl;
	os<<endl;
	os<<"NODES"<<endl;
	for (int i=0; i<n.nodes.size(); i++)
		os<<"\t"<<n.nodes[i]<<endl;
	os<<endl;
	os<<"BRANCHES"<<endl;
	for (int i=0; i<n.branches.size(); i++)
		os<<"\t"<<n.branches[i]<<endl;
	return os;
}
