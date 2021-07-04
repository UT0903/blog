This is the readme.txt file in example code for HW03 of Scientific ComputingaddAndMax

Your submission (you only need to submit one of the following):
	Python: ellipseFit.py
	Matlab: ellipseFit.m

Example input/output files:
	input.txt: input file
	output.standard_python.txt: output file (the correct answer returned by Python)
	output.standard_matlab.txt: output file (the correct answer returned by MATLAB)

Input/output file format:
	Input:
		Each two-row is a set of 2D points, with the first row is X coordinates and the second row is Y coordinates.
		For each two-row, you need to generate a set of [cx, cy, rx, ry]
		For instance, "input.txt" has 20 rows, indicating there are 10 sets of 2D points, and you need to output 10 sets of answers.
	Output:
		A matrix of numbers, with each row being an answer to a set of 2D points.

Example main program to run the test:
	Python: mainTest.py, with the following command to run it.
		python mainTest.py < input.txt > output.python.txt
	Matlab: mainText.m, with the following command (within matlab) to run it.
		mainText input.txt output.matlab.txt

Standard program for MATLAB
	ellipseFitSP.p is a standard program that can be invoked just like an M file in MATLAB to check against your submission of "ellipseFit.m".
	In particular, if you type "ellipseFitSP(data, 1), the program will show the dataset together with the final ellipse for fitting.
	Some of the fitting results are placed under "output" folder for comparison.

Requirement:
	Python: You need to use scipy.optimize.fmin() for DSS, and numpy.linalg.lstsq() for least-square estimate.
	Matlab: You need to use fminsearch() for DSS, and "\" for least-square estimate.
