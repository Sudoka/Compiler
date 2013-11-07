FILES=testfiles/good1*

rm -I *.tic
for f in $FILES
do
#	./instrTube-ic $f instr-out.tic
#	TubeIC instr-out.tic
	echo "Trying file: $f"
	echo "Compiling "
	./tube-ic $f fais.tic
	echo "Running "
	TubeIC fais.tic
	echo "\n"
done
