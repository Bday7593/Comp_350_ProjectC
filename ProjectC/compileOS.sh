dd if=/dev/zero of=diskc.img bs=512 count=1000
nasm bootload.asm
dd if=bootload of=diskc.img bs=512 count=1 conv=notrunc

bcc -ansi -c -o kernel_c.o  kernel.c
as86 kernel.asm -o kernel_asm.o
ld86 -o kernel -d kernel_c.o kernel_asm.o
gcc -o loadFile loadFile.c
./loadFile kernel
./loadFile message.txt

#projectC part 2 load a program and execute it.
bcc -ansi -c -o tstpr1.o tstpr1.c
as86 -o userlib.o userlib.asm
ld86 -d -o tstpr1 tstpr1.o userlib.o
./loadFile tstpr1

#projectC part 3 terminate program system call
bcc -ansi -c -o tstpr2.o tstpr2.c
ld86 -d -o tstpr2 tstpr2.o userlib.o
./loadFile tstpr2

#projectc part 4 the shell - making you own user program.
bcc -ansi -c -o shell_c.o  shell.c
ld86 -d -o shell shell_c.o userlib.o
./loadFile shell