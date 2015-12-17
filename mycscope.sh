#!/bin/bash


echo "[Indexing for cscope]..."
find $(pwd) ! \( -path './build' -prune \) -iname "*.c"    > ./cscope.files
find $(pwd) ! \( -path './build' -prune \) -iname "*.cc"    > ./cscope.files
find $(pwd) ! \( -path './build' -prune \) -iname "*.cpp" >> ./cscope.files
find $(pwd) ! \( -path './build' -prune \) -iname "*.h"   >> ./cscope.files
find $(pwd) ! \( -path './build' -prune \) -iname "*.hh"   >> ./cscope.files
find $(pwd) ! \( -path './build' -prune \) -iname "*.hpp" >> ./cscope.files
cscope -cb

rm ./cscope.files
echo "[Indexing for ctags]..."
#ctags --fields=+i -n -R -L ./cscope.files
#cqmakedb -s ./myproject.db -c ./cscope.out -t ./tags -p

