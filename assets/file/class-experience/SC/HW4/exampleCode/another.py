def hyperplaneFitViaTls(data):
    from numpy.linalg import eig
    import numpy as np
    #first - normalize the matrix
    new_data = []
    average = []
    for i in range(len(data)):
        average.append(sum(data[i])/len(data[i]))
        new_data.append([j - average[i] for j in data[i]])
 
 
 
    #covariance matrix
    #print(new_data)
    cov_max = np.cov(np.array(new_data), rowvar = 1)
    # cov_max = np.array(new_data).dot(np.array(new_data).T)
    
    #decomposite covariance matrix
    eigen_vals, eigenvecs = np.linalg.eig(cov_max)
    print(eigen_vals)
    print(eigenvecs)
    sorted_indices = np.argsort(eigen_vals)
    the_least_num = 0
    the_least = eigen_vals[0]
    for i in range(len(eigen_vals)):
        if the_least > eigen_vals[i]:
            the_least = eigen_vals[i]
            the_least_num = i
    eigenvecs = eigenvecs.T
    least_eigenvecs = eigenvecs[the_least_num]
    print('another min =', least_eigenvecs)
    """first = least_eigenvecs.tolist()
    if first[0] < 0:
        for i in range(len(first)):
            first[i] = -first[i]
    a_d_1 = 0.0
    for i in range(len(data)):
        a_d_1 += average[i] * first[i]
    ans = first
    ans.append(-a_d_1)"""