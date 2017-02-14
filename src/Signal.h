#pragma once
#ifndef __SIGNAL_H__
#define __SIGNAL_H__

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "types.h"
#include "Operations.h"


class Signal {

  public:
      Signal(int nucleosomeDist, int ploidy, int fragmentLength, std::vector<std::vector<CNVentry> > CNVlist, std::vector<std::vector<PEAKentry> > PEAKlist, std::string const& outputSignalRegions);
      int getTotalSignalNucleosomeLength();

  private:
      std::vector<SIGNALREGIONentry> SIGNALREGIONlist;
      std::vector<SIGNALNUCLEOSOMEentry> SIGNALNUCLEOSOMElist;
      int numberOfSignalRegions;
      int numberOfSignalNucleosomes;
      int totalSignalNucleosomeLength;
};

#endif


