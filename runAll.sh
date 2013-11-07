FILES=testfilesOLD/good*

rm -I *.tic
for f in $FILES
do
	echo "Testing: $f"
	./instrTube-ic $f instr-out.tic
	TubeIC instr-out.tic
	./tube-ic $f fais.tic
	TubeIC fais.tic
	echo "\n"
done
