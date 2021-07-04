# Use DSS to optimize function of one variable, with parameter

from scipy import optimize
def f(x, a):
    return x**2-a*x+5

x0 = 0
a = 20;
xopt = optimize.fmin(f, x0, xtol=1e-8, args=(a,))

print(xopt)