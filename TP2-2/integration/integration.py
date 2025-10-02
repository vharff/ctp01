import numpy as np
import matplotlib.pyplot as plt
exact = 8.04977183346942e-2
n, e1, e2, e3 = np.loadtxt('integration.txt', unpack=True)

plt.plot(n,np.abs(exact-e1),marker='o', markersize=3, label='rectangles')
plt.plot(n,np.abs(exact-e2),marker='o', markersize=3, label='trapezes')
plt.plot(n,np.abs(exact-e3),marker='o', markersize=3, label='simpson')

plt.xscale('log')
plt.yscale('log')
plt.legend()
plt.xlabel("Nombre d'intervalles")
plt.ylabel("Erreur relative")
plt.grid()
plt.savefig("figure.png", bbox_inches='tight')
plt.show()
