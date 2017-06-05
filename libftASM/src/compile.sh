~/.brew/bin/nasm -f macho64 -o hello.o test.s
ld -e _main -o hello hello.o /usr/lib/crt1.o -lc
