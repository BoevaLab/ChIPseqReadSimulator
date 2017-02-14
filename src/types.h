#ifndef TYPES_H_
#define TYPES_H_

#include <vector>
#include <map>
#include <string>

struct CNVentry {
    std::string chr;
	int start;
	int end;
	int cn;
};

struct PEAKentry{
	std::string chr;
	int start;
	int end;
    double score;
};

struct ERRORRATEentry{
	double error;
};

struct SIGNALREGIONentry{
	std::string chr;
	int signalRegionStart;
	int signalRegionEnd;
};

struct SIGNALNUCLEOSOMEentry{
	std::string chr;
	int signalRegionStart;
	int signalRegionEnd;
    int signalNucleosomeStart;
	int signalNucleosomeEnd;
	int signalNucleosomeCN;
};



enum sequanceType {
	Input,
	ChipSignal,
	ChipBackground
};

struct GCentry{
	double start;
	double end;
	double GCcontent;
	double GCfrequency;
};

#endif


