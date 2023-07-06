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
import time

from os import environ
environ['KERAS_BACKEND'] = 'theano'

# Set architecture of system (AVX instruction set is not supported on SWAN)
environ['THEANO_FLAGS'] = 'gcc.cxxflags=-march=corei7'
 
from ROOT import TMVA, TFile, TTree, TCut
from subprocess import call
from os.path import isfile



import tensorflow.keras
from keras.utils import np_utils
import tensorflow.keras.callbacks as cb
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout, Activation
from tensorflow.keras import regularizers
from tensorflow.keras import backend as K
from tensorflow.keras import optimizers
from tensorflow.keras import callbacks
from tensorflow.keras.constraints import max_norm
 

isW=False


# Setup TMVA
TMVA.Tools.Instance()
TMVA.PyMethodBase.PyInitialize()
if isW: output = TFile.Open('TMVA_WpairJets.root', 'RECREATE')
else: output = TFile.Open('TMVA_ToppairJets.root', 'RECREATE')
factory = TMVA.Factory('TMVAClassification', output,
                       '!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification')
 
# Load data
#if not isfile('tmva_class_example.root'):
#    call(['curl', '-L', '-O', 'http://root.cern.ch/files/tmva_class_example.root'])
 
data = TFile.Open('SgnBkgTrees/SgnBckTree_UNICANttCatGenInfo-v1_FullSelStep_FNano2017-v7_ttCat_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8.root')
signal = data.Get('SgnPairTree')
if isW: background = data.Get('BckWPairTree')
else: background = data.Get('BckTopPairTree')

n_sgn_train = int(signal.GetEntries()/2)
n_bck_train = int(background.GetEntries()/2)

 
dataloader = TMVA.DataLoader('dataset')
for branch in signal.GetListOfBranches():
    dataloader.AddVariable(branch.GetName())
 
dataloader.AddSignalTree(signal, 1.0)
dataloader.AddBackgroundTree(background, 1.0)
dataloader.PrepareTrainingAndTestTree(TCut(''),
                                      'nTrain_Signal='+str(n_sgn_train)+':nTrain_Background='+str(n_bck_train)+':SplitMode=Random:!V')#NormMode=NumEvents:!V')
 
# Generate model
 
# Define model
model = Sequential()

model.add(Dense(70, kernel_initializer='glorot_normal', activation='relu', input_dim=6))
model.add(Dropout(0.2))
model.add(Dense(50, kernel_initializer='glorot_normal', activation='relu', kernel_constraint=max_norm(1.)))
model.add(Dropout(0.2))
model.add(Dense(30, kernel_initializer='glorot_normal', activation='relu', kernel_constraint=max_norm(1.)))
model.add(Dropout(0.2))
model.add(Dense(30, kernel_initializer='glorot_normal', activation='relu', kernel_constraint=max_norm(1.)))
model.add(Dropout(0.1))
model.add(Dense(20, kernel_initializer='glorot_normal', activation='relu', kernel_constraint=max_norm(1.)))
model.add(Dropout(0.1))
model.add(Dense(10, kernel_initializer='glorot_normal', activation='relu', kernel_constraint=max_norm(1.)))

model.add(Dense(2, kernel_initializer='glorot_normal', activation='sigmoid'))


# Set loss and optimizer
model.compile(loss='binary_crossentropy', optimizer=optimizers.RMSprop(0.001, decay=0.001/60), metrics=['accuracy'])


print('Model compiled')


print('Training model...')

n_epochs = 500
n_batch = 512

start_time = time.time()

 
# Store model to file
if isW: model.save('model_W.h5')
else: model.save('model_Top.h5')
model.summary()
 
# Book methods
#factory.BookMethod(dataloader, TMVA.Types.kFisher, 'Fisher',
#                   '!H:!V:Fisher:VarTransform=D,G')
if isW: factory.BookMethod(dataloader, TMVA.Types.kPyKeras, 'PyKeras', 'H:!V:VarTransform=D,G:FilenameModel=model_W.h5:NumEpochs='+str(n_epochs)+':BatchSize='+str(n_batch)+':verbose=2')
else: factory.BookMethod(dataloader, TMVA.Types.kPyKeras, 'PyKeras', 'H:!V:VarTransform=D,G:FilenameModel=model_Top.h5:NumEpochs='+str(n_epochs)+':BatchSize='+str(n_batch)+':verbose=2')

# Run training, test and evaluation
factory.TrainAllMethods()
factory.TestAllMethods()
factory.EvaluateAllMethods()

#Save header for c++ KerasReader
if isW:


	with open('generated_code_new_quad_Bos.h', 'w') as f:


	    print ("""
	    // Select all (Ctrl+A), Copy (Ctrl+C), paste to an empty text file (Ctrl+V) and save that file as 'generated_code.h'
	    // 
	    // Auto-generated header file. Assumes img to be a floating point array
	    // of 64 elements (corresponding to an 8x8 b&w image)
	    #include <math.h>
	    float norma_Bos;
	    """, file=f)

	    iLayer_tmp=-1

	    for iLayer, layer in enumerate(model.layers):
	      if type(layer) is not Dropout:
        	kernel, bias = layer.get_weights()
        	iLayer_tmp+=1
        	print ("inline float Bos_activation_%d (float x, float n) " % iLayer_tmp, file=f);
        	activation =  layer.get_config()['activation'] 
        	if activation == 'sigmoid':
        	  print ("{ return 1./(1 + exp(-x)); }", file=f)
        	elif activation == 'tanh':
        	  print ("{ return tanh(x);}")
        	elif activation == 'relu':
        	  print ("{ return x > 0 ? x : 0;}", file=f)
        	elif activation == 'linear':
        	  print ("{ return x;}", file=f)
        	elif activation == 'softmax':
        	  print ("{ return exp(x)/n;  }", file=f)
        	else:
        	  raise KeyError ("Unexpected activation %s"%activation)

	    iLayer_tmp=-1


	    print ("""
	    float guess_digit_Bos (const float *img, int flag)
	    {
	    """, file=f)

	    max_out = 100
	    for iLayer, layer in enumerate(model.layers):
	      if type(layer) is not Dropout:
        	iLayer_tmp+=1
        	print ("  // Declare the arrays in the stack", file=f)
        	kernel, bias = layer.get_weights()

        	max_out = max(kernel.shape[1], max_out)
        	#print ("  //",bias.shape)
        	kernel_values = "{%s}"%(',\n   '.join(["{%s}"%(','.join(["%18.13f"%x for x in row])) for row in kernel]))
        	bias_values   = "{%s}"% ( ",".join(["%18.13f"%x for x in bias]))
        	print ("  const float kernel_%d[%d][%d] = \n  %s;" % (iLayer_tmp, kernel.shape[0], kernel.shape[1],kernel_values), file=f)
        	print ("  const float bias_%d[%d] = %s;" % (iLayer_tmp, bias.shape[0], bias_values), file=f)

	    print ("  float buffer_in[%d];" % max_out, file=f)
	    print ("  float buffer_out[%d];" % max_out, file=f)

	    print ("  unsigned int i,j,c; ", file=f)

	    print ("\n\n\n", file=f)
	    print ("  // Load the input in the buffer", file=f)
	    print ("  for (c = 0; c < 64; ++c) \n  buffer_in[c] = img[c];", file=f)



	    iLayer_tmp=-1

	    for iLayer, layer in enumerate(model.layers):
	      if type(layer) is not Dropout: 
        	kernel, bias = layer.get_weights()
        	iLayer_tmp+=1

        	print ( "  // Processing layer %i " % iLayer_tmp , file=f)
        	print ( """
        	for (c = 0; c < {n_out}; ++c ) 
        	  buffer_out[c] = bias_{iLayer_tmp}[c];

        	for (c = 0; c < {n_out}; ++c )
        	  for (i = 0; i < {n_in}; ++i)
        	    buffer_out[c] += buffer_in[i] * kernel_{iLayer_tmp}[i][c];

        	norma_Bos = 0;

        	for(c=0;c<4;++c)
        	  norma_Bos+=exp(buffer_out[c]);
        	// Prepares for next layer 
        	for (c = 0; c < {n_out}; ++c )
        	  buffer_in[c] = Bos_activation_{iLayer_tmp}(buffer_out[c], norma_Bos);

        	""".format (
        	    n_in = kernel.shape[0],
        	    n_out = kernel.shape[1],
        	    iLayer_tmp = iLayer_tmp,
        	), file=f)

	    last_kernel, last_bias = model.layers[-1].get_weights()
	    print ("""
	      //i = 0;
	      //for (c = 0; c < {n_out}; ++c)
	      //  if (buffer_in[c] > buffer_in[i])
	      //    i = c;

	      if (flag==0)
        	return buffer_in[0];
	      else if (flag==1)
        	return buffer_in[1];
	      else if (flag==2)
        	return buffer_in[2];
	      else if (flag==3)
        	return buffer_in[3];

	      //return i;
	    """.format(n_out = last_kernel.shape[1]), file=f)

	    print ("}", file=f)
	    
else:

	with open('generated_code_new_quad_Top.h', 'w') as f:


	    print ("""
	    // Select all (Ctrl+A), Copy (Ctrl+C), paste to an empty text file (Ctrl+V) and save that file as 'generated_code.h'
	    // 
	    // Auto-generated header file. Assumes img to be a floating point array
	    // of 64 elements (corresponding to an 8x8 b&w image)
	    #include <math.h>
	    float norma_Top;
	    """, file=f)

	    iLayer_tmp=-1

	    for iLayer, layer in enumerate(model.layers):
	      if type(layer) is not Dropout:
        	kernel, bias = layer.get_weights()
        	iLayer_tmp+=1
        	print ("inline float Top_activation_%d (float x, float n) " % iLayer_tmp, file=f);
        	activation =  layer.get_config()['activation'] 
        	if activation == 'sigmoid':
        	  print ("{ return 1./(1 + exp(-x)); }", file=f)
        	elif activation == 'tanh':
        	  print ("{ return tanh(x);}")
        	elif activation == 'relu':
        	  print ("{ return x > 0 ? x : 0;}", file=f)
        	elif activation == 'linear':
        	  print ("{ return x;}", file=f)
        	elif activation == 'softmax':
        	  print ("{ return exp(x)/n;  }", file=f)
        	else:
        	  raise KeyError ("Unexpected activation %s"%activation)

	    iLayer_tmp=-1


	    print ("""
	    float guess_digit_Top (const float *img, int flag)
	    {
	    """, file=f)

	    max_out = 100
	    for iLayer, layer in enumerate(model.layers):
	      if type(layer) is not Dropout:
        	iLayer_tmp+=1
        	print ("  // Declare the arrays in the stack", file=f)
        	kernel, bias = layer.get_weights()

        	max_out = max(kernel.shape[1], max_out)
        	#print ("  //",bias.shape)
        	kernel_values = "{%s}"%(',\n   '.join(["{%s}"%(','.join(["%18.13f"%x for x in row])) for row in kernel]))
        	bias_values   = "{%s}"% ( ",".join(["%18.13f"%x for x in bias]))
        	print ("  const float kernel_%d[%d][%d] = \n  %s;" % (iLayer_tmp, kernel.shape[0], kernel.shape[1],kernel_values), file=f)
        	print ("  const float bias_%d[%d] = %s;" % (iLayer_tmp, bias.shape[0], bias_values), file=f)

	    print ("  float buffer_in[%d];" % max_out, file=f)
	    print ("  float buffer_out[%d];" % max_out, file=f)

	    print ("  unsigned int i,j,c; ", file=f)

	    print ("\n\n\n", file=f)
	    print ("  // Load the input in the buffer", file=f)
	    print ("  for (c = 0; c < 64; ++c) \n  buffer_in[c] = img[c];", file=f)



	    iLayer_tmp=-1

	    for iLayer, layer in enumerate(model.layers):
	      if type(layer) is not Dropout: 
        	kernel, bias = layer.get_weights()
        	iLayer_tmp+=1

        	print ( "  // Processing layer %i " % iLayer_tmp , file=f)
        	print ( """
        	for (c = 0; c < {n_out}; ++c ) 
        	  buffer_out[c] = bias_{iLayer_tmp}[c];

        	for (c = 0; c < {n_out}; ++c )
        	  for (i = 0; i < {n_in}; ++i)
        	    buffer_out[c] += buffer_in[i] * kernel_{iLayer_tmp}[i][c];

        	norma_Top = 0;

        	for(c=0;c<4;++c)
        	  norma_Top+=exp(buffer_out[c]);
        	// Prepares for next layer 
        	for (c = 0; c < {n_out}; ++c )
        	  buffer_in[c] = Top_activation_{iLayer_tmp}(buffer_out[c], norma_Top);

        	""".format (
        	    n_in = kernel.shape[0],
        	    n_out = kernel.shape[1],
        	    iLayer_tmp = iLayer_tmp,
        	), file=f)

	    last_kernel, last_bias = model.layers[-1].get_weights()
	    print ("""
	      //i = 0;
	      //for (c = 0; c < {n_out}; ++c)
	      //  if (buffer_in[c] > buffer_in[i])
	      //    i = c;

	      if (flag==0)
        	return buffer_in[0];
	      else if (flag==1)
        	return buffer_in[1];
	      else if (flag==2)
        	return buffer_in[2];
	      else if (flag==3)
        	return buffer_in[3];

	      //return i;
	    """.format(n_out = last_kernel.shape[1]), file=f)

	    print ("}", file=f)
