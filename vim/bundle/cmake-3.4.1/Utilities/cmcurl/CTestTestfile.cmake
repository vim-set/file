# CMake generated Testfile for 
# Source directory: /home/skchoi2/works/vim-set/file/vim/bundle/cmake-3.4.1/Utilities/cmcurl
# Build directory: /home/skchoi2/works/vim-set/file/vim/bundle/cmake-3.4.1/Utilities/cmcurl
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(curl "LIBCURL" "http://open.cdash.org/user.php")
subdirs(lib)
