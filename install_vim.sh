#!/bin/bash
mkdir -p ~/.vim/autoload ~/.vim/bundle && \
    curl -LSso ~/.vim/autoload/pathogen.vim https://tpo.pe/pathogen.vim

cp vimrc $HOME.vimrc

cd $HOME.vim/bundle && \
    git clone --depth=1 https://github.com/Valloric/YouCompleteMe.git && \
    git clone --depth=1 https://github.com/SirVer/ultisnips.git && \
    git clone --depth=1 https://github.com/vim-jp/cpp-vim.git && \
    git clone --depth=1 https://github.com/rhysd/vim-clang-format.git && \
    git clone --depth=1 https://github.com/realincubus/vim-snippets.git && \
    git clone --depth=1 https://github.com/ervandew/supertab.git
 
RUN cd $HOME/.vim/bundle/YouCompleteMe/ && \
    git submodule update --init --recursive 
    #./install.py --clangd-completer


