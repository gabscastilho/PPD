for i in {1..3}; do
    echo "Compilando mm$i"
    gcc mm$i.c -o mm$i -O3 -fopenmp    
done

for i in {1,2,4,8,16,32,64,128}; do 
        for j in {1..3}; do 
                echo "Rodando mm$j com $i threads"
                OMP_NUM_THREADS=$i time ./mm$j < 2048 > /dev/null
        done
        echo
done