#ifndef ERRORRATE_H_
#define ERRORRATE_H_

#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "types.h"


class ErrorRate {
public:
    ErrorRate(std::string const& errorRateFile);
	virtual ~ErrorRate();
	std::vector<ERRORRATEentry> getERRORRATElist();

private:
    std::vector<ERRORRATEentry> ERRORRATElist;
};

#endif
