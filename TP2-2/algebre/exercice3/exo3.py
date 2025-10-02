import math
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import CubicSpline

# Read data
# =============================

data1 = np.loadtxt("vvp_QR.txt")
vap1  = data1[0,:]
vep1  = data1[1:,:]

data2 = np.loadtxt("vvp_SI.txt")
vap2  = data2[0,:]
vep2  = data2[1:,:]

# Plot spectrum of eigenvalues
# =============================

plt.plot(vap1,ls='',marker='x',label="method#1")
plt.plot(vap2,ls='',marker='o',markersize=3,label="method#2")

x = np.linspace(0,len(vap1),100)
plt.plot(x,(np.pi*(x+1))**2,'k',ls=':',lw=0.5, label='analytical')

plt.legend()
plt.xlabel(r"Index $i$")
plt.ylabel(r"Eigenvalue $(i+1)^2\pi^2$")
plt.xlim(0,len(vap1))
plt.ylim(0,)
plt.grid()
plt.savefig('eigenvalues.png',bbox_inches='tight')
plt.show()


# Plot some eigenvectors
# =============================

#index of eigenvector to plot
vects = [0,1,5]
title = f"Eigenvectors"


for i,iv in enumerate(vects):

    title += f" {iv},"
    if i==0:
        lab1 = f"method#1"
        lab2 = f"method#2"
    else:
        lab1 = None
        lab2 = None

    v1    = vep1[:,iv]
    x1 = np.linspace(0,1,len(v1))
    l, = plt.plot(x1, np.sign(v1[1])*v1,marker='x',ls='', label=lab1)

    v2    = vep2[:,iv]
    x2 = np.linspace(0,1,len(v2))
    plt.plot(x2, np.sign(v2[1])*v2, marker='o',markersize=3, ls='', color=l.get_color(), label=lab2)

    x = np.linspace(0,1,100)
    plt.plot(x,np.max(abs(v2))*np.sin(np.pi*(iv+1)*x),color='k',lw=0.5)

plt.legend()
plt.xlim(0,1)
plt.title(title)
plt.ylabel(r"Vector Coordinates $v_i$")
plt.xlabel(r"Position $x_i$")
plt.grid()
plt.savefig('eigenvectors.png',bbox_inches='tight')
plt.show()
