set makeprg=g++\ -Wextra\ -Wall\ -std=c++20\ -o\ %:r\ %
map <Leader>s :vsp %.in<CR>
map <Leader>c :w<CR>:make<CR>
map <Leader>r :!%:r < %.in<CR>
