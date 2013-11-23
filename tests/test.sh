FAIL_COUNT=0
TEST_NUMBER=0

MY_TUBE_EXEC="./tube5"
EX_TUBE_EXEC="./correct/tube5"

TUBECODE_EXEC="./tubecode"

for file in /Users/mwein/Projects/GitHub/Project6/tests/p6/* #{p5,p6}/*
do
 TEST_NUMBER=$[TEST_NUMBER+1]
 
 FILENAME=`basename "$file" .tube`

 my_output_tca=/Users/mwein/Projects/GitHub/Project6/tests/my_tca_output/$FILENAME.tca
 my_temp_output_tca_result=/Users/mwein/Projects/GitHub/Project6/tests/my_tca_output/temp.output
 my_output_result=/Users/mwein/Projects/GitHub/Project6/tests/my_program_output/$FILENAME.output
 
 ex_output_tca=/Users/mwein/Projects/GitHub/Project6/tests/ex_tca_output/$FILENAME.tca
 ex_temp_output_tca_result=/Users/mwein/Projects/GitHub/Project6/tests/ex_tca_output/temp.output
 ex_output_result=/Users/mwein/Projects/GitHub/Project6/tests/ex_program_output/$FILENAME.output
 
 touch $my_output_tca
 touch $my_temp_output_tca_result
 touch $my_output_result

 touch $ex_output_tca
 touch $ex_temp_output_tca_result
 touch $ex_output_result

 $MY_TUBE_EXEC $file $my_output_tca > $my_temp_output_tca_result
 $MY_TUBE_EXEC $file $ex_output_tca > $ex_temp_output_tca_result #replace with ex

 MY_TMP_OUTPUT=`cat $my_temp_output_tca_result`

 if ! [ "$MY_TMP_OUTPUT" = "Parse Successful!" ]; then
   echo "TEST: $TEST_NUMBER $FILENAME"
   cat $my_temp_output_tca_result
 fi
  
 $TUBECODE_EXEC $my_output_tca > $my_output_result
 $TUBECODE_EXEC $ex_output_tca > $ex_output_result  #replace with ex

 #always true right now
 if ! diff $my_output_tca $my_output_tca >/dev/null ; then
  FAIL_COUNT=$[FAIL_COUNT+1]
  echo FAIL
  echo TEST: $TEST_NUMBER
  echo FILE: $file
  cat $file
 fi
done

if [ $FAIL_COUNT -gt 0 ] 
then
 echo $FAIL_COUNT "TEST(S) FAILED"
else
 echo $TEST_NUMBER "TEST(S) SUCCEEDED"
fi

echo EXECUTION COMPLETE