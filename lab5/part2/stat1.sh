#!/bin/bash

for ((i = 10000; i <= 50000; i+=10000))
do
./lab5 -s p -k a -o a -e $i -a 5
done

for ((i = 100000; i <= 150000; i+=50000))
do
./lab5 -s p -k a -o a -e $i -a 5
done

