import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import scipy.optimize


data = np.loadtxt('percolation_2pp40.dat', skiprows=1)

x = data[:,0]
y = data[:,1]

fig, axe = plt.subplots(1, 1)

axe.plot(x, y, 'o-', c='black')

plt.xlabel("p", fontsize =15 )
plt.ylabel("pp", fontsize = 15)

fig.savefig("pp40_model2.png")
