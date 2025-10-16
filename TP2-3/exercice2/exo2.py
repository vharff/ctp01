import numpy as np
import matplotlib.pyplot as plt

gamma, M = np.loadtxt("star.txt",unpack=True,max_rows=1)

r,g,rho = np.loadtxt("star.txt",unpack=True, skiprows=1)

plt.plot(r,g-1)
plt.yscale('log')
plt.ylim(1.e-6,)
plt.xlabel('r')
plt.ylabel(r'$g(r)-1$')
plt.title(f'Metrics for $\gamma$={gamma:.2f}, M={M}')
plt.grid()
#plt.savefig("metrics.png", bbox_inches='tight')
plt.show()

plt.plot(r,rho,label='rho')
plt.yscale('log')
plt.xlabel('r')
plt.ylabel(r'$\rho(r)$')
plt.title(f'Density for $\gamma$={gamma:.2f}, M={M}')
plt.grid()
#plt.savefig("density.png", bbox_inches='tight')
plt.show()
