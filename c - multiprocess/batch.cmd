ECHO OFF
ECHO Hi batch
g++ main.c -o main.exe -I ./include/ ./static/libcrypto.a ./static/libssl.a
for /l %%x in (33, 1, 127) do (
   start main.exe %%x
)
PAUSE