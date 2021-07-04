
from scipy import optimize

def f1(x, a):
    return x[0]**2-a[0]*x[0]+x[1]**2-a[1]*x[1]

x0 = [0, 0]
a = [4, 6]
xopt = optimize.fmin(f1, x0, xtol=1e-8, args=(a,))

print(xopt)