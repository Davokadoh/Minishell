#!/bin/bash
G=$(tput setaf 2)
Y=$(tput setaf 3)

make;
rm -f file2;
echo $G"bash"
bash -c 'echo salut >file2 | cat file2'
cat file2
rm -f file2;
echo $Y"msh"
./minishell -c 'echo salut >file2 | cat file2'
cat file2
rm -f file2;
