#include "CopyNumberVariation.h"

using namespace std;


CopyNumberVariation::CopyNumberVariation(std::string const& copyNumberVariationFile, int ploidy, std::string const& genomeLengthFile) {

    //computing genome length
    cout << ".. Reading chromosomes length file and computing genome length\n";
    ifstream genomeLengthFileStream(genomeLengthFile.c_str());
    string line, prechr = "";
    std::vector<std::string> strs;
    long chromosomesLength = 0;
    long genomeLength;
    int chrNum = 0;
    if (!genomeLengthFileStream.is_open()) {
        cerr << ".. Unable to open " + genomeLengthFile + " file for reading\n";
        exit (-1);
    }
    else {
        while (!genomeLengthFileStream.eof() && chrNum < 24) {
            getline(genomeLengthFileStream, line);
            strs = split(line, '\t');
            chromosomesLength += atof(strs[2].c_str());
            chrNum++;
        }
    }
    strs.clear();
    genomeLengthFileStream.close();
	genomeLength = chromosomesLength * ploidy;
	cout << "Genome length before copy number variation:" << genomeLength << "\n";
	CNVgenomeLength = genomeLength;

	//read the copy number variations from file
	cout << ".. Reading copy number variation file\n";
    ifstream copyNumberVariationFileStream(copyNumberVariationFile.c_str());
    std::vector<CNVentry> CNVvector;
    CNVentry entry;
    if (!copyNumberVariationFileStream.is_open()) {
        cerr << ".. Unable to open " + copyNumberVariationFile + " file for reading\n";
        exit (-1);
    }
    else {
        while (!copyNumberVariationFileStream.eof()) {
            getline(copyNumberVariationFileStream, line);
            if (!line.length()) continue;
            strs = split(line, '\t');
            entry.chr = strs[0].c_str();
            if (prechr == "")
                prechr = entry.chr;
            if (entry.chr != prechr) {
                CNVlist.push_back(CNVvector);
                prechr = entry.chr;
                CNVvector.clear();
            }
            entry.start = atof(strs[1].c_str());
            entry.end = atof(strs[2].c_str());
            entry.cn = atof(strs[3].c_str());
            if (!strs[4].compare("loss")) {
                CNVgenomeLength -= ((entry.end - entry.start + 1) * (ploidy - entry.cn));
            } else {
                CNVgenomeLength += ((entry.end - entry.start + 1) * (entry.cn - ploidy));
            }
            CNVvector.push_back(entry);
        }
        CNVlist.push_back(CNVvector);
    }
    CNVvector.clear();
    strs.clear();
    copyNumberVariationFileStream.close();
    cout << "Genome length after copy number variation:" << CNVgenomeLength << "\n";
}

CopyNumberVariation::~CopyNumberVariation() {
	// TODO Auto-generated destructor stub
	CNVlist.clear();
}


std::vector<std::vector<CNVentry> > CopyNumberVariation::getCNlist() {
    return CNVlist;
}


long CopyNumberVariation::getCNVgenomeLength() {
    return CNVgenomeLength;
}

