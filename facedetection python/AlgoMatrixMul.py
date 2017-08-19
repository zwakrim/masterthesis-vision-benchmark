import numpy as np
import time
import sys



def matrixmul(m1,m2):
    start = time.clock()
    response=[]
    for i in range(len(m1)):
        response.append( m1[i]*m2[i])
    stop= time.clock()
    #print(response)
    end= stop-start
    print("time,"+str(end)+",")

n = int(sys.argv[1])
m1= np.random.random(n)
m2= np.random.random(n)

if __name__ == '__main__':

    matrixmul(m1,m2)
