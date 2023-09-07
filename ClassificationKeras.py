#from os import environ
#environ['KERAS_BACKEND'] = 'tensorflow'

from ROOT import TMVA, TFile, TTree, TCut
from subprocess import call
from os.path import isfile

import tensorflow.keras

from tensorflow.keras.backend import *

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Activation
from tensorflow.keras.optimizers import SGD, Adam
from tensorflow.keras import initializers
from tensorflow.keras import regularizers

from tensorflow.keras import callbacks
from tensorflow.keras.constraints import max_norm


# Setup TMVA
TMVA.Tools.Instance()
TMVA.PyMethodBase.PyInitialize()
 
output = TFile.Open('TMVA_Classification_Keras.root', 'RECREATE')
factory = TMVA.Factory('TMVAClassification', output,
                       '!V:!Silent:Color:DrawProgressBar:Transformations=D,G:AnalysisType=Classification')
 
# Load data
input_file = 'HistoResult/FinalVbles/FinalVbles_BDTTree_FNano2017-v7_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8.root'
 
data = TFile.Open(input_file)
signal = data.Get('Tree_Right')
background = data.Get('Tree_Wrong')
 
dataloader = TMVA.DataLoader('dataset')

dataloader.AddVariable('j_Deep')
dataloader.AddVariable('DR_lj')
dataloader.AddVariable('Deta_lj')
dataloader.AddVariable('DpT_metj')
dataloader.AddVariable('DPhi_lj')
dataloader.AddVariable("Deta_lmet")
dataloader.AddVariable("DpT_lj")
dataloader.AddVariable("DR_metj")
dataloader.AddVariable("DPhi_metj")
 
dataloader.AddSpectator('region')
dataloader.AddSpectator( 'M_lj')
   
dataloader.AddSignalTree(signal, 1.0)
dataloader.AddBackgroundTree(background, 1.0)

dataloader.SetSignalWeightExpression( "W_evt" )
dataloader.SetBackgroundWeightExpression( "W_evt" )

dataloader.PrepareTrainingAndTestTree(TCut('region >= 6'),'SplitMode=random:!V' )
 
# Generate model
 
# Define model
model = Sequential()
model.add(Dense(128, kernel_initializer='glorot_normal',  activation='relu', input_dim=9))
model.add(Dense(128, kernel_initializer='glorot_normal', activation='relu'))
model.add(Dense(128, kernel_initializer='glorot_normal', activation='relu'))
model.add(Dense(2, kernel_initializer='glorot_normal', activation='softmax'))
 
# Set loss and optimizer
model.compile(loss='categorical_crossentropy', optimizer=Adam(learning_rate=0.01), weighted_metrics=['accuracy', ])
 
# Store model to file
model.save('modelClassification.h5')
model.summary()
 
# Book methods
factory.BookMethod(dataloader, TMVA.Types.kPyKeras, 'PyKeras', 'H:!V:VarTransform=D,G:'+\
                   'FilenameModel=modelClassification.h5:'+\
                   'NumEpochs=100:BatchSize=256:'+\
                   'TriesEarlyStopping=10:verbose=2:tf.keras=True')
 
# Run training, test and evaluation
factory.TrainAllMethods()
factory.TestAllMethods()
factory.EvaluateAllMethods()