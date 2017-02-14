#include "Signal.h"

using namespace std ;

Signal::Signal(int nucleosomeDist, int ploidy, int fragmentLength, std::vector<std::vector<CNVentry> > CNVlist, std::vector<std::vector<PEAKentry> > PEAKlist, std::string const& outputSignalRegions) {
    int numberOfNucleosomesPerSignalRegion;
    int regionStart;
    int regionEnd;
    int regionLength;
    int nucleosomeStart;
    int nucleosomeEnd;
    int nucleosomeCN;
    SIGNALREGIONentry regionEntry;
    SIGNALNUCLEOSOMEentry nucleosomEntry;
    totalSignalNucleosomeLength = 0;

    cout << ".. Output file " + outputSignalRegions + " is contained signal regions.\n";
    std::ofstream outputSignalRegionsStream (outputSignalRegions.c_str());
    outputSignalRegionsStream << "Chromosome\tSignalNucleosomeStartPosition\tSignalNucleosomeEndPosition\tSignalCopyNumber\tSignalRegionStartPosition\tSignalRegionEndPosition\n";

    //cout << ".. i:" << i << " j:" << j << " n:" << n << "\t";
    //cout << ".. nucleosomeStart:" << nucleosomeStart << "\t";
    //cout << ".. nucleosomeEnd:" << nucleosomeEnd << "\t";
    //cout << ".. nucleosomeCN:" << nucleosomeCN << "\n";



    for (int i = 0; i < PEAKlist.size(); i++) {
        for (int j = 0; j < PEAKlist[i].size(); j++) {
            regionStart = PEAKlist[i][j].start;
            regionEnd = PEAKlist[i][j].end;
            regionLength = regionEnd - regionStart;
            regionEntry.chr = PEAKlist[i][j].chr;
            regionEntry.signalRegionStart = regionStart;
            regionEntry.signalRegionEnd = regionEnd;
            SIGNALREGIONlist.push_back(regionEntry);

            numberOfNucleosomesPerSignalRegion = regionLength/nucleosomeDist;
            nucleosomeStart = regionStart - fragmentLength;
            nucleosomeEnd = regionStart;
            for (int n = 0; n < numberOfNucleosomesPerSignalRegion && nucleosomeEnd <= regionEnd; n++) {
                nucleosomeCN = getCopyNumber(CNVlist, i, nucleosomeStart, ploidy, fragmentLength);
                nucleosomEntry.chr = regionEntry.chr;
                nucleosomEntry.signalRegionStart = regionStart;
                nucleosomEntry.signalRegionEnd = regionEnd;
                nucleosomEntry.signalNucleosomeStart = nucleosomeStart;
                nucleosomEntry.signalNucleosomeEnd = nucleosomeEnd;
                nucleosomEntry.signalNucleosomeCN = nucleosomeCN;
                SIGNALNUCLEOSOMElist.push_back(nucleosomEntry);
                totalSignalNucleosomeLength += fragmentLength * nucleosomeCN;
                outputSignalRegionsStream << nucleosomEntry.chr << "\t" << nucleosomeStart << "\t" << nucleosomeEnd << "\t"<< nucleosomeCN << "\t" << regionStart<< "\t" << regionEnd << "\n";
                nucleosomeEnd = nucleosomeEnd + nucleosomeDist;
                nucleosomeStart = nucleosomeEnd - fragmentLength;
            }
        }
    }
    outputSignalRegionsStream.close();
    numberOfSignalRegions = SIGNALREGIONlist.size();
    numberOfSignalNucleosomes = SIGNALNUCLEOSOMElist.size();
    cout << ".. Number of Signal Regions:" << numberOfSignalRegions << "\n";
    cout << ".. Number of Signal Nucleosomes: " << numberOfSignalNucleosomes << "\n";
    cout << ".. Total Signal Nucleosome Length: " << totalSignalNucleosomeLength << "\n";
}


int Signal::getTotalSignalNucleosomeLength() {
    return totalSignalNucleosomeLength;
}
