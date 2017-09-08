#!/bin/bash

echo "[ALL Source Path]..."
find $(pwd) -iname "*.c"   >> ./cscope.files
find $(pwd) -iname "*.cc"  >> ./cscope.files
find $(pwd) -iname "*.cpp" >> ./cscope.files

echo "[ALL Header Path]..."
find $(pwd) -iname "*.h"   >> ./cscope.files
find $(pwd) -iname "*.hpp" >> ./cscope.files
echo "[ALL Header Path2]..."
cscope -b

echo "[Indexing for ctags]..."
ctags --fields=+i -n -R -L ./cscope.files
rm ./cscope.files
