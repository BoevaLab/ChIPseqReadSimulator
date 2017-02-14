#include "ErrorRate.h"

using namespace std;



ErrorRate::ErrorRate(std::string const& errorRateFile) {
	//read the error rates from file
	cout << ".. Reading error rate file\n";
	ifstream errorRateFileStream(errorRateFile.c_str());
	string line;
    ERRORRATEentry entry;
    if (!errorRateFileStream.is_open())	{
        cerr << ".. Unable to open " + errorRateFile + " file for reading\n";
        exit (-1);
    }
    while (!errorRateFileStream.eof())	{
        getline (errorRateFileStream, line);
        if (!line.length()) continue;
        entry.error = atof(line.c_str());
        ERRORRATElist.push_back(entry);
    }
    errorRateFileStream.close();
}

ErrorRate::~ErrorRate() {
	// TODO Auto-generated destructor stub
}

vector<ERRORRATEentry> ErrorRate::getERRORRATElist() {
    return ERRORRATElist;
}
