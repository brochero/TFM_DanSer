#include <vector>
#include "TString.h"
#include <iostream>
#include <fstream>

std::vector<TString> GetListOfFiles(TString FileName, TString FromOutside){

  std::vector<TString> ListOfSamples;

  std::ifstream InFile;
  InFile.open(FileName);

  if (!InFile){
    std::cout << "File " << FileName << " not found!" << std::endl;
    std::exit(0);
  }
  else{
    std::string tmpLine;
    while (std::getline(InFile,tmpLine)){
      TString TxtLine = tmpLine;
      if (FromOutside == "ciemat") TxtLine = "root://gaexrdoor.ciemat.es/" + tmpLine;
      if (FromOutside == "cern")   TxtLine = "root://eoscms.cern.ch/" + tmpLine;      
      if (!TxtLine.Contains("#") && TxtLine.Contains(".root")) ListOfSamples.push_back(TxtLine);
    }// while
  }


  if (ListOfSamples.size() == 0){
    std::cout << "No input files found!" << std::endl;
    std::exit(0);
  }

  return ListOfSamples;
}

