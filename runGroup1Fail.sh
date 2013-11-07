FILES=testfiles/fail1*

rm -I *.tic
for f in $FILES
do
	echo "Trying file: $f"
	echo "Compiling "
	./tube4 $f instr-out.tic
	echo "Running "
	TubeIC instr-out.tic
	echo "\nCompiling "
	./tube-ic $f fais.tic
	echo "Running "
	TubeIC fais.tic
	echo "\n"
done
