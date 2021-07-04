function output=mainTest(inputFile, outputFile)

if nargin<1, inputFile='input.txt'; end
if nargin<2, outputFile='output.matlab.txt'; end

% Read input file
fprintf('Reading input file "%s"...\n', inputFile);
output={}; id=1;
fidInput=fopen(inputFile, 'r');
if fidInput<0, error('Cannot open input file "%s"!', inputFile); end
while ~feof(fidInput)
	pv=str2num(fgetl(fidInput));
	notePitch=str2num(fgetl(fidInput));
	figure;
	output{id}=myPvAlignSP(pv, notePitch, 1);
	drawnow;
	fprintf('id=%d, minDist=%f\n', id, output{id}); id=id+1;
	fprintf('\tpv=%s, note=%s\n', mat2str(pv), mat2str(notePitch));
end
fclose(fidInput);

% Write output file
fprintf('Writing output file "%s"...\n', outputFile);
fidOutput=fopen(outputFile, 'w');
if fidOutput<0, error('Cannot open output file "%s"!', outputFile); end
for i=1:length(output)
	fprintf(fidOutput, '%.15f ', output{i});
	fprintf(fidOutput, '\n');
end
fclose(fidOutput);