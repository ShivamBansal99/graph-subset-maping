python A3-generate.py $1 $2 $3 $4 > test.graph
./compile.sh
./run1.sh test
./minisat/core/minisat test.satinput test.satoutput
./run2.sh test
python check.py test.graph test.mapping
