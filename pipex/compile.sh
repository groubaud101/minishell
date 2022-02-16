gcc *.c -L. -lft -I./libft/include

echo './a.out infile "ls -la" "grep a.out" outfile\n'
./a.out infile "ls -la" "grep a.out" outfile

echo "cat outfile :"
cat outfile

echo '\nrm a.out outfile'
rm -rf a.out outfile
