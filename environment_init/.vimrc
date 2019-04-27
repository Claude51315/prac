syntax on
set hls
set number
set cursorline
set ic
set expandtab
set shiftwidth=4
set tabstop=4

" open file from last position 
if has("autocmd")
  au BufReadPost * if line("'\"") > 0 && line("'\"") <= line("$")
    \| exe "normal! g'\"" | endif
endif
