#pragma once
#ifndef __GCDISTRIBUTION_H__
#define __GCDISTRIBUTION_H__

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "Operations.h"
#include "math.h"
#include "types.h"
#include "Signal.h"

class GCDistribution {

public:
    GCDistribution(std::string const& GCdistribution, std::string const& outputGCDistribution, std::string const& genomeFile, int readNumber, int ploidy, int fragmentLength, float noiseLevel, long genomeLength, std::vector<std::vector<CNVentry> >  CNVlist, Signal signalRegions, sequanceType seqType);
    std::vector<GCentry> getGClist();

private:
    std::vector<GCentry> GClist;
};

#endif
