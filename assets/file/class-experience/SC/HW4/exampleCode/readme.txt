This is the readme.txt file in example code for HW04 of Scientific Computing

Your submission (you only need to submit one of the following):
	Python: hyperplaneFitViaTls.py
	Matlab: hyperplaneFitViaTls.m

Example input/output files:
	input.txt: input file
	output.standard_python.txt: output file (the correct answer returned by Python)
	output.standard_matlab.txt: output file (the correct answer returned by MATLAB)

Input/output file format:
	Input:
		The first line is the number of rows, D, of the subsequent dataset.
		The dataset is a D-by-N matrix, with each row being placed in a horizontal line, and the last row is the desired output.
		The above (D+1) lines are repeated as many times as the number of datasets in the file.
		For instance, "input.txt" has 10 datasets in the file.
	Output:
		For a dataset, the output will be the coefficients of the fitting hyperplane.

Example main program to run the test:
	Python: mainTest.py, with the following command to run it.
		python mainTest.py < input.txt > output.python.txt
	Matlab: mainText.m, with the following command (within matlab) to run it.
		mainText input.txt output.matlab.txt

Standard program for MATLAB
	hyperplaneFitViaTlsSP.p is a standard program that can be invoked just like an M file in MATLAB to check against your submission of "hyperplaneFitViaTls.m".
	In particular, if you type "hyperplaneFitSP(data, 1), the program will show the dataset together with the final plane for fitting.