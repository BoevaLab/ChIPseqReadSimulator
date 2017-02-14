#pragma once
#ifndef __READ_H__
#define __READ_H__

#include <string>
#include <vector>

#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "math.h"
#include "types.h"


class Read {

  public:
  Read(int readLength);
  void setSequence(std::string seq);
  void complement();
  void replaceN();
  void addErrors (std::vector<ERRORRATEentry> ERRORRATElist);
  void print(std::ofstream & outstream, int position, int ID);
  private:
  std::string SEQUENCElist;
  std::string QUALITYlist;
  int readLen;
};


#endif
