import numpy as np
import matplotlib.pyplot as plt

ind, x, err = np.loadtxt('NR.txt', unpack=True)

plt.plot(err,marker='o',markersize=3)
plt.yscale('log')
plt.xlabel("Nombre d'iterations")
plt.ylabel("Erreur absolue")
plt.show()
