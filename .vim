<<<<<<< Updated upstream
set makeprg=g++\ -Wextra\ -Wall\ -std=c++20\ -o\ %:r\ %
map <Leader>s :vsp %.in<CR>
map <Leader>c :w<CR>:make<CR>
map <Leader>r :!./%:r < ./%.in<CR>
=======
set makeprg=./build.bat
noremap <Leader>c :make<CR>
noremap <Leader>s :vsp input.txt<CR>
noremap <Leader>v :vsp output.txt<CR>
>>>>>>> Stashed changes
