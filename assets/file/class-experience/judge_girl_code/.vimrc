:set nu
:set ai
:set tabstop=4
:set shiftwidth=4
:set mouse=a
:set ruler
:inoremap ( ()<Esc>i
:inoremap {<CR> {<CR>}<Esc>ko
:inoremap {{ {}<Esc>i
set hlsearch
hi Search cterm=reverse ctermbg=none ctermfg=none
filetype indent on

set bg=dark
"color evening
hi LineNr cterm=bold ctermfg=DarkGrey ctermbg=NONE
hi CursorLineNr cterm=bold ctermfg=Green ctermbg=NONE
syntax enable


