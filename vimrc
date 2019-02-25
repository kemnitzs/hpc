execute pathogen#infect()
syntax on
filetype plugin indent on

let g:clang_c_options = '-std=gnu14'
let g:clang_cpp_options = '-std=c++14 -stdlib=libc++'
let g:ycm_confirm_extra_conf = 0

filetype plugin indent on     " required!

set shiftwidth=2
set softtabstop=2
set number

let g:ycm_key_list_select_completion = ['<C-n>', '<Down>']
let g:ycm_key_list_previous_completion = ['<C-p>', '<Up>']
let g:ycm_server_log_level = "debug"
let g:SuperTabDefaultCompletionType = '<C-n>'

" better key bindings for UltiSnipsExpandTrigger
let g:UltiSnipsExpandTrigger = "<tab>"
let g:UltiSnipsJumpForwardTrigger = "<tab>"
let g:UltiSnipsJumpBackwardTrigger = "<s-tab>"

let g:UltiSnipsEditSplit="horizontal"

set encoding=utf-8

syntax on
