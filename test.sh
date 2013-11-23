FAIL_COUNT=0
TEST_NUMBER=0

TUBE_EXEC="./tube5"
TUBECODE_EXEC="./test_files/tubecode"

for file in /Users/mwein/Projects/GitHub/Project6/test_files/p5/* #{p5,p6}/*
do
 TEST_NUMBER=$[TEST_NUMBER+1]
 
 my_output_tca=/Users/mwein/Projects/GitHub/Project6/test_files/tca_output/$TEST_NUMBER.tca
 my_temp_output_tca_result=/Users/mwein/Projects/GitHub/Project6/test_files/tca_output/temp.output
 my_output_result=/Users/mwein/Projects/GitHub/Project6/test_files/program_output/$TEST_NUMBER.output
 
 touch $my_output_tca
 touch $my_temp_output_tca_result
 touch $my_output_result
 
 $TUBE_EXEC $file $my_output_tca > $my_temp_output_tca_result
 TMP_OUTPUT=`cat $my_temp_output_tca_result`

 if ! [ "$TMP_OUTPUT" = "Parse Successful!" ]; then
   echo "TEST: $TEST_NUMBER"
   cat $my_temp_output_tca_result
 fi
  

 $TUBECODE_EXEC $my_output_tca > $my_output_result

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