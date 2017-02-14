#include "SimulateReads.h"

using namespace std ;

SimulateReads::SimulateReads(std::string const& genomeFile, int readLength, int ploidy, int fragmentLength, vector<ERRORRATEentry> ERRORRATElist,  std::vector<std::vector<CNVentry> > CNVlist, vector<GCentry> GClist, Signal signalRegions, std::string const&  outputFile, sequanceType seqType) {
    //open file to write reads
    std::ofstream outputstream;
    switch (seqType) {
    case Input:
        outputstream.open(outputFile.c_str());
        cout << "\n\n.. Start generating reads for Input and write them to "<< outputFile <<"\n";
        break;
    case ChipSignal:
        outputstream.open(outputFile.c_str());
        cout << "\n\n.. Start generating reads for Chip signals and write them to "<< outputFile <<"\n";
        break;
    case ChipBackground:
        outputstream.open(outputFile.c_str(), ios_base::app);
        cout << "\n\n.. Start generating reads for Chip background and write them to "<< outputFile <<"\n";
        break;
    }

    //open chromosome file to read the sequance
    ifstream genomeFileStream (genomeFile.c_str());
    char nucleotid;
	int countNucleotide = 0;
	int countGC = 0;
	int countN = 0;
	int position = 0;
	int observedGC = -1;
	int readID = 1;
	int chrNum = 0;
	int positionCopyNumber;
	double GCrand;
	double randomStrand;
    string fragmentNucleotides = "";
    string line;

    //start generating reads
    if (!genomeFileStream.is_open()) {
        cerr << "Unable to open " + genomeFile + " for reading\n\n";
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
            countGC = isGC(nucleotid);
            countN = isN(nucleotid);
            fragmentNucleotides.push_back(nucleotid);
        }
        while((!genomeFileStream.eof()) && (countNucleotide < fragmentLength)) {
            genomeFileStream >> nucleotid;
            countGC += isGC(nucleotid);
            countN += isN(nucleotid);
            countNucleotide++;
            fragmentNucleotides.push_back(nucleotid);
        }
        position = fragmentLength; //read "fragmentLength" nucleotids into "fragmentNucleotides"

        while(!genomeFileStream.eof()) {
            if (fragmentLength - countN > fragmentLength * 0.80) { //less than 80% of NNN
                observedGC = -1;
                if (countN == 0) {
                    observedGC = countGC;
                } else if (countN < fragmentLength) {
                    observedGC = round(float(countGC) / (fragmentLength - countN) * fragmentLength);
                }
                if (observedGC != -1) {
                    positionCopyNumber = getCopyNumber(CNVlist, chrNum, position-fragmentLength, ploidy, fragmentLength);
                    for (int cn = 0; cn < positionCopyNumber; cn++) {
                        GCrand = random() * 1./ RAND_MAX;
                       // if (checkGC(GCrand, observedGC/fragmentLength, GClist)) {
                            randomStrand = round(random() * 1./ RAND_MAX);
                            Read read (readLength);
                            if (randomStrand) {
                                read.setSequence(fragmentNucleotides.substr(fragmentLength-readLength));
                                read.replaceN();
                                read.complement();
                                read.addErrors(ERRORRATElist);
                                read.print(outputstream, position-readLength+1, readID);
                            } else { //generate normal read
                                read.setSequence(fragmentNucleotides.substr(0,readLength));
                                read.replaceN();
                                read.addErrors(ERRORRATElist);
                                read.print(outputstream, position-fragmentLength+1, readID);
                            }
                            readID++;
                      //  }
                    }
                }
            }
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
    outputstream.close();
    cout << "Created " << readID - 1 << " reads\n";
}


bool SimulateReads::checkGC(double GCrand, double GCpercent, vector<GCentry> GClist) {
    for(vector<GCentry>::iterator it = GClist.begin(); it != GClist.end(); ++it) {
        if ((*it).start <= GCpercent && GCpercent < (*it).end) {
            if (GCrand <= (*it).GCcontent)
                return 1;
            else
                return 0;
        }
    }
    return 0;
}

