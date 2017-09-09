#nasm="~/.brew/bin/nasm"
#$nasm -f macho64 -o hello.o test.s

nasm=nasm

mkdir -p obj

nasm -f elf64 -o obj/play.o src/elf/play.s
gcc -nostdlib -lc obj/play.o -o play

strip -s play
