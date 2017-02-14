#pragma once
#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include <vector>
#include <string>
#include <sstream>

#include "math.h"
#include "types.h"


class Operations {

public:
	Operations(void);
	~Operations(void);
};

    std::vector<std::string> &split (const std::string &s, char delim, std::vector<std::string> &elems);
    std::vector<std::string> split (const std::string &s, char delim);
    int getCopyNumber (std::vector<std::vector<CNVentry> > CNVlist, int chrnum, int positionStart, int ploidy, int fragmentLength);
	int isGC (const char & a) ;
    int isN (const char & a) ;
    long double sum (const std::vector<double>& data);
    int round(float r);

#endif
