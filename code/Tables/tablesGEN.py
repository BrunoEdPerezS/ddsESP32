import numpy as np
import matplotlib.pyplot as plt
import math

#Generador de wavetables 


#Square wave*******************************************

#Valores para la onda------------------------
samples =256
max = 255
duty = 0.5
#Calculo-------------------------------------
high = int(samples*0.5)
down = int(samples - high)
dwn = np.zeros(down,dtype=int)
hgh = np.ones(high,dtype=int)*max
SQUARE = np.concatenate((dwn,hgh))
hexSQUARE = np.array2string(SQUARE, formatter={'int':lambda x: hex(x)},separator=', ')

#WaveCheck
#print("Size = ", np.size(SQUARE),end = '\n')
#print("Max  = ", np.max(SQUARE),  end = '\n')
#print("Min  = ", np.min(SQUARE),  end = '\n')
#plt.plot(SQUARE)
#plt.show()

#Saw wave***********************************************
samples =256
max = 255
SAW = np.linspace(0,255,samples,dtype=int)
hexSAW = np.array2string(SAW, formatter={'int':lambda x: hex(x)},separator=', ')

#WaveCheck
#print("Size = ", np.size(SAW),end = '\n')
#print("Max  = ", np.max(SAW),  end = '\n')
#print("Min  = ", np.min(SAW),  end = '\n')
#plt.plot(SAW)
#plt.show()

#Triangle wave***********************************************
samples =256
max = 255

halfSamples = int(samples/2)
half1 = np.linspace(0,max,halfSamples,dtype=int)
half2 = np.flip(half1)
#print(half2, np.size(half1), np.size(half2))
TRIANGLE = np.concatenate((half1,half2))
hexTRIANGLE = np.array2string(TRIANGLE, formatter={'int':lambda x: hex(x)},separator=', ')
#WaveCheck
#print("Size = ", np.size(TRIANGLE),end = '\n')
#print("Max  = ", np.max(TRIANGLE),  end = '\n')
#print("Min  = ", np.min(TRIANGLE),  end = '\n')
#plt.plot(TRIANGLE)
#plt.show()

#Sine wave***********************************************
samples =256
max = 255

steps = np.linspace(0,360,samples,dtype=int)
values = np.linspace(0,255,samples,dtype=int)
SINE = np.zeros(samples,dtype=int)
for i in range(samples):
    SINE[i] = int(((math.sin(math.radians(steps[i])))*(255/2))+127)
SINE.astype(int)
hexSINE = np.array2string(SINE, formatter={'int':lambda x: hex(x)},separator=', ')

#WaveCheck
#print("Size = ", np.size(SINE),end = '\n')
#print("Max  = ", np.max(SINE),  end = '\n')
#print("Min  = ", np.min(SINE),  end = '\n')
#plt.plot(SINE)
#plt.show()


#Seleccionar tipo de onda (SAW-TRIANGLE-SINE-SQUARE)
#sintaxis ejemplo ->print(hexSINE)

wave = SAW
print("Size = ", np.size(wave),end = '\n')
print("Max  = ", np.max(wave),  end = '\n')
print("Min  = ", np.min(wave),  end = '\n')
plt.plot(wave)
plt.show()
hexWAVE = np.array2string(wave, formatter={'int':lambda x: hex(x)},separator=', ')
print(hexWAVE)