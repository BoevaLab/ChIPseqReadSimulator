#include "Read.h"

using namespace std ;

 Read::Read(int readLength) {
    for (int i = 0; i < readLength; i++)
        QUALITYlist.push_back('I');
    readLen = readLength;
 }


void Read::setSequence(std::string seq) {
    SEQUENCElist = seq;
}


void Read::complement() {
    string comp;
    for (int i = 0; i < readLen; i++) {
        char letter = SEQUENCElist[readLen-i-1];
        switch (letter) {
        case 'A':
            letter = 'T';
            break;
        case 'T':
            letter = 'A';
            break;
        case 'C':
            letter = 'G';
            break;
        case 'G':
            letter = 'C';
            break;
        }
        comp.push_back(letter);
    }
    SEQUENCElist = comp;
}


 void Read::replaceN() {
    for (int i = 0; i < readLen; i++) {
        SEQUENCElist[i] = toupper(SEQUENCElist[i]);
        if (SEQUENCElist[i] == 'N') {
            double randomL = random() * 1. / RAND_MAX;
            if (randomL < 0.28) {
                SEQUENCElist[i] = 'A';
            } else if (randomL < 0.5) {
                SEQUENCElist[i] = 'C';
            } else if (randomL < 0.72) {
                SEQUENCElist[i] = 'G';
            } else
                SEQUENCElist[i] = 'T';
        }
    }
 }


void Read::addErrors (std::vector<ERRORRATEentry> ERRORRATElist) {
    for (int i = 0; i < readLen; i++) {
        double randomL = random()*1./RAND_MAX;
        if (randomL < ERRORRATElist[i].error*4./3) {
            randomL = random()*1./RAND_MAX;
                if (randomL<0.25) {
                    SEQUENCElist[i] = 'A';
                } else if (randomL<0.5) {
                    SEQUENCElist[i] = 'C';
                } else if (randomL<0.75) {
                    SEQUENCElist[i] = 'G';
                } else
                    SEQUENCElist[i] = 'T';
            QUALITYlist[i]='%';
        }
    }
}

void Read::print(ofstream & outstream, int position, int ID) {
    outstream << "@HWI-EAS209_XX:" << position << ":" << ID << "\n";
    outstream << SEQUENCElist << "\n";
    outstream << "+\n";
    outstream << QUALITYlist << "\n";
}
