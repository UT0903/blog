This is the readme.txt file in example code for HW05 of Scientific Computing

Your submission (you only need to submit one of the following):
	Python: myPvAlign.py
	Matlab: myPvAlign.m

Example input/output files:
	input.txt: input file
	output.standard_python.txt: output file (the correct answer returned by Python)
	output.standard_matlab.txt: output file (the correct answer returned by MATLAB)

Input/output file format:
	Input:
		Each two-row is a set of singing pitch vector and music note vector, with the first row being the singing pitch vector and the second row music note vector
		For each two-row, you need to generate a number of minimum distance of the alignment of these two vectors.
		For instance, "input.txt" has 96 rows, indicating there are 48 problems for the alignment, and you should generate 48 minimum distances.
	Output:
		A column vector of numbers, with each row being an answer to an alignment problem.

Example main program to run the test:
	Python: mainTest.py, with the following command to run it.
		python mainTest.py < input.txt > output.python.txt
	Matlab: mainText.m, with the following command (within matlab) to run it.
		mainText input.txt output.matlab.txt

Standard program for MATLAB
	myPvAlignSP.p is a standard program that can be invoked just like an M file in MATLAB to check against your submission of "myPvAlign.m".
	In particular, if you type "myPvAlignSP(PV, NOTE, 1), the program will show result of dynamic programming which assigns each point of PV to each note in NOTE.