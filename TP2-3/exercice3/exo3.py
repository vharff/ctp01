import numpy as np
import matplotlib.pyplot as plt

H100 = 100
c = 299792.4585

# Plot data points
xdata, ydata, dydata = np.loadtxt('sndata.txt', unpack=True, skiprows=1)
plt.errorbar(xdata,ydata/1000,dydata/1000,ls='',marker='o',markersize=2,elinewidth=1)

# Plot model
h,Wm = np.loadtxt('model.txt', unpack=True, max_rows=1)
x,y = np.loadtxt('model.txt', unpack=True, skiprows=1)
plt.plot(x,y*c/H100/1000)
plt.xlabel(r'Redshift $z$')
plt.ylabel(r'Luminosity Distance $D_L$ (Gpc)')
plt.title(f'h = {h:.3f},   $\Omega_m$={Wm:.3f}')

plt.savefig("sn.png",bbox_inches='tight')
plt.show()
