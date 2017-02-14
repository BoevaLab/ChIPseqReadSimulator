#include "GCDistribution.h"

using namespace std ;


GCDistribution::GCDistribution(std::string const& GCdistribution, std::string const& outputGCDistribution, std::string const& genomeFile, int readNumber, int ploidy, int fragmentLength, float noiseLevel, long genomeLength, std::vector<std::vector<CNVentry> > CNVlist, Signal signalRegions, sequanceType seqType) {
    double correctionNonMap = 1.102;
    double averageReadsPerPosition;
    std::ofstream outputGCDistributionStream;
    switch (seqType) {
    case Input:
        averageReadsPerPosition = readNumber * 1./ genomeLength * correctionNonMap;
        cout << "\n\n.. Average number of reads per position for Input is: " << averageReadsPerPosition << "\n";
        cout << ".. Output file " << outputGCDistribution << " is contained GC distribution.\n";
        outputGCDistributionStream.open(outputGCDistribution.c_str());
        outputGCDistributionStream << "Input\n";
        break;
    case ChipSignal:
        averageReadsPerPosition = readNumber * (1 - noiseLevel) / signalRegions.getTotalSignalNucleosomeLength() * correctionNonMap;
        cout << "\n\n.. Average number of reads per position for Chip signal is: " << averageReadsPerPosition << "\n";
        cout << ".. Output file " + outputGCDistribution + " is contained GC distribution.\n";
        outputGCDistributionStream.open(outputGCDistribution.c_str(), ios_base::app);
        outputGCDistributionStream << "\n\nChipSignal\n";
        break;
    case ChipBackground:
        averageReadsPerPosition = readNumber * (noiseLevel) / (genomeLength - signalRegions.getTotalSignalNucleosomeLength()) * correctionNonMap;
        cout << "\n\n.. Average number of reads per position for Chip background is: " << averageReadsPerPosition << "\n";
        cout << ".. Output file " + outputGCDistribution + " is contained GC distribution.\n";
        outputGCDistributionStream.open(outputGCDistribution.c_str(), ios_base::app);
        outputGCDistributionStream << "\n\nChipBackground\n";
        break;
    }
    outputGCDistributionStream << "start\tend\tGCcontent\tGCfrequency\n";

    //read the .fasta to get frequencies of GC-content:
    vector<double> GCFreqs(fragmentLength+1, 0);
    char nucleotid;
	int countNucleotide = 0;
	int countGC = 0;
	int countN = 0;
	int position = 0;
	int observedGC = -1;
	int chrNum = 0;
	int positionCopyNumber;
    string fragmentNucleotides = "";
    string line;

    ifstream genomeFileStream (genomeFile.c_str());
    if (!genomeFileStream.is_open()) {
        cerr << ".. Unable to open " + genomeFile + " for reading\n\n";
        exit (-1);
    }
    else {
	    cout << ".. Reading "<< genomeFile << "\n";
        genomeFileStream >> nucleotid;
	    if (nucleotid == '>') {
            getline(genomeFileStream, line);
            chrNum = 0;
	    }
        else {
            countNucleotide = 1;
            countNucleotide = isGC(nucleotid);
            countN = isN(nucleotid);
            fragmentNucleotides.push_back(nucleotid);
        }
        while ((!genomeFileStream.eof()) && (countNucleotide < fragmentLength)) {
				genomeFileStream >> nucleotid;
				countGC += isGC(nucleotid);
				countN += isN(nucleotid);
				countNucleotide ++;
                fragmentNucleotides.push_back(nucleotid);
        }
        position = fragmentLength; //read "fragmentLength" letters into "fragmentNucleotides"

        while (!genomeFileStream.eof()) {
            positionCopyNumber = getCopyNumber(CNVlist, chrNum, position-fragmentLength, ploidy, fragmentLength);
            observedGC = -1;
            if (countN == 0) {
                observedGC = countGC;
            } else if (countN < fragmentLength)
                observedGC = round(float(countGC) / (fragmentLength - countN) * fragmentLength);
            if (observedGC != -1)
                GCFreqs[observedGC] += positionCopyNumber;
            genomeFileStream >> nucleotid;
            if (nucleotid == '>') {
                getline(genomeFileStream, line);
                chrNum++;
                genomeFileStream >> nucleotid;
            }
            countGC += isGC(nucleotid);
            countN += isN(nucleotid);
            fragmentNucleotides.push_back(nucleotid);
            nucleotid = fragmentNucleotides[0];
            countGC -= isGC(nucleotid);
			countN -= isN(nucleotid);
            fragmentNucleotides = fragmentNucleotides.substr(1);
            position++;
        }
    }
    genomeFileStream.close();

    long double totalSumGCFreqs = sum(GCFreqs);
    for (int i = 0; i <= fragmentLength; i++) {
        GCFreqs[i] /= totalSumGCFreqs;
    }


    //read GC-Distribution file
    ifstream GCdistributionStream(GCdistribution.c_str());
    std::vector<std::string> strs;
    vector <double> GCdist;
    GCentry entry;
    double GCfreq;
    if (!GCdistributionStream.is_open()) {
        cerr << ".. Unable to open " + GCdistribution + " for reading\n\n";
        exit (-1);
    } else {
	    cout << ".. Reading "<< GCdistribution << "\n";
		while (!GCdistributionStream.eof())	{
			getline (GCdistributionStream,line);
			if (! line.length()) continue;
            strs = split(line, '\t');
            entry.start = atof(strs[0].c_str());
            entry.end = atof(strs[1].c_str());
            entry.GCcontent = atof(strs[2].c_str());
            GCfreq = 0;
            for (int i = round(entry.start * fragmentLength); i < round(entry.end * fragmentLength); i++) {
                GCfreq += GCFreqs[i];
            }
            entry.GCfrequency = GCfreq;
            GClist.push_back(entry);
            GCdist.push_back(entry.GCfrequency * entry.GCcontent);
		}
    }
    strs.clear();
    GCdistributionStream.close();

    double correctionConstant = averageReadsPerPosition / sum(GCdist);
    for(std::vector<GCentry>::iterator it = GClist.begin(); it != GClist.end(); ++it) {
        (*it).GCcontent *= correctionConstant;
        outputGCDistributionStream << (*it).start << "\t" << (*it).end << "\t" << (*it).GCcontent << "\t" << (*it).GCfrequency << "\n";
    }
    outputGCDistributionStream.close();
 }


vector<GCentry> GCDistribution::getGClist() {
    return GClist;
}






