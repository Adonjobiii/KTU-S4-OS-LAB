#!/bin/bash

i=1
sum=0  # Initialize sum to 0
echo "Enter the limit (number of numbers to input):"
read n

echo "Enter the numbers:"
while [ $i -le $n ]
do
    read num
    sum=$(($sum + $num))
    i=$(($i + 1))
done

# Calculate the average
average=$(($sum / $n))
echo "Average = $average"
