# CMake generated Testfile for 
# Source directory: /home/skchoi2/works/vim-set/file/vim/bundle/cmake-3.4.1
# Build directory: /home/skchoi2/works/vim-set/file/vim/bundle/cmake-3.4.1
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/home/skchoi2/works/vim-set/file/vim/bundle/cmake-3.4.1/Tests/EnforceConfig.cmake")
add_test(SystemInformationNew "/home/skchoi2/works/vim-set/file/vim/bundle/cmake-3.4.1/bin/cmake" "--system-information" "-G" "Unix Makefiles")
subdirs(Utilities/KWIML)
subdirs(Source/kwsys)
subdirs(Utilities/cmzlib)
subdirs(Utilities/cmcurl)
subdirs(Utilities/cmcompress)
subdirs(Utilities/cmbzip2)
subdirs(Utilities/cmliblzma)
subdirs(Utilities/cmlibarchive)
subdirs(Utilities/cmexpat)
subdirs(Utilities/cmjsoncpp)
subdirs(Source/CursesDialog/form)
subdirs(Source)
subdirs(Utilities)
subdirs(Tests)
subdirs(Auxiliary)
