import numpy as np
import time
import sys
import psutil
import math


def matrixmul(m1,m2):
    global times
    start = time.clock()
    response=[]
    for i in range(len(m1)):
        response.append( m1[i]*m2[i])
    stop= time.clock()
    #print(response)
    times = stop-start


n = int(sys.argv[1])
m1= np.random.random(n)
m2= np.random.random(n)

Ops=0 #ops/s = #elements/time
Bw=0 #ops * sizeof(float)*3 #3 because m1 m2 and resultMatrix
ticks=0 #ticks = cpu freq * time
freq = psutil.cpu_freq()[0] #in MHz

if __name__ == '__main__':
    matrixmul(m1,m2)

    ops= n/times/math.pow(10,9) #n /s / 10^9 to have evething in Gb/s
    ticks =  (freq/math.pow(10,3)) * times #MHz * s 10^3 to have it in Ghz
    Bw=ops*np.dtype(float).itemsize*3 #ops * 8 * 3 (B/s)

    print("time(s)," + str(times)+",")
    print("ops(Gb),"+str(ops)+",")
    print("ticks,"+str(ticks)+",")
    print("Bw(Gb/s),"+str(Bw)+",")

