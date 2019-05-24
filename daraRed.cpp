#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 
#include <GeographicLib/Geocentric.hpp>
#include <GeographicLib/LocalCartesian.hpp>


using namespace std;
using namespace GeographicLib;

int main(int argc, char *argv[])
{
	try 
	{
		Geocentric earth(Constants::WGS84_a(), Constants::WGS84_f());
		fstream infile;
		fstream outfile;
		cout << argv[1]<<endl;
		string inname="data/gpsData";
		inname.append(argv[1]);
		string outname="data/reduced";
		outname.append(argv[1]);
		string line;
		infile.open(inname, fstream::in);
		outfile.open(outname, fstream::out | fstream::trunc);
		int i = 0;
		int numData = 0;
		size_t found;
		long double lati,longi,alti;
		while (!(infile.eof()))
		{
			infile >> line;
			found = line.find("latitude");
			if (found!=string::npos)
			{
				infile >>lati;
				i++;
			}
			found = line.find("longitude");
			if (found!=string::npos)
			{
				infile>>longi;
				i++;
			}
			found = line.find("altitude");
			if (found!=string::npos)
			{
				infile>>alti;
				i++;
			}
			found = line.find("---");
			if (found!=string::npos)
			{
				if (i==3)
				{
					outfile<<setprecision(10)<<lati<<" "<<setprecision(10)<<longi<<" "<<setprecision(10)<<alti<<endl;
				}
				i=0; 
				numData++;
			}

			//cout << line <<endl;

		}
		outfile.close();
		infile.close();
		infile.open(outname, fstream::in);
		outname = "data/localized";
		outname.append(argv[1]);
		outfile.open(outname, fstream::out | fstream::trunc);
		double* longAr = new double[numData];
		double* latiAr = new double[numData];
		double* altiAr = new double[numData];
		double latiMean, longMean;
		latiMean = 0;
		longMean = 0;
		for (int j=0; j<(numData-1);j++)
		{
			infile>>latiAr[j];
			infile>>longAr[j];
			infile>>altiAr[j];
			latiMean+=latiAr[j];
			longMean+=longAr[j];
		}

		latiMean = latiMean/(numData-1);
		longMean = longMean/(numData-1);
		
		const double lat0 = 51.49842113, lon0 = -0.177425392; // Paris
    	LocalCartesian proj(lat0, lon0, 0, earth);
    	/*
    	{
      // Sample forward calculation
     		 double lat = 50.9, lon = 1.8, h = 0; // Calais
     		 double x, y, z;
     		 proj.Forward(lat, lon, h, x, y, z);
     		 cout << x << " " << y << " " << z << "\n";
    	}
    	*/
    	double x, y, z;
    	double h=0;
    	for (int j=0; j<numData-1;j++)
		{
			proj.Forward(latiAr[j], longAr[j], h, x, y, z);
			outfile<<setprecision(10)<<x<<" "<<setprecision(10)<<y<<" "<<setprecision(10)<<z<<endl;
		}
		
		cout <<setprecision(10)<<latiMean<<" "<<setprecision(10)<<longMean<<endl;
		infile.close();
		outfile.close();
	}
  catch (const exception& e) 
  	{
   		cerr << "Caught exception: " << e.what() << "\n";
  	  	return 1;
 	}
	
	return 0;
}
