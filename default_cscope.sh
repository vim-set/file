echo "[ALL Source Path]..."
find -iname "*.c"   >> ./cscope.files
find -iname "*.cc"  >> ./cscope.files
find -iname "*.cpp" >> ./cscope.files

echo "[ALL Header Path]..."
find -iname "*.h"   >> ./cscope.files
find -iname "*.hpp" >> ./cscope.files
cscope -cb

echo "[Indexing for ctags]..."
ctags --fields=+i -n -R -L ./cscope.files
rm ./cscope.files
#cqmakedb -s ./myproject.db -c ./cscope.out -t ./tags -p
