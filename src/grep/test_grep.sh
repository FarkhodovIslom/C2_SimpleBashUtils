#!/bin/bash

# Simple test script for s21_grep

echo "=== Testing s21_grep utility ==="
echo

# Test 1: Basic pattern search
echo "Test 1: Basic pattern search"
./s21_grep "test" test.txt > s21_output.txt
grep "test" test.txt > grep_output.txt
if diff -q s21_output.txt grep_output.txt > /dev/null; then
    echo "✓ PASS"
else
    echo "✗ FAIL"
    echo "Expected:"
    cat grep_output.txt
    echo "Got:"
    cat s21_output.txt
fi
echo

# Test 2: -i flag (ignore case)
echo "Test 2: -i flag (ignore case)"
./s21_grep -i "hello" test.txt > s21_output.txt
grep -i "hello" test.txt > grep_output.txt
if diff -q s21_output.txt grep_output.txt > /dev/null; then
    echo "✓ PASS"
else
    echo "✗ FAIL"
fi
echo

# Test 3: -v flag (invert match)
echo "Test 3: -v flag (invert match)"
./s21_grep -v "test" test.txt > s21_output.txt
grep -v "test" test.txt > grep_output.txt
if diff -q s21_output.txt grep_output.txt > /dev/null; then
    echo "✓ PASS"
else
    echo "✗ FAIL"
fi
echo

# Test 4: -c flag (count only)
echo "Test 4: -c flag (count only)"
./s21_grep -c "test" test.txt > s21_output.txt
grep -c "test" test.txt > grep_output.txt
if diff -q s21_output.txt grep_output.txt > /dev/null; then
    echo "✓ PASS"
else
    echo "✗ FAIL"
fi
echo

# Test 5: -n flag (line numbers)
echo "Test 5: -n flag (line numbers)"
./s21_grep -n "test" test.txt > s21_output.txt
grep -n "test" test.txt > grep_output.txt
if diff -q s21_output.txt grep_output.txt > /dev/null; then
    echo "✓ PASS"
else
    echo "✗ FAIL"
fi
echo

# Test 6: -e flag (multiple patterns)
echo "Test 6: -e flag (multiple patterns)"
./s21_grep -e "Hello" -e "numbers" test.txt > s21_output.txt
grep -e "Hello" -e "numbers" test.txt > grep_output.txt
if diff -q s21_output.txt grep_output.txt > /dev/null; then
    echo "✓ PASS"
else
    echo "✗ FAIL"
fi
echo

# Test 7: -f flag (patterns from file)
echo "Test 7: -f flag (patterns from file)"
./s21_grep -f patterns.txt test.txt > s21_output.txt
grep -f patterns.txt test.txt > grep_output.txt
if diff -q s21_output.txt grep_output.txt > /dev/null; then
    echo "✓ PASS"
else
    echo "✗ FAIL"
fi
echo

# Test 8: Combined flags -in
echo "Test 8: Combined flags -in"
./s21_grep -in "HELLO" test.txt > s21_output.txt
grep -in "HELLO" test.txt > grep_output.txt
if diff -q s21_output.txt grep_output.txt > /dev/null; then
    echo "✓ PASS"
else
    echo "✗ FAIL"
fi
echo

# Cleanup
rm -f s21_output.txt grep_output.txt

echo "=== Tests completed ==="
