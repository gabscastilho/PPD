gcc mm.c -o mm -O3 -fopenmp
time ./mm < 2048 > /dev/null