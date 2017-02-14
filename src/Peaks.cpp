#include "Peaks.h"

using namespace std;


Peaks::Peaks(std::string const& peakSignalsFile) {

    //read peak signals from file
    cout << ".. Reading peak signals file\n";
    ifstream peakSignalsFileStream(peakSignalsFile.c_str());
    std::vector<PEAKentry> PEAKvector;
    PEAKentry entry;
    string line, prechr = "";
    std::vector<std::string> strs;
    if (!peakSignalsFileStream.is_open()) {
        cerr << "Unable to open " + peakSignalsFile + " file for reading\n";
        exit (-1);
    }
    else {
        while (!peakSignalsFileStream.eof()) {
            getline (peakSignalsFileStream, line);
            if (!line.length()) continue;
            strs = split(line, '\t');
            entry.chr = strs[0].c_str();
            if (prechr == "")
                prechr = entry.chr;
            if (entry.chr != prechr) {
                PEAKlist.push_back(PEAKvector);
                prechr = entry.chr;
                PEAKvector.clear();
            }
            entry.start = atof(strs[1].c_str());
            entry.end = atof(strs[2].c_str());
            entry.score = atof(strs[4].c_str());
            if (entry.score >= 10)
                PEAKvector.push_back(entry);
        }
        PEAKlist.push_back(PEAKvector);
    }
    strs.clear();
    PEAKvector.clear();
    peakSignalsFileStream.close();
}

Peaks::~Peaks() {
	// TODO Auto-generated destructor stub
	PEAKlist.clear();
}

std::vector<std::vector<PEAKentry> > Peaks::getPEAKlist() {
    return PEAKlist;
}
