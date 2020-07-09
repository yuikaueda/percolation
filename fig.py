import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import scipy.optimize


#df_cp = pd.read_table('percolation_cp.dat')

data = np.loadtxt('percolation_2cp40.dat', skiprows=1)

x = data[:,0]
y1 = data[:, 1]
y2 = data[:, 2]

#print(x)

fig, axe = plt.subplots(1, 1)
#axes[0].set_title('x-y1')
#axes[1].set_title('x-y2')

axe.plot(x, y1, 'o-', c='red', label = "cp_ver")
axe.plot(x, y2, 'o-', c='blue', label = "cp_hor")

plt.xlabel("f", fontsize = 15)
plt.ylabel("cp", fontsize = 15)
plt.legend(loc = 'upper right')
fig.savefig("cpp40_model2.png")
#plt.show()



