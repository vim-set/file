#!/bin/bash
working_directory=$(pwd)
files=("vim" "vimrc")

cd ~
for file in "${files[@]}"
do
	dotfile=."$file"
	echo "Making symbolic link for $file"
	if [ -e "$dotfile" ] || [ -L "$dotfile" ]
	then
		rm "$dotfile"
	fi
	ln -s $working_directory/$file "$dotfile"
done

# install vundle
echo "Cloning Vundle.vim from github"
git clone https://github.com/gmarik/Vundle.vim.git ~/.vim/bundle/Vundle.vim

sudo npm install jshint -g

echo "Done!"
