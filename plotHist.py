import numpy as np
import matplotlib.pyplot as plt
import math

import sys

print 'Number of arguments:', len(sys.argv), 'arguments.'
print 'Argument List:', str(sys.argv)


with open('data/localized'+sys.argv[1]) as f:
    array = np.array([[float(x) for x in line.split()] for line in f])
array = np.hsplit(array,3)
arLong = array[0].reshape(1,-1)[0]
arLati = array[1].reshape(1,-1)[0]

arRad = np.sqrt(arLong*arLong+arLati*arLati)


plt.hist(arRad, bins=40)
plt.ylabel("Radius Distribution from mean")
plt.show()

"""
plt.plot(i,arRad,'ro')
plt.show()
"""