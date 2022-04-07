# gcc *.c -L. -lft -I./libft/include

# echo './a.out "ls -la | grep user | grep 4096 > outfile\n'
# ./a.out "ls -la_|_grep user_|_grep 4096_>_outfile"

# echo "cat outfile :"
# cat outfile

# echo '\nrm a.out outfile'
# rm -rf a.out outfile

gcc *.c -L. -lft -I./libft/include

echo './a.out "ls -la | grep user | grep 4096\n'
./a.out "ls -la_|_grep user_|_grep 4096"

echo '\nrm a.out'
rm -rf a.out