ECHO OFF
ECHO Hi batch
g++ main.c -o main.exe -I ./include/ ./static/libcrypto.a ./static/libssl.a
main.exe 69
ECHO Bye batch
PAUSE