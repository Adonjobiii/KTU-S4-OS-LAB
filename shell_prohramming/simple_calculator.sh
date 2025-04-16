#!/bin/bash

echo "Enter two numbers:"
read a
read b

echo "Your choices are:"
echo "1. Addition"
echo "2. Subtraction"
echo "3. Multiplication"
echo "4. Division"
echo "5. Modulus"
echo -n "Enter your choice: "
read choice

# Function for Addition
addition() {
    echo "$a + $b = $(($a + $b))"
}

# Function for Subtraction
subtraction() {
    echo "$a - $b = $(($a - $b))"
}

# Function for Multiplication
multiplication() {
    echo "$a * $b = $(($a * $b))"
}

# Function for Division
division() {
    if [ $b -ne 0 ]; then
        # Using bc to handle floating-point division
        result=$(echo "scale=2; $a / $b" | bc)
        echo "$a / $b = $result"
    else
        echo "Error: Division by zero is not allowed."
    fi
}

# Function for Modulus
modulus() {
    echo "$a % $b = $(($a % $b))"
}

# Conditional block to select operation
if [ $choice -eq 1 ]; then
    addition
elif [ $choice -eq 2 ]; then
    subtraction
elif [ $choice -eq 3 ]; then
    multiplication
elif [ $choice -eq 4 ]; then
    division    
elif [ $choice -eq 5 ]; then
    modulus
else
    echo "Wrong choice. Please select a valid option."
fi

exit 0
