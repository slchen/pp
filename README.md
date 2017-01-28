[![Issues](https://img.shields.io/github/issues/slchen/pp.svg)](https://github.com/slchen/pp/issues)

# pp
simple C preprocessor  library

# test commnad
gcc -E pp.h > test.h && sed -i 's/#/\/\//g' test.h && gcc -Wall -O2 -o a.out test.c && ./a.out
