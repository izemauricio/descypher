#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include <openssl/aes.h>

void print2(unsigned char* buffer, int size)
{
	for (int i=0; i<size; i++)
	{
        printf("%lc", buffer[i]);
	}
    printf("\n");
}

void print3(unsigned char* buffer, int size)
{
	for (int i=0; i<size; i++)
	{
        printf("%x ", buffer[i]);
	}
    printf("\n");
}

int testaCorretude()
{
	unsigned char bloco_dados_string[(AES_BLOCK_SIZE * 1) + 1] = "Texto para teste";
	unsigned char bloco_dados[AES_BLOCK_SIZE];
	unsigned char bloco_cifrado[AES_BLOCK_SIZE];
	unsigned char bloco_claro[AES_BLOCK_SIZE];

	int BLOCO_SIZE = AES_BLOCK_SIZE;

	for(int i=0; i<BLOCO_SIZE; i++)
	{
		bloco_dados[i] = bloco_dados_string[i];
	}
	print3(bloco_dados, AES_BLOCK_SIZE);

	AES_KEY aes_key;
	unsigned char key[16] = "essasenhaehfrac";
	key[15] = 'a';
	AES_set_encrypt_key(key, 128, &aes_key);

	AES_ecb_encrypt(bloco_dados, bloco_cifrado, &aes_key, AES_ENCRYPT);	
	print3(bloco_cifrado, AES_BLOCK_SIZE);

	AES_KEY aes_keytest;
	unsigned char keytest[16] = "essasenhaehfrac";
	keytest[15] = 'a';
	AES_set_decrypt_key(keytest, 128, &aes_keytest);

	AES_ecb_encrypt(bloco_cifrado, bloco_claro, &aes_keytest, AES_DECRYPT);
	print3(bloco_claro, AES_BLOCK_SIZE);
}

unsigned char verifica(unsigned char* str, int size)
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

	int BLOCO_SIZE = AES_BLOCK_SIZE * 21;
	char bloco_dados_string[BLOCO_SIZE*2+1] = "5D80B22B7AE8ECD2FE85DB34AF46436069F1959B24998C569078BDB9B137E7B7C098A1866273C219EAAF296B68EE224565A3D704BDEC51638A880002DC6188A97D007FD1D4F58C2794017272433F7235C31344841374F957485B39AA8D3DF4A2C6DE4332405BE51C065D38106840674C775C343D8068C5AEE95327B57DF0955C4C8B340B5C9848540DCD0494BAAB2ABBDC8D4D92105F757C02B6BB3189298BE172FF4D6B40435134FC677047C44D440C3D8D5E62FD8A2340085C93AFC53EF733FBA235553C89CCDFF3D478BAF467D3F15859643DF3CD2BFA74A561F8A8F822AE8FF5F3827BBA50AFC39CB2E390CAC23A2A9A291072E21186D5E144CAB7B3FE06EB0D68B27D5BD8E0A2EA37AD3AEC4F1E657264F53D53C45C81DFD9DAE9A8B1F3606E229B6F3DB0EC43949101110E7667AB33A862B82C5CB44694224099E2C8AA63704ACCDB22CDCE266B636CC400485C";
	char* pos = bloco_dados_string;
	unsigned char bloco_dados[BLOCO_SIZE];
	for(int count = 0; count < BLOCO_SIZE; count++) {
        sscanf(pos, "%2hhx", &bloco_dados[count]);
        pos += 2;
    }

    int KEY_SIZE = 16;
	AES_KEY aes_keytest;
	unsigned char keytest[KEY_SIZE] = "Key2Group17";
	
	int i1 = x;	
	printf("i1 = %d\n", i1);
	keytest[11] = (unsigned char) i1;

		for(int i2=33; i2<=126; i2++)
		{
			printf("  i2 = %d\n", i2);
			keytest[12] = (unsigned char) i2;
			for(int i3=33; i3<=126; i3++)
			{
				keytest[13] = (unsigned char) i3;
				for(int i4=33; i4<=126; i4++)
				{
					keytest[14] = (unsigned char) i4;
					for(int i5=33; i5<=126; i5++)
					{
						keytest[15] = (unsigned char) i5;

						unsigned char bloco_claro[BLOCO_SIZE];
						AES_set_decrypt_key(keytest, 128, &aes_keytest);
						AES_ecb_encrypt(bloco_dados, bloco_claro, &aes_keytest, AES_DECRYPT);
						if (verifica(bloco_claro, BLOCO_SIZE) > 0)
						{
							fwrite(keytest, sizeof(unsigned char), KEY_SIZE, fp);
							fwrite("\n", sizeof(unsigned char), 1, fp);

							fwrite(bloco_claro, sizeof(unsigned char), BLOCO_SIZE, fp);
							fwrite("\n\n\n", sizeof(unsigned char), 3, fp);

							printf("\n\n---\n\n");
							printf("ACHOU!\nKEY=%d %d %d %d %d \nTEXTO= \n", i1, i2, i3, i4, i5);
							print3(bloco_claro, BLOCO_SIZE);
							print2(bloco_claro, BLOCO_SIZE);
							printf("\n\n");
							getchar();
						}
					}
				}
			}
		}
	//}

	fclose(fp);
}

void test()
{
	int BLOCO_SIZE = AES_BLOCK_SIZE;
	char bloco_dados_string[BLOCO_SIZE*2+1] = "5D80B22B7AE8ECD2FE85DB34AF464360";
	unsigned char bloco_dados[BLOCO_SIZE];
	char* pos = bloco_dados_string;
	for(int count = 0; count < BLOCO_SIZE; count++) {
        sscanf(pos, "%2hhx", &bloco_dados[count]);
        printf("%x = %d\n",bloco_dados[count],bloco_dados[count]);
        pos += 2;
    }
	//print3(bloco_dados, BLOCO_SIZE);
	//getchar();
}

int main(int argc, char *argv[])
{
	printf("Hi\n");
	test();
	//testaCorretude();
	char *p; long conv = strtol(argv[1], &p, 10); int x = conv; bruteForce2(x);
    return 0;
}