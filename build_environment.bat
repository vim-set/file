set working_directory=%~dp0
cd %HOMEPATH%

echo "Making symbolic link for .vimrc"
if exist  .vimrc (
	del  .vimrc
)
mklink .vimrc %working_directory%\vimrc

echo "Making symbolic link for .vim"
if exist  .vim (
	del  .vim
)
mklink /d .vim %working_directory%\vim

echo "Cloning Vundle.vim from github"
mkdir %HOMEPATH%\.vim\bundle\Vundle.vim
git clone https://github.com/gmarik/Vundle.vim.git %HOMEPATH%\.vim\bundle\Vundle.vim

echo "Done!"
