#!/bin/bash


gcc ../Sources/main.c -lpthread -lrt -o ../Bin/main.out
gcc ../Sources/A.c -lpthread -lrt -o ../Bin/A.out
gcc ../Sources/B.c -lpthread -lrt -o ../Bin/B.out
gcc ../Sources/C.c -lpthread -lrt -o ../Bin/C.out
gcc ../Sources/prod.c -lpthread -lrt -o ../Bin/prod.out

./../Bin/main.out &
./../Bin/A.out &
./../Bin/B.out &
./../Bin/C.out &
./../Bin/prod.out &



