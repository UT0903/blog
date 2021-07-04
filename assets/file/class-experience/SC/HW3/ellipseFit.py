import numpy as np
from scipy import optimize

def ellipseFit(data):
    def f(center, data):
    	r = sseOfEllipseFit(center, data)
    	#print(r)
    	summ = 0.0
    	for i in range(len(data[0])):
    		summ += (((data[0][i] - center[0])**2)/(r[0]**2) + ((data[1][i] - center[1])**2)/(r[1]**2) - 1)**2
    	return summ
    center0 = np.zeros(2)
    for i in range(len(data[0])):
    	for j in range(2):
    		center0[j] += data[j][i]
    center0[0] /= len(data[0])
    center0[1] /= len(data[0])
    #print(center0)
    center = optimize.fmin(f, center0, args=(data,), disp=False)
    #print(center)
    R = sseOfEllipseFit(center, data)
    return center[0], center[1], R[0], R[1]

def sseOfEllipseFit(center, data):
    A = np.zeros((len(data[0]), 2))
    B = np.ones(len(data[0])).T
    B = B.T
    for i in range(len(data[0])):
    	A[i][0] = (data[0][i] - center[0])**2
    	A[i][1] = (data[1][i] - center[1])**2
    a, b = np.linalg.lstsq(A, B, rcond=None)[0]
    return (1/abs(a))**(1/2), (1/abs(b))**(1/2)