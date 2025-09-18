import matplotlib.pyplot as plt
import numpy as np
exo = 4





if exo ==1:
    for x in ['1',"2","3"]:
        f = open(f'fich{x}.txt')
        data = f.read()
        data = data.split("\n")
        xData = np.zeros(len(data)-1)
        yData = np.zeros(len(data)-1)
        diffData = np.zeros(len(data)-1)
        for k in range(len(data)):
            if len(data[k])!= 0 :
                [xData[k],yData[k],diffData[k]] = data[k].split(" ")[1:4]
        plt.plot(np.abs(diffData))
    ax = plt.gca()
    ax.set_yscale('log')
    plt.show()

if exo ==2:
    f = open(f'fich21.txt')
    data = f.read()
    data = data.split("\n")
    xData = np.zeros(len(data)-1)
    yData = np.zeros(len(data)-1)
    abscisseData = np.zeros(len(data)-1)
    diffData = np.zeros(len(data)-1)
    for k in range(len(data)):
        if len(data[k])!= 0 :
            [abscisseData[k],xData[k],yData[k],diffData[k]] = data[k].split(" ")[0:4]
    plt.plot(abscisseData,xData, label = "Gamma - P")
    plt.plot(abscisseData,yData, label = "1/(Gamma + P)")
    plt.plot(abscisseData,np.abs(diffData/yData), label = "Relative error")
    ax = plt.gca()
    ax.set_xscale('log')
    ax.set_yscale('log')
    plt.legend()
    plt.show()

if exo ==4 :
    f = open(f'fich41.txt')
    data = f.read()
    data = data.split("\n")
    abscisseData = np.zeros(len(data)-1)
    d1 = np.zeros(len(data)-1)
    d2 = np.zeros(len(data)-1)
    d3 = np.zeros(len(data)-1)
    d4 = np.zeros(len(data)-1)
    d5 = np.zeros(len(data)-1)
    xData = np.e
    for k in range(len(data)):
        if len(data[k])!= 0 :
            [abscisseData[k],d1[k],d2[k],d3[k],d4[k],d5[k]] = data[k].split(" ")[0:6]
    plt.plot(abscisseData,d1, label = "Droite")
    plt.plot(abscisseData,np.abs(d2/xData), label = "Gauche")
    plt.plot(abscisseData,np.abs(d3/xData), label = "Centre")
    plt.plot(abscisseData,np.abs(d4/xData), label = "Centre4")
    plt.plot(abscisseData,np.abs(d5/xData), label = "Centre4B")
    ax = plt.gca()
    ax.set_xscale('log')
    ax.set_yscale('log')
    plt.legend()
    plt.show()
