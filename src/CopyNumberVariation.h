#ifndef __COPYNUMBER_H__
#define __COPYNUMBER_H__

#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "types.h"
#include "Operations.h"



class CopyNumberVariation {
public:
    CopyNumberVariation(std::string const& copyNumberVariationFile,int ploidy, std::string const& genomeLengthFile);
	virtual ~CopyNumberVariation();
	std::vector<std::vector<CNVentry> > getCNlist();
	long getCNVgenomeLength();

private:
    std::vector<std::vector<CNVentry> > CNVlist;
    long CNVgenomeLength;
  };

#endif
