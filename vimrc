" vundle configuration

set nocompatible              " be iMproved, required
filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')
Plugin 'gmarik/Vundle.vim'

Plugin 'scrooloose/nerdtree'                " NERDTree
Plugin 'kien/ctrlp.vim'	                    " ctrlp	
Plugin 'Shougo/neocomplcache.vim'           " neocomplcache
Plugin 'scrooloose/syntastic'               " Syntactic
Plugin 'mileszs/ack.vim'                    " Ack.vim
Plugin 'majutsushi/tagbar'                  " Tagbar
Plugin 'bling/vim-airline'                  " Airline
Plugin 'milkypostman/vim-togglelist'
Plugin 'cespare/tlist'
Plugin 'vim-scripts/taglist.vim'
Plugin 'AutoComplPop'
Plugin 'airblade/vim-gitgutter'             " airline of git
Plugin 'tpope/vim-fugitive'                 " git command ex> Glog, Gstatus, Gmv
Plugin 'mattn/emmet-vim'                    " ctrl + y + , = html5 tag
Plugin 'terryma/vim-multiple-cursors'       " multiple cursors
Plugin 'DirDiff.vim'                        " DirDiff
Plugin 'git://github.com/leafgarland/typescript-vim.git' "TypeScript
Plugin 'junegunn/fzf', { 'dir': '~/.fzf', 'do': './install --all' }
"[cscope](http://cscope.sourceforge.net/)   " cscope 
"[ctags](http://ctags.sourceforge.net/)     " ctags 

Plugin 'othree/javascript-libraries-syntax.vim'

" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required
" To ignore plugin indent changes, instead use:
" filetype plugin on
"
" Brief help
" :PluginList          - list configured plugins
" :PluginInstall(!)    - install (update) plugins
" :PluginSearch(!) foo - search (or refresh cache first) for foo
" :PluginClean(!)      - confirm (or auto-approve) removal of unused plugins
"
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this line

"
" Written by Aron Griffis <agriffis@gentoo.org>
" Modified by Ryan Phillips <rphillips@gentoo.org>
" Modified some more by Ciaran McCreesh <ciaranm@gentoo.org>
" Added Redhat's vimrc info by Seemant Kulleen <seemant@gentoo.org>
"
" You can override any of these settings on a global basis via the
" "/etc/vim/vimrc.local" file, and on a per-user basis via "~/.vimrc". You may
" need to create these.
" 
" {{{ General settings
" The following are some sensible defaults for Vim for most users.
" We attempt to change as little as possible from Vim's defaults,
" deviating only where it makes sense
"
" Don't use Ex mode, use Q for formatting
map Q gq
"
" When doing tab completion, give the following files lower priority. You may
" wish to set 'wildignore' to completely ignore files, and 'wildmenu' to enable
" enhanced tab completion. These can be done in the user vimrc file.
set suffixes+=.info,.aux,.log,.dvi,.bbl,.out,.o,.lo
"
" When displaying line numbers, don't use an annoyingly wide number column. This
" doesn't enable line numbers -- :set number will do that. The value given is a
" minimum width to use for the number column, not a fixed size.
if v:version >= 700
  set numberwidth=3
endif
" }}}

" {{{ Modeline settings
" We don't allow modelines by default. See bug #14088 and bug #73715.
" If you're not concerned about these, you can enable them on a per-user
" basis by adding "set modeline" to your ~/.vimrc file.
set nomodeline
" }}}

" {{{ Locale settings
" Try to come up with some nice sane GUI fonts. Also try to set a sensible
" value for fileencodings based upon locale. These can all be overridden in
" the user vimrc file.
if v:lang =~? "^ko"
  set fileencodings=euc-kr
  set guifontset=-*-*-medium-r-normal--16-*-*-*-*-*-*-*
elseif v:lang =~? "^ja_JP"
  set fileencodings=euc-jp
  set guifontset=-misc-fixed-medium-r-normal--14-*-*-*-*-*-*-*
elseif v:lang =~? "^zh_TW"
  set fileencodings=big5
  set guifontset=-sony-fixed-medium-r-normal--16-150-75-75-c-80-iso8859-1,-taipei-fixed-medium-r-normal--16-150-75-75-c-160-big5-0
elseif v:lang =~? "^zh_CN"
  set fileencodings=gb2312
  set guifontset=*-r-*
endif

" If we have a BOM, always honour that rather than trying to guess.
if &fileencodings !~? "ucs-bom"
  set fileencodings^=ucs-bom
endif

" Always check for UTF-8 when trying to determine encodings.
if &fileencodings !~? "utf-8"
  " If we have to add this, the default encoding is not Unicode.
  " We use this fact later to revert to the default encoding in plaintext/empty
  " files.
  let g:added_fenc_utf8 = 1
  set fileencodings+=utf-8
endif

" Make sure we have a sane fallback for encoding detection
if &fileencodings !~? "default"
  set fileencodings+=default
endif
" }}}

" {{{ Terminal fixes
"if &term ==? "xterm"
"  set t_Sb=^[4%dm
"  set t_Sf=^[3%dm
"  set ttymouse=xterm2
"endif

if &term ==? "gnome" && has("eval")
  " Set useful keys that vim doesn't discover via termcap but are in the
  " builtin xterm termcap. See bug #122562. We use exec to avoid having to
  " include raw escapes in the file.
  exec "set <C-Left>=\eO5D"
  exec "set <C-Right>=\eO5C"
endif
" }}}

" {{{ Filetype plugin settings
" Enable plugin-provided filetype settings, but only if the ftplugin
" directory exists (which it won't on livecds, for example).
if isdirectory(expand("$VIMRUNTIME/ftplugin"))
  filetype plugin on

  " Uncomment the next line (or copy to your ~/.vimrc) for plugin-provided
  " indent settings. Some people don't like these, so we won't turn them on by
  " default.
  " filetype indent on
endif
" }}}

" {{{ Fix &shell, see bug #101665.
if "" == &shell
  if executable("/bin/bash")
    set shell=/bin/bash
  elseif executable("/bin/sh")
    set shell=/bin/sh
  endif
endif
"}}}

" {{{ Our default /bin/sh is bash, not ksh, so syntax highlighting for .sh
" files should default to bash. See :help sh-syntax and bug #101819.
if has("eval")
  let is_bash=1
endif
" }}}

" {{{ Autocommands
if has("autocmd")

augroup gentoo
  au!

  " Gentoo-specific settings for ebuilds.  These are the federally-mandated
  " required tab settings.  See the following for more information:
  " http://www.gentoo.org/proj/en/devrel/handbook/handbook.xml
  " Note that the rules below are very minimal and don't cover everything.
  " Better to emerge app-vim/gentoo-syntax, which provides full syntax,
  " filetype and indent settings for all things Gentoo.
  au BufRead,BufNewFile *.e{build,class} let is_bash=1|setfiletype sh
  au BufRead,BufNewFile *.e{build,class} set ts=4 sw=4 noexpandtab

  " In text files, limit the width of text to 78 characters, but be careful
  " that we don't override the user's setting.
  autocmd BufNewFile,BufRead *.txt
        \ if &tw == 0 && ! exists("g:leave_my_textwidth_alone") |
        \     setlocal textwidth=78 |
        \ endif

  " When editing a file, always jump to the last cursor position
  autocmd BufReadPost *
        \ if ! exists("g:leave_my_cursor_position_alone") |
        \     if line("'\"") > 0 && line ("'\"") <= line("$") |
        \         exe "normal g'\"" |
        \     endif |
        \ endif

  " When editing a crontab file, set backupcopy to yes rather than auto. See
  " :help crontab and bug #53437.
  autocmd FileType crontab set backupcopy=yes

  " If we previously detected that the default encoding is not UTF-8
  " (g:added_fenc_utf8), assume that a file with only ASCII characters (or no
  " characters at all) isn't a Unicode file, but is in the default encoding.
  " Except of course if a byte-order mark is in effect.
  autocmd BufReadPost *
        \ if exists("g:added_fenc_utf8") && &fileencoding == "utf-8" && 
        \    ! &bomb && search('[\x80-\xFF]','nw') == 0 && &modifiable |
        \       set fileencoding= |
        \ endif

augroup END

endif " has("autocmd")
" }}}

" {{{ vimrc.local
if filereadable("/etc/vim/vimrc.local")
  source /etc/vim/vimrc.local
endif
" }}}


scriptencoding = utf-8
set number
set expandtab
set sw=4 sts=4 ts=4 et
set nocompatible
set showmatch
set ci
set smartindent
set incsearch
set title
set hlsearch
set history=200
set mouse=a
set bs=2                " Allow backspacing over everything in insert mode
set autoindent
set ignorecase
set cindent
set ai                  " Always set auto-indenting on
set ruler               " Show the cursor position all the time
set viminfo='20,\"500   " Keep a .viminfo file.
set colorcolumn=95
set lcs=tab:>-          " Indicate Tab Space
set list
syntax on

filetype on
filetype plugin on
filetype plugin indent on

colorscheme 256-jungle

set csprg=/usr/local/bin/cscope
set csto=0
set cst
set nocst              " no using cscope tag
set nocsverb

let cscope_tag = 'cscope.out'
let ctags = 'tags'
let i = 1
while i < 15
let i += 1
if filereadable(cscope_tag) 
    exec 'cs add' cscope_tag
    let &tags=ctags
    break
else 
    let cscope_tag = '../' . cscope_tag
    let ctags = '../' . ctags
endif
endwhile

"find -iname "*.c"    > ./cscope.files
"find -iname "*.cpp" >> ./cscope.files
"find -iname "*.h"   >> ./cscope.files
"find -iname "*.hpp" >> ./cscope.files
"cscope -cb
"ctags --fields=+i -n -R -L ./cscope.files
"cqmakedb -s ./myproject.db -c ./cscope.out -t ./tags -p
set csverb

map <F3> <c-w><c-w>
map <F4> :Tlist<CR>
nmap <C-E> :NERDTreeToggle<CR>
let Tlist_Ctags_Cmd = "/usr/local/bin/ctags"
let Tlist_Inc_Winwidth = 0
let Tlist_Exit_OnlyWindow = 0

let Tlist_Auto_Open =0
let Tlit_Use_Right_Window = 1

nmap <F5> :SrcExplToggle<CR>
nmap <C-H> <C-W>h
nmap <C-J> <C-W>j
nmap <C-K> <C-W>k
nmap <C-L> <C-W>l
nmap <C-F>s :cs find s <C-R>=expand("<cword>")<CR><CR>
nmap <C-F>e :cs find e <C-R>=expand("<cword>")<CR><CR>
map <C-]> :tj <C-R>=expand("<cword>")<CR><CR>
map <C-F>f :cs find f 
map <C-F>z :FZF<CR>
imap <INSERT>` printf("[skchoi2][%s][%d] +++++++++++++++++++++++++++++++++  \n", __FUNCTION__,__LINE__);

let g:SrcExpl_winHeight = 8
let g:SrcExpl_refreshTime = 100
let g:SrcExpl_jumpKey = "<ENTER>"
let g:SrcExpl_gobackKey = "<SPACE>"
let g:SrcExpl_isUpdateTags = 0

let g:DirDiffExcludes = "CVS,*.class,*.exe,.*.swp,*.svn-base,*.o,*.d,*.so,*.svn"
let g:DirDiffWindowSize = 10

let NERDTreeWinPos = "left"

nmap <F8> : TrinityToggleAll<cr>

let g:netrw_browse_split=0
map <Char-27>t : Te<cr>
map <Char-27>n :tabn<cr>


nmap <Char-27>j : !echo %:p<cr>

let g:airline_powerline_fonts = 1

