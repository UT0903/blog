def myPvAlign(pv, noteVec):
	import numpy as np
	graph = np.zeros((len(pv), len(noteVec)+1))
	for i in range(len(graph)):
		graph[i][0] = 100000
		for j in range(1, min(len(graph[0]), i + 2)):
			graph[i][j] = abs(pv[i] - noteVec[j-1])
		for j in range(i+2, len(graph[0])):
			graph[i][j] = 100000
	#print(graph)
	for i in range(1, len(graph)):
		for j in range(1, len(graph[0])):
			graph[i][j] += min(graph[i-1][j], graph[i-1][j-1])
	minn = 1000000
	for i in range(1, len(graph[0])):
		if graph[-1][i] < minn:
			minn = graph[-1][i]
	return minn
	#min(graph[len(graph)-1][x] for x in range(1, len(graph[0])))

#print(myPvAlign([1,2,3,4,5,6,7], [2,3,4,5,6]))