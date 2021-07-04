def circleFitByDss(data):
	from scipy.optimize import fmin
	def f(p, x, y):
		summ = 0.0
		for i in range(len(x)):
			summ += abs(((x[i] - p[0])**2 + (y[i] - p[1])**2)**(1/2) - p[2])
		return summ
	p0 = [0.0, 0.0, 0.0]
	for i in range(len(data[0])):
		p0[0] += data[0][i]
		p0[1] += data[1][i]
	p0[0] /= len(data[0])
	p0[1] /= len(data[0])
	for i in range(len(data[0])):
		p0[2] += ((data[0][i] - p0[0])**2 + (data[1][i] - p0[1])**2)**(1/2)
	p0[2] /= len(data[0])
	a, b, r = fmin(f, p0, args=(data[0], data[1]), disp=False, maxiter=10)
	return a, b, r
	   

