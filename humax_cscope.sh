#!/bin/bash

BROWSER_PATH=apps/appl/browser/corsair/base-2.0
BROWSER_PATH2=apps/appl/browser/archon/base-2.0
OCTO_APPKIT_PATH=apps/octo/appkit/
OCTO_SERVICE_PATH=apps/octo/service/
OCTO_LIBRARY_PATH=apps/octo/library/
DEVICE_PATH=device/platform/driver/

echo "[Indexing for cscope]..."
echo "[Browser Source Path]..."
find $(pwd)/$BROWSER_PATH2 ! \( -path $(pwd)/$BROWSER_PATH2/build -prune \) -iname "*.c"   >> ./cscope.files
find $(pwd)/$BROWSER_PATH2 ! \( -path $(pwd)/$BROWSER_PATH2/build -prune \) -iname "*.cc"  >> ./cscope.files
find $(pwd)/$BROWSER_PATH2 ! \( -path $(pwd)/$BROWSER_PATH2/build -prune \) -iname "*.cpp" >> ./cscope.files
find $(pwd)/$BROWSER_PATH2 ! \( -path $(pwd)/$BROWSER_PATH2/build -prune \) -iname "*.h"   >> ./cscope.files
find $(pwd)/$BROWSER_PATH2 ! \( -path $(pwd)/$BROWSER_PATH2/build -prune \) -iname "*.hpp" >> ./cscope.files

find $(pwd)/$BROWSER_PATH ! \( -path $(pwd)/$BROWSER_PATH/build -prune \) -iname "*.c"   >> ./cscope.files
find $(pwd)/$BROWSER_PATH ! \( -path $(pwd)/$BROWSER_PATH/build -prune \) -iname "*.cc"  >> ./cscope.files
find $(pwd)/$BROWSER_PATH ! \( -path $(pwd)/$BROWSER_PATH/build -prune \) -iname "*.cpp" >> ./cscope.files
find $(pwd)/$BROWSER_PATH ! \( -path $(pwd)/$BROWSER_PATH/build -prune \) -iname "*.h"   >> ./cscope.files
find $(pwd)/$BROWSER_PATH ! \( -path $(pwd)/$BROWSER_PATH/build -prune \) -iname "*.hpp" >> ./cscope.files

echo "[OCTO Source Path]..."
find $(pwd)/$OCTO_APPKIT_PATH -iname "*.c"   >> ./cscope.files
find $(pwd)/$OCTO_APPKIT_PATH -iname "*.cpp" >> ./cscope.files
find $(pwd)/$OCTO_APPKIT_PATH -iname "*.h"   >> ./cscope.files

find $(pwd)/$OCTO_SERVICE_PATH -iname "*.c"   >> ./cscope.files
find $(pwd)/$OCTO_SERVICE_PATH -iname "*.cpp" >> ./cscope.files
find $(pwd)/$OCTO_SERVICE_PATH -iname "*.h"   >> ./cscope.files

find $(pwd)/$OCTO_LIBRARY_PATH -iname "*.c"   >> ./cscope.files
find $(pwd)/$OCTO_LIBRARY_PATH -iname "*.cpp" >> ./cscope.files
find $(pwd)/$OCTO_LIBRARY_PATH -iname "*.h"   >> ./cscope.files


echo "[Device Source Path]..."
find $(pwd)/$DEVICE_PATH -iname "*.c"   >> ./cscope.files
find $(pwd)/$DEVICE_PATH -iname "*.h"   >> ./cscope.files 

cscope -cb

echo "[Indexing for ctags]..."
ctags --fields=+i -n -R -L ./cscope.files
rm ./cscope.files
#cqmakedb -s ./myproject.db -c ./cscope.out -t ./tags -p

