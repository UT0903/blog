def hyperplaneFitViaTls(data):
	from numpy.linalg import eig
	import numpy as np
	normalized_data, average = [], []
	for i in range(len(data)):
		average.append(sum(data[i]) / len(data[i]))
		normalized_data.append([ele - average[i] for ele in data[i]])
	eigval, eigvec = np.linalg.eig(np.cov(np.array(normalized_data)))
	return np.append(np.sign((eigvec.T)[np.argmin(eigval)][0]) * (eigvec.T)[np.argmin(eigval)], -np.dot(average, np.sign((eigvec.T)[np.argmin(eigval)][0]) * (eigvec.T)[np.argmin(eigval)])) 