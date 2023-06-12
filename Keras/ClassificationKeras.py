#!/usr/bin/env python
## \file
## \ingroup tutorial_tmva_keras
## \notebook -nodraw
## This tutorial shows how to do classification in TMVA with neural networks
## trained with keras.
##
## \macro_code
##
## \date 2017
## \author TMVA Team

from ROOT import TMVA, TFile, TTree, TCut
from subprocess import call
from os.path import isfile

from keras.models import Sequential
from keras.layers import Dense, Activation
from keras.optimizers import Adam
from keras import backend as K

# Setup TMVA
TMVA.Tools.Instance()
TMVA.PyMethodBase.PyInitialize()

outputFileName = 'TMVA_Keras_v3.root'
output = TFile.Open(outputFileName, 'RECREATE')
factory = TMVA.Factory('TMVAClassification', output,
                       '!V:!Silent:Color:DrawProgressBar:Transformations=D,G:AnalysisType=Classification')

# Load data
data = TFile.Open('../HistoResult/Test-v11/Test-v11_BDTTree_FNano2017-v7_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8.root')
signal = data.Get('Tree_Right')
background = data.Get('Tree_Wrong')

dataloader = TMVA.DataLoader('dataset')
#for branch in signal.GetListOfBranches():
#    print(type(branch.GetName()))
#    dataloader.AddVariable(branch.GetName())

dataloader.AddVariable('j_Deep')
dataloader.AddVariable('DR_lj')
dataloader.AddVariable('Deta_lj')
dataloader.AddVariable('DpT_metj')
dataloader.AddVariable('DPhi_lj')
dataloader.AddVariable("Deta_lmet")
#dataloader.AddVariable("Dphi_lmet")
dataloader.AddVariable("DpT_lj")
dataloader.AddVariable("DR_metj")
dataloader.AddVariable("DPhi_metj")
#dataloader.AddVariable("W_mT")

dataloader.AddSignalTree(signal, 1.0)
dataloader.AddBackgroundTree(background, 1.0)
#dataloader.PrepareTrainingAndTestTree(TCut(''),
#                                      'nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V')

#Set individual event weights (the variables must exist in the original TTree)
dataloader.SetSignalWeightExpression( "W_evt" )
dataloader.SetBackgroundWeightExpression( "W_evt" )

dataloader.PrepareTrainingAndTestTree(TCut(''), "SplitMode=random:!V" )

# Generate model
#K.clear_session()
# Define model
model = Sequential()

model.add(Dense(128,  activation='relu', input_dim=9))
model.add(Dense(128, activation='relu'))
model.add(Dense(128, activation='relu'))
model.add(Dense(2, activation='softmax'))

# Set loss and optimizer
model.compile(loss='categorical_crossentropy', optimizer=Adam(lr=0.01), metrics=['accuracy'])

# Store model to file
model.save('modelClassification_v2.h5')
model.summary()

# Book methods
#factory.BookMethod(dataloader, TMVA.Types.kFisher, 'Fisher',
#                   '!H:!V:Fisher:VarTransform=D,G')
factory.BookMethod(dataloader, TMVA.Types.kPyKeras, 'PyKeras',
                    'H:!V:VarTransform=D,G:FilenameModel=modelClassification_v2.h5:'+\
                    'NumEpochs=100:BatchSize=256:'+\
                    'TriesEarlyStopping=10')

# Run training, test and evaluation
factory.TrainAllMethods()
factory.TestAllMethods()
factory.EvaluateAllMethods()

#if ( !(gROOT.IsBatch()) ):
#TMVA.TMVAGui(outputFileName)
