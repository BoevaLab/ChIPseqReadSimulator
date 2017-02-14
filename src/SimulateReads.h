#pragma once
#ifndef __SIMULATEREADS_H__
#define __SIMULATEREADS_H__

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "Signal.h"
#include "Operations.h"
#include "Read.h"
#include "types.h"
#include "ErrorRate.h"

class SimulateReads {

public:
    SimulateReads(std::string const& genomeFile, int readLength, int ploidy, int fragmentLength, std::vector<ERRORRATEentry> ERRORRATElist,  std::vector<std::vector<CNVentry> > CNVlist, std::vector<GCentry> GClist, Signal signalRegions, std::string const&  outputFile, sequanceType seqType);
    bool checkGC(double GCrand, double GCpercent, std::vector<GCentry> GClist);

private:

};

#endif
