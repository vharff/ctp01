import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import minimize






nxQ4 = [[64, 128, 256  ,512  ,1024 ],'nx']
relerrQ4 = [1.5508e-02,7.7018e-03,3.8563e-03,1.9261e-03,9.6347e-04,'Erreur relative']
tQ5 = [[1,2,4,8,16],"T max (s)"] 
relerrQ5 = [[1.5508e-02,3.0522e-02,6.0156e-02,1.1635e-01,2.1920e-01],"Erreur relative"]

cflQ6 = [[1.2,1.1,1.05,1.025,0.975,0.95,0.9,0.8],"CFL"]   #Prendre np.abs(cfl-1)
relerrQ6 = [[-6.4856e-02,-3.1966e-02,-1.5595e-02,-7.8449e-03,7.7494e-03,1.5508e-02,3.0876e-02,5.9932e-02],"Erreur relative"] #Prendre val absolue


def loglogregression(x,y):
    def loglogscore(par):
        [order,cst] = par
        res = 0
        for i in range(len(x)):
            res += (np.log(y[i])-cst-order*np.log(x[i]))**2
        return(res)
    order = 1
    cst = 0
    par = [order,cst]
    opti = minimize(loglogscore,par,options = {"maxiter":20})
    optpar = opti.x
    regressiony = [np.exp(optpar[0]*np.log(x[i])+optpar[1])  for i in range(len(x))]
    plt.plot(x,regressiony,label = f"Reg. Linéaire - Pente : {np.round(optpar[0],4)}")
    plt.legend()
    plt.scatter(x,y,ec='b',fc='r',zorder = 10)


def plotter(x,y):
    loglogregression(x[0],y[0])
    plt.xlabel(x[1])
    plt.ylabel(y[1])
    ax = plt.gca()
    ax.set_xscale('log')
    ax.set_yscale('log')
    plt.title(f"Erreur relative en fonction de {x[1]}")
    plt.show()

plotter(tQ5,relerrQ5)

