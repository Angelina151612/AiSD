#!/bin/bash
gcc main.c -o lr1.o 

cat T1.txt
./lr1.o < T1.txt

cat T2.txt
./lr1.o < T2.txt

cat T3.txt
./lr1.o < T3.txt

cat T4.txt
./lr1.o < T4.txt

cat T5.txt
./lr1.o < T5.txt
