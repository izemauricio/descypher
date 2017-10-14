#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <openssl/aes.h>

void print(unsigned char* buffer, int size)
{
	for (int i=0; i<size; i++)
	{
        printf("%02X", buffer[i]);
	}
    printf("\n");
    for (int i=0; i<size; i++)
	{
        printf("%03d ", buffer[i]);
	}
	printf("\n");
	for (int i=0; i<size; i++)
	{
        printf("%c ", buffer[i]);
	}
    printf("\n\n\n");
}

int testaCorretude()
{
	int BLOCO_SIZE = AES_BLOCK_SIZE*2;

	unsigned char bloco_dados_string[BLOCO_SIZE + 1] = "Texto para testeTexto para teste";
	unsigned char bloco_dados[BLOCO_SIZE];
	unsigned char bloco_cifrado[BLOCO_SIZE];
	unsigned char bloco_claro[BLOCO_SIZE];

	// Char to byte
	for(int i=0; i<BLOCO_SIZE; i++)
	{
		bloco_dados[i] = bloco_dados_string[i];
	}
	printf("\nBLOCO_DADO\n");
	print(bloco_dados, BLOCO_SIZE);

	// Chave para encriptar
	AES_KEY aes_key;
	unsigned char key[16] = "Key2Group17AbCd";
	key[15] = 'a';
	AES_set_encrypt_key(key, 128, &aes_key);

	// Encripta
	AES_ecb_encrypt(bloco_dados, bloco_cifrado, &aes_key, AES_ENCRYPT);	
	printf("\nBLOCO_CRIPTOGRAFADO\n");
	print(bloco_cifrado, BLOCO_SIZE);

	// Chave para descriptografar
	AES_KEY aes_keytest;
	unsigned char keytest[16] = "Key2Group17AbCd";
	keytest[15] = 'a';
	AES_set_decrypt_key(keytest, 128, &aes_keytest);

	// Descripta
	AES_ecb_encrypt(bloco_cifrado, bloco_claro, &aes_keytest, AES_DECRYPT);
	printf("\nBLOCO_CLARO\n");
	print(bloco_claro, BLOCO_SIZE);
}

signed int verifica(unsigned char* str, int size)
{
	for (int i=0; i<size; i++)
	{
		if (str[i] == 0 || str[i] == 9 || str[i] == 10 || str[i] == 13)
    	{
    		continue; // go to next letter
    	}
        for (unsigned char EE=1; EE<=31; EE++)
        {
        	if (str[i] == EE) {
        		return (-EE);
        	}
        }
	}
	return 1;
}

void bruteForce2(int x)
{
	printf("AES_BLOCK_SIZE: %d\n", AES_BLOCK_SIZE);

	char filename[100];
	sprintf(filename, "results_%d.txt\0", x);
	printf("FILENAME: %s\n", filename);
	FILE *fp = fopen(filename, "w");

	int BLOCO_SIZE = AES_BLOCK_SIZE * 1;
	char bloco_dados_string[BLOCO_SIZE*2+1] = "A506A19333F306AC2C62CBE931963AE7";
	char* pos = bloco_dados_string;
	unsigned char bloco_dados[BLOCO_SIZE];
	for(int count = 0; count < BLOCO_SIZE; count++) {
        sscanf(pos, "%2hhx", &bloco_dados[count]);
        pos += 2;
    }

    int KEY_SIZE = 16;
	
	unsigned char keytest[KEY_SIZE] = "essasenhaehfrac";
	keytest[15] = 'a';

	for (int i='a'; i<'z'; i++) {
		keytest[14] = i;
		AES_KEY aes_keytest;
		unsigned char bloco_claro[BLOCO_SIZE];
		AES_set_decrypt_key(keytest, 128, &aes_keytest);
		AES_ecb_encrypt(bloco_dados, bloco_claro, &aes_keytest, AES_DECRYPT);

		printf("i=%c\n",i);
		print(bloco_claro, BLOCO_SIZE);

		int r = verifica(bloco_claro, BLOCO_SIZE);
		if(r > 0) {
			printf("verifica MAIOR=%d\n", r);
		} else {
			printf("verifica MENOR=%d\n", r);
		}

		getchar();
	}

	fclose(fp);
}

int main(int argc, char *argv[])
{
	printf("Hi\n");
	//test();
	testaCorretude();
	//char *p; long conv = strtol(argv[1], &p, 10); int x = conv; bruteForce2(x);
	char k[16] = "Key2Group17AbCd";
	k[15] = 'a';
	for (int i=0; i<16; i++)
	{
		printf("%c", k[i]);
	}
	printf("\n");
	for (int i=0; i<16; i++)
	{
		printf("%d ", k[i]);
	}
	printf("\n");
    return 0;
}