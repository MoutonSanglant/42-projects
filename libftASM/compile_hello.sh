#nasm="~/.brew/bin/nasm"
#$nasm -f macho64 -o hello.o test.s

nasm=nasm

mkdir -p obj

### 64-bit version

#$nasm -f elf64 -o hello.o elf/test.s
#ld -s -dynamic-linker /lib64/ld-linux-x86-64.so.2 -o hello hello.o -lc
#gcc -nostdlib -lc hello.o -o hello

# tiny
$nasm -f elf64 -o obj/hello.o src/elf/tiny.s
gcc -nostdlib obj/hello.o -o hello

#/usr/lib/crt1.o -lc


## 32-bit version

$nasm -f elf -o obj/hello_32.o src/elf/test_32.s
#ld -o hello_32 hello_32.o -lc
#gcc -m32 -nostdlib -lc hello_32.o -o hello_32
gcc -m32 -nostdlib obj/hello_32.o -o hello_32

# strip executable

strip -s hello
strip -s hello_32
