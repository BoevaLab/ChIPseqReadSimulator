#include "Operations.h"

using namespace std ;

Operations::Operations(void) {
}

Operations::~Operations(void) {
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return split(s, delim, elems);
}

int getCopyNumber(std::vector<std::vector<CNVentry> > CNVlist, int chrnum, int positionStart, int ploidy, int fragmentLength) {
    int copyNumber = ploidy;
    //TODO: check the chromosome
    for(vector<CNVentry>::iterator it = CNVlist[chrnum].begin(); it != CNVlist[chrnum].end(); ++it) {
        if (positionStart >= ((*it).start - (fragmentLength / 3)) && positionStart < ((*it).end - (fragmentLength / 3))) {
            copyNumber = (*it).cn;
            break;
        }
    }
    return copyNumber;
}


int isGC (const char& n) {
	if ((n == 'C') || (n == 'c') || (n == 'G') || (n == 'g'))
		return 1;
	return 0;
}


int isN (const char & n) {
	if ((n == 'N')||(n == 'n'))
		return 1;
	return 0;
}

long double sum (const std::vector<double>& data) {
	long double sum = 0;
	for (int i = 0; i < (int)data.size(); i++) {
		sum += data[i];
	}
	return sum;
}

int round(float r) {
    return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}



