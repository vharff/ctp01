import numpy as np
import matplotlib.pyplot as plt

# Physical constants
hbar = 1.0546e-34    # Planck constant (J.s)
mp   =  1.6726e-27   # Proton mass (kg)
G    = 6.6726e-11    # Gravitationnal constant (m3/s2/kg)
c    = 2.9979e8      # speed of light (m/s)
c2   = c*c
Msol = 1.988e30      # solor mass (kg)
km   = 1000          # kilometer (m)

# Equation of state
gamma = np.loadtxt("mr.txt",unpack=True, max_rows=1)
K = (3*np.pi**2)**(2./3.)/5 * hbar**2 / mp**(8./3)

# normalisations
rho0 = (c2/K)**(1./(gamma-1.))
P0 = rho0*c2
R0 = (c2/G/rho0)**0.5
M0 = rho0*R0**3

# Plots
M,R = np.loadtxt("mr.txt",unpack=True, skiprows=1)
plt.plot(R*R0/km,M*M0/Msol)
plt.xlim(7,)
plt.ylim(0,)
plt.xlabel('R (km)')
plt.ylabel(r'$M \ / \ M_\odot$')
plt.title(f'M-R relation ($\gamma$={gamma:.2f}, K={K:.2f})')
plt.grid()
#plt.savefig("MR.png", bbox_inches='tight')
plt.show()
