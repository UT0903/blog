
from scipy import optimize

def f1(x, a, b):
    return x[0]**2-a*x[0]+x[1]**2-b*x[1]

x0 = [0, 0]
a = 2
b = 4
xopt = optimize.fmin(f1, x0, xtol=1e-8, args=(a, b,))

print(xopt)