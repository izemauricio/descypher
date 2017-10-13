ECHO OFF
ECHO Hi batch
g++ main.c -o main.exe -I ./include/ ./static/libcrypto.a ./static/libssl.a
main.exe
ECHO Bye batch
PAUSE