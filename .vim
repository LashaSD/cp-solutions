set makeprg=clang++\ -g\ -std=c++20\ -o\ build\sol.exe\ sol.cpp

noremap <Leader>c :make<CR>
noremap <Leader>s :vsp input.txt<CR>
noremap <Leader>v :vsp output.txt<CR>
noremap <Leader>b :vsp error.txt<CR>
