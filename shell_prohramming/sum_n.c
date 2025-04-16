#!/bin/bash

i=0
sum=0
echo "Enter the limit (N):"
read N

while [ $i -lt $N ]
do
    i=$(expr $i + 1)
    sum=$(($sum + $i))
done

echo "Sum = $sum"
