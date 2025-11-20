# This script reads the data stored by advection.f90 in file advection.out and plots the results

# Import mathematical and plot libraries
import numpy as np
import matplotlib.pyplot as plt

# Read data
arr =  np.loadtxt("advection.txt")
x   = arr[0,:]   # location array
y0  = arr[1,:]   # initial condition
y   = arr[2,:]   # numerical solution
yth = arr[3,:]   # analytical solution

# Plot solutions
p = plt.plot(x,yth,lw=0.5,label='Analytical',color='b')
plt.plot(x,y,'.-',color='r',lw=0.5,label='Numerical')

# Setup plot
plt.xlim(0,1)
plt.ylim(-1.2,1.2)
plt.xlabel('x')
plt.ylabel('u')
plt.grid()
plt.legend()
plt.show()

