Yes, You can use gcc to compile your asm code. Use -c for compilation like this:
gcc -c file.S -o file.o

This will give object code file named file.o. To invoke linker perform following after above command:
gcc file.o -o file
