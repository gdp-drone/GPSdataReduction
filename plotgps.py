import numpy as np
import matplotlib.pyplot as plt


with open('localizedS1.txt') as f:
    array = np.array([[float(x) for x in line.split()] for line in f])
array = np.hsplit(array,3)
arLong = array[0].reshape(1,-1)[0]
arLati = array[1].reshape(1,-1)[0]

plt.plot(arLong,arLati,'ro')
plt.show()
