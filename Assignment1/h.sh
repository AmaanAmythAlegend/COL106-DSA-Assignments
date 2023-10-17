g++ -o my_program main.cpp
start=$(date +%s)
./my_program < test1.txt > output.txt
end=$(date +%s)
total_time=$((end - start))
if cmp -s output.txt result1.txt; then
    echo "All tests passed: Output matches result1.txt"
else
    echo "Some tests failed: Output does not match result1.txt"
fi

total_test_cases=$(wc -l < test1.txt)
echo "Total test cases: $total_test_cases"
echo "Total time taken: $total_time seconds"
rm my_program output.txt