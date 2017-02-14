#ifndef PEAKS_H_
#define PEAKS_H_

#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "types.h"
#include "Operations.h"


class Peaks {
public:
    Peaks (std::string const& peakSignalsFile);
	virtual ~Peaks();
	std::vector<std::vector<PEAKentry> > getPEAKlist();

private:
    std::vector<std::vector<PEAKentry> > PEAKlist;
};

#endif
