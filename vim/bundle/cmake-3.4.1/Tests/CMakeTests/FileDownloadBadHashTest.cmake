set(url "file:///home/skchoi2/works/vim-set/file/vim/bundle/cmake-3.4.1/Tests/CMakeTests/FileDownloadInput.png")
set(dir "/home/skchoi2/works/vim-set/file/vim/bundle/cmake-3.4.1/Tests/CMakeTests/downloads")

file(DOWNLOAD
  ${url}
  ${dir}/file3.png
  TIMEOUT 2
  STATUS status
  EXPECTED_HASH SHA1=5555555555555555555555555555555555555555
  )
