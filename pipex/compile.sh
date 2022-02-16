gcc *.c -L. -lft -I./libft/include

echo './a.out infile "ls -la" "grep a.out" outfile\n'
./a.out infile "ls -la" "grep a.out" outfile

echo "cat outfile :"
cat outfile
