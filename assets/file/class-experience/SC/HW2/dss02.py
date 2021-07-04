# Use DSS to optimize function of two variables

from scipy import optimize

def f1(x):
    return x[0]**2-2*x[0]+x[1]**2-4*x[1]

f2 = lambda x: x[0]**2-2*x[0]+x[1]**2-4*x[1]

def banana1(x):
    return 100*(x[1]-x[0]**2)**2+(1-x[0])**2

banana2 = lambda x: 100*(x[1]-x[0]**2)**2+(1-x[0])**2

x0 = [0, 0]
xopt = optimize.fmin(banana1, x0)

print(xopt)