#include "chipSimulation.h"

using namespace std ;

int main(int argc, char *argv[]) {

    freopen( "/home/ristretto/Elnaz/Valentina/project/ChIPseqReadSimulator/output/output.txt", "w", stdout );
    freopen( "/home/ristretto/Elnaz/Valentina/project/ChIPseqReadSimulator/output/error.txt", "w", stderr );
    cout << "Output message" << endl;
    cerr << "Error message" << endl;


	//check arguments
    cout << "Simulation of the ChIPseq-reads \n";
	if (argc < 3) {
		cerr << "\n\tPlease specify a config file\n\n";
		cerr << "chipSimulation -conf config.txt";
		return 0;
	}
	if (argc == 3) {
		if ((strcmp(argv[1], "-conf") != 0) && (strcmp(argv[1], "--conf") != 0)) {
            cerr << "chipSimulation -conf config.txt";
			return 0;
		}
	}
	//check if config file exists
    ifstream ifile(argv[2]);
    if (!ifile) {
      cerr << "\n\tCould not find your config file.. Please, check the existance of " << argv[2] <<"\n\n";
      return -1;
    }

	//read config file
	ConfigFile cf(argv[2]);

	//declaration of input variables
    int chromosomeLength;
    int ploidy;
    int nucleosomeDist;
    int fragmentLength;
    int readLength;
    int readNumber;
    float noiseLevel;

    string genomeFile;
    string genomeLengthFile;
    string inputGCDistribution;
    string chipGCDistribution;
    string copyNumberVariationFile;
    string peakSignalsFile;
    string errorRateFile;
    string outputChIPReads;
    string outputControlReads;
    string outputSignalRegions;
    string outputGCDistribution;

    //read the config file and assign the values of input variables
    try {
        ploidy = int(cf.Value("general","ploidy"));
        nucleosomeDist = int(cf.Value("general","nucleosomeDist"));
        fragmentLength = int(cf.Value("general","fragmentLength"));
        readLength = int(cf.Value("general","readLength"));
        readNumber = int(cf.Value("general","readNumber"));
        noiseLevel = float(cf.Value("general","noiseLevel"));

        genomeFile = std::string(cf.Value("general","genomeFile"));
        genomeLengthFile = std::string(cf.Value("general","genomeLengthFile"));
        inputGCDistribution = std::string(cf.Value("general","inputGCDistribution"));
        chipGCDistribution = std::string(cf.Value("general","chipGCDistribution"));
        copyNumberVariationFile = std::string(cf.Value("general","copyNumberVariationFile"));
        peakSignalsFile = std::string(cf.Value("general","peakSignalsFile"));
        errorRateFile = std::string(cf.Value("general","errorRateFile"));
        outputChIPReads = std::string(cf.Value("general","outputChIPReads"));
        outputControlReads = std::string(cf.Value("general","outputControlReads"));
        outputSignalRegions = std::string(cf.Value("general","outputSignalRegions"));
        outputGCDistribution = std::string(cf.Value("general","outputGCDistribution"));
    } catch (const char * error) {
		cerr << "Some parameteres are massing ...\n";
		return -1;
	}

    CopyNumberVariation cp(copyNumberVariationFile, ploidy, genomeLengthFile);
    std:vector<std::vector<CNVentry> > CNVlist = cp.getCNlist();
    long genomeLength = cp.getCNVgenomeLength();

    Peaks pk(peakSignalsFile);
    std::vector<std::vector<PEAKentry> > PEAKlist = pk.getPEAKlist();

    ErrorRate er(errorRateFile);
    vector<ERRORRATEentry> ERRORRATElist = er.getERRORRATElist();

    Signal signalRegions(nucleosomeDist, ploidy, fragmentLength, CNVlist, PEAKlist, outputSignalRegions);


    GCDistribution GCcountsInput(inputGCDistribution, outputGCDistribution, genomeFile, readNumber, ploidy, fragmentLength, noiseLevel, genomeLength, CNVlist, signalRegions, Input);
    GCDistribution GCcountsChIPSignal(chipGCDistribution, outputGCDistribution, genomeFile, readNumber, ploidy, fragmentLength, noiseLevel, genomeLength, CNVlist, signalRegions, ChipSignal);
    GCDistribution GCcountsChIPBackground(chipGCDistribution, outputGCDistribution, genomeFile, readNumber, ploidy, fragmentLength, noiseLevel, genomeLength, CNVlist, signalRegions, ChipBackground);

    SimulateReads simulateReadsInput(genomeFile, readLength, ploidy, fragmentLength, ERRORRATElist, CNVlist, GCcountsInput.getGClist(), signalRegions, outputControlReads, Input);
    SimulateReads simulateReadsChIPSignal(genomeFile, readLength, ploidy, fragmentLength, ERRORRATElist, CNVlist, GCcountsChIPSignal.getGClist(), signalRegions, outputChIPReads, ChipSignal);
    SimulateReads simulateReadsChIPBackground(genomeFile, readLength, ploidy, fragmentLength, ERRORRATElist, CNVlist, GCcountsChIPBackground.getGClist(), signalRegions, outputChIPReads, ChipBackground);

	return 0;
}
