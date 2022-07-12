all:
gcc main.c lexico.c sintatico.c sp.c -o compilador.exe

run:
./compilador.exe