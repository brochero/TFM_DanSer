#all: NanoTreeAnalyzer.exe NanoTreeAnalyzerForJEC.exe HistoCreator.exe NanoTreeAnalyzerDDForQCD.exe HistoQCDCreator.exe BDTNanoAnalyzer.exe BDTNanoValidation.exe
#all: NanoTreeAnalyzerForJEC.exe HistoCreator.exe NanoTreeAnalyzerDDForQCD.exe HistoQCDCreator.exe BDTNanoAnalyzer.exe BDTNanoValidation.exe
all: BDTNanoAnalyzer.exe BDTNanoValidation.exe
# -- NANOAODREADER
plugins/NanoAODReader.o: plugins/NanoAODReader.cc includes/NanoAODReader.h
	c++ -std=c++17 -static -I`root-config --incdir` -Iincludes -c plugins/NanoAODReader.cc -o plugins/NanoAODReader.o
# --++ NANOAODREADERForJEC
plugins/NanoAODReaderForJEC.o: plugins/NanoAODReaderForJEC.cc includes/NanoAODReader.h
	c++ -std=c++17 -static -I`root-config --incdir` -Iincludes -c plugins/NanoAODReaderForJEC.cc -o plugins/NanoAODReaderForJEC.o

# -- TOOLS
plugins/GetListOfFiles.o: plugins/GetListOfFiles.cc
	c++ -std=c++17 -static -I`root-config --incdir` -c plugins/GetListOfFiles.cc -o plugins/GetListOfFiles.o
plugins/SFLumi.o: plugins/SFLumi.cc
	c++ -std=c++17 -static -I`root-config --incdir` -c plugins/SFLumi.cc -o plugins/SFLumi.o
plugins/SFLepIDISOTr.o: plugins/SFLepIDISOTr.cc includes/NanoAnalyzer.h includes/ObjectsDef.h
	c++ -std=c++17 -static -I`root-config --incdir` -Iincludes -c plugins/SFLepIDISOTr.cc -o plugins/SFLepIDISOTr.o

# -- CREATE COLLECTIONS
plugins/CreateCollections.o: plugins/CreateCollections.cc includes/NanoAnalyzer.h includes/ObjectsDef.h
	c++ -std=c++17 -static -I`root-config --incdir` -Iincludes -c plugins/CreateCollections.cc -o plugins/CreateCollections.o

# -- LEPTONS
plugins/MuonSel.o: plugins/MuonSel.cc includes/NanoAnalyzer.h includes/ObjectsDef.h
	c++ -std=c++17 -static -I`root-config --incdir` -Iincludes -c plugins/MuonSel.cc -o plugins/MuonSel.o
plugins/ElectronSel.o: plugins/ElectronSel.cc includes/NanoAnalyzer.h includes/ObjectsDef.h
	c++ -std=c++17 -static -I`root-config --incdir` -Iincludes -c plugins/ElectronSel.cc -o plugins/ElectronSel.o

# -- JETS
# Jet selection
plugins/JetSel.o: plugins/JetSel.cc includes/NanoAnalyzer.h includes/ObjectsDef.h
	c++ -std=c++17 -static -I`root-config --incdir` -Iincludes -c plugins/JetSel.cc -o plugins/JetSel.o
# b-tagging SF (from CSV file)
plugins/BTagCalibrationStandalone.o: plugins/BTagCalibrationStandalone.cc includes/Corrections/btagSF/BTagCalibrationStandalone.h
	c++ -std=c++17 -static -I`root-config --incdir` -Iincludes/ -c plugins/BTagCalibrationStandalone.cc -o plugins/BTagCalibrationStandalone.o
plugins/JetbtagCSVSF.o: plugins/JetbtagCSVSF.cc includes/NanoAnalyzer.h includes/ObjectsDef.h
	c++ -std=c++17 -static -I`root-config --incdir` -Iincludes -c plugins/JetbtagCSVSF.cc -o plugins/JetbtagCSVSF.o

# ---------------------------------------------------------
# ---------------------------------------------------------
# ---------------------------------------------------------

# TTree producer (central)
# NanoTreeAnalyzer.exe: NanoTreeAnalyzer.cc includes/NanoAODReader.h includes/NanoAnalyzer.h includes/ObjectsDef.h plugins/NanoAODReader.o plugins/GetListOfFiles.o plugins/SFLumi.o plugins/SFLepIDISOTr.o plugins/CreateCollections.o plugins/MuonSel.o plugins/ElectronSel.o plugins/JetSel.o plugins/BTagCalibrationStandalone.o plugins/JetbtagCSVSF.o
# 	c++ -std=c++17 -o NanoTreeAnalyzer.exe NanoTreeAnalyzer.cc plugins/NanoAODReader.o \
# 	plugins/GetListOfFiles.o plugins/SFLumi.o plugins/SFLepIDISOTr.o \
# 	plugins/CreateCollections.o \
# 	plugins/MuonSel.o plugins/ElectronSel.o plugins/JetSel.o \
# 	plugins/BTagCalibrationStandalone.o plugins/JetbtagCSVSF.o \
# 	`root-config --libs --cflags` -I`root-config --incdir` -Wl,-rpath ${ROOTSYS}/lib -lMathCore -lMinuit -lGenVector -Iincludes

# Histograms (central)
HistoCreator.exe: HistoCreator.cc includes/Corrections/MET/XYMETCorrection.h
	c++ -std=c++17 -o HistoCreator.exe HistoCreator.cc \
	`root-config --libs --cflags` -I`root-config --incdir` -Wl,-rpath ${ROOTSYS}/lib -lMathCore -lMinuit -lGenVector -lTMVA -Iincludes

# TTree producer (for JEC)
NanoTreeAnalyzerForJEC.exe: NanoTreeAnalyzerForJEC.cc includes/NanoAODReader.h includes/NanoAnalyzer.h includes/ObjectsDef.h plugins/NanoAODReaderForJEC.o plugins/GetListOfFiles.o plugins/SFLumi.o plugins/SFLepIDISOTr.o plugins/CreateCollections.o plugins/MuonSel.o plugins/ElectronSel.o plugins/JetSel.o plugins/BTagCalibrationStandalone.o plugins/JetbtagCSVSF.o
	c++ -std=c++17 -o NanoTreeAnalyzerForJEC.exe NanoTreeAnalyzerForJEC.cc plugins/NanoAODReaderForJEC.o \
	plugins/GetListOfFiles.o plugins/SFLumi.o plugins/SFLepIDISOTr.o \
	plugins/CreateCollections.o \
	plugins/MuonSel.o plugins/ElectronSel.o plugins/JetSel.o \
	plugins/BTagCalibrationStandalone.o plugins/JetbtagCSVSF.o \
	`root-config --libs --cflags` -I`root-config --incdir` -Wl,-rpath ${ROOTSYS}/lib -lMathCore -lMinuit -lGenVector -Iincludes -lTMVA

# TTree producer (DD for QCD)
NanoTreeAnalyzerDDForQCD.exe: NanoTreeAnalyzerDDForQCD.cc includes/NanoAODReader.h includes/NanoAnalyzer.h includes/ObjectsDef.h plugins/NanoAODReader.o plugins/GetListOfFiles.o plugins/SFLumi.o plugins/SFLepIDISOTr.o plugins/CreateCollections.o plugins/MuonSel.o plugins/ElectronSel.o plugins/JetSel.o plugins/BTagCalibrationStandalone.o plugins/JetbtagCSVSF.o
	c++ -std=c++17 -o NanoTreeAnalyzerDDForQCD.exe NanoTreeAnalyzerDDForQCD.cc plugins/NanoAODReader.o \
	plugins/GetListOfFiles.o plugins/SFLumi.o plugins/SFLepIDISOTr.o \
	plugins/CreateCollections.o \
	plugins/MuonSel.o plugins/ElectronSel.o plugins/JetSel.o \
	plugins/BTagCalibrationStandalone.o plugins/JetbtagCSVSF.o \
	`root-config --libs --cflags` -I`root-config --incdir` -Wl,-rpath ${ROOTSYS}/lib -lMathCore -lMinuit -lGenVector -Iincludes

# Histograms (DD for QCD)
HistoQCDCreator.exe: HistoQCDCreator.cc includes/Corrections/MET/XYMETCorrection.h
	c++ -std=c++17 -o HistoQCDCreator.exe HistoQCDCreator.cc \
	`root-config --libs --cflags` -I`root-config --incdir` -Wl,-rpath ${ROOTSYS}/lib -lMathCore -lMinuit -lGenVector -Iincludes -lTMVA

# Trees for BDT Trainning
BDTNanoAnalyzer.exe: BDTNanoAnalyzer.cc includes/NanoAODReader.h includes/NanoAnalyzer.h includes/ObjectsDef.h plugins/NanoAODReader.o plugins/GetListOfFiles.o plugins/SFLumi.o plugins/SFLepIDISOTr.o plugins/CreateCollections.o plugins/MuonSel.o plugins/ElectronSel.o plugins/JetSel.o plugins/BTagCalibrationStandalone.o plugins/JetbtagCSVSF.o
	c++ -std=c++17 -o BDTNanoAnalyzer.exe BDTNanoAnalyzer.cc plugins/NanoAODReader.o \
	plugins/GetListOfFiles.o plugins/SFLumi.o plugins/SFLepIDISOTr.o \
	plugins/CreateCollections.o \
	plugins/MuonSel.o plugins/ElectronSel.o plugins/JetSel.o \
	plugins/BTagCalibrationStandalone.o plugins/JetbtagCSVSF.o \
	`root-config --libs --cflags` -I`root-config --incdir` -Wl,-rpath ${ROOTSYS}/lib -lMathCore -lMinuit -lGenVector -Iincludes

# BDT Performance 
BDTNanoValidation.exe: BDTNanoValidation.cc includes/NanoAODReader.h includes/NanoAnalyzer.h includes/ObjectsDef.h plugins/NanoAODReader.o plugins/GetListOfFiles.o plugins/SFLumi.o plugins/SFLepIDISOTr.o plugins/CreateCollections.o plugins/MuonSel.o plugins/ElectronSel.o plugins/JetSel.o plugins/BTagCalibrationStandalone.o plugins/JetbtagCSVSF.o
	c++ -std=c++17 -o BDTNanoValidation.exe BDTNanoValidation.cc plugins/NanoAODReader.o \
	plugins/GetListOfFiles.o plugins/SFLumi.o plugins/SFLepIDISOTr.o \
	plugins/CreateCollections.o \
	plugins/MuonSel.o plugins/ElectronSel.o plugins/JetSel.o \
	plugins/BTagCalibrationStandalone.o plugins/JetbtagCSVSF.o \
	`root-config --libs --cflags` -I`root-config --incdir` -Wl,-rpath ${ROOTSYS}/lib -lMathCore -lMinuit -lGenVector -Iincludes

# Studies at GEN level
NanoGenFracVal.exe: NanoGenFracVal.cc includes/NanoAODReader.h includes/NanoAnalyzer.h includes/ObjectsDef.h plugins/NanoAODReader.o plugins/GetListOfFiles.o 
	c++ -std=c++17 -o NanoGenFracVal.exe NanoGenFracVal.cc plugins/NanoAODReader.o \
	plugins/GetListOfFiles.o \
	`root-config --libs --cflags` -I`root-config --incdir` -Wl,-rpath ${ROOTSYS}/lib -lMathCore -lMinuit -lGenVector -Iincludes

clean:
	rm *.exe plugins/GetListOfFiles.o plugins/SFLumi.o plugins/SFLepIDISOTr.o plugins/CreateCollections.o plugins/MuonSel.o plugins/ElectronSel.o plugins/JetSel.o plugins/NanoAODReader.o plugins/NanoAODReaderForJEC.o plugins/BTagCalibrationStandalone.o plugins/JetbtagCSVSF.o

