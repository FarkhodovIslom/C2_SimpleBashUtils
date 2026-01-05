#!/bin/bash

# Simple test script for s21_cat

echo "=== Testing s21_cat utility ==="
echo

# Test 1: Basic output
echo "Test 1: Basic output"
./s21_cat test.txt > s21_output.txt
cat test.txt > cat_output.txt
if diff -q s21_output.txt cat_output.txt > /dev/null; then
    echo "✓ PASS"
else
    echo "✗ FAIL"
fi
echo

# Test 2: -b flag (number non-blank lines)
echo "Test 2: -b flag (number non-blank lines)"
./s21_cat -b test.txt > s21_output.txt
cat -b test.txt > cat_output.txt
if diff -q s21_output.txt cat_output.txt > /dev/null; then
    echo "✓ PASS"
else
    echo "✗ FAIL"
fi
echo

# Test 3: -n flag (number all lines)
echo "Test 3: -n flag (number all lines)"
./s21_cat -n test.txt > s21_output.txt
cat -n test.txt > cat_output.txt
if diff -q s21_output.txt cat_output.txt > /dev/null; then
    echo "✓ PASS"
else
    echo "✗ FAIL"
fi
echo

# Test 4: -s flag (squeeze blank lines)
echo "Test 4: -s flag (squeeze blank lines)"
./s21_cat -s test.txt > s21_output.txt
cat -s test.txt > cat_output.txt
if diff -q s21_output.txt cat_output.txt > /dev/null; then
    echo "✓ PASS"
else
    echo "✗ FAIL"
fi
echo

# Test 5: Combined flags -bn
echo "Test 5: Combined flags -bn"
./s21_cat -bn test.txt > s21_output.txt
cat -bn test.txt > cat_output.txt
if diff -q s21_output.txt cat_output.txt > /dev/null; then
    echo "✓ PASS"
else
    echo "✗ FAIL"
fi
echo

# Cleanup
rm -f s21_output.txt cat_output.txt

echo "=== Tests completed ==="
