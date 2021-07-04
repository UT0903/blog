# Use DSS to optimize function of one variable

from scipy import optimize
def f(x):
    return x**2-4*x+5

x0 = 0
xopt = optimize.fmin(f, x0)

print(xopt)