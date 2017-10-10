#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include <openssl/aes.h>

void testaCorretude()
{
	unsigned char key[] = "essasenhaehfraca";
	AES_KEY aes_key;

	unsigned char claro[AES_BLOCK_SIZE * 2] = "Texto para teste";
	unsigned char cifrado[AES_BLOCK_SIZE * 2];

	AES_set_encrypt_key(key, 128, &aes_key);
	AES_ecb_encrypt(claro, cifrado, &aes_key, AES_ENCRYPT);

	for (int i=0; i<AES_BLOCK_SIZE; i++)
	{
        printf("%x ", cifrado[i]);
	}
    printf("\n");

    for (int i=0; i<AES_BLOCK_SIZE; i++)
	{
        printf("%c ", cifrado[i]);
	}
    printf("\n");

    for (int i=0; i<AES_BLOCK_SIZE; i++)
	{
		printf("%d ", cifrado[i]);
        if( ((int) cifrado[i]) == 243)
        {
        }
	}

    printf("\n");

    for (int i=0; i<AES_BLOCK_SIZE; i++)
	{
        printf("%d ", cifrado[i]);
	}
    printf("\n");
}

void print(unsigned char* buffer)
{
	for (int i=0; i<AES_BLOCK_SIZE; i++)
	{
        printf("%c ", buffer[i]);
	}
    printf("\n");
}

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
        printf("%d ", buffer[i]);
	}
    printf("\n");
}

int test()
{
	unsigned char claro[(AES_BLOCK_SIZE * 1) + 1] = "Texto para teste";
	print(claro);

	unsigned char cifrado[(AES_BLOCK_SIZE * 1) + 1];
	unsigned char key[17] = "essasenhaehfraca";
	AES_KEY aes_key;
	AES_set_encrypt_key(key, 128, &aes_key);
	AES_ecb_encrypt(claro, cifrado, &aes_key, AES_ENCRYPT);
	print(cifrado);

	unsigned char teste[(AES_BLOCK_SIZE * 1) + 1];
	unsigned char keytest[17] = "essasenhaehfraca";
	AES_KEY aes_keytest;
	AES_set_decrypt_key(keytest, 128, &aes_keytest);
	AES_ecb_encrypt(cifrado, teste, &aes_keytest, AES_DECRYPT);
	print(teste);
}

int verifica(unsigned char* teste, int mSIZE) 
{
	int encontrouCharErrado = 0;

	for (int i=0; i<mSIZE; i++)
	{
        for (int e=0; e<=31; e++)
        {
        	if (teste[i] == 9 || teste[i] == 10 || teste[i] == 13)
        	{
        		continue;
        	}
        	if (teste[i] == e) {
        		encontrouCharErrado = 1;
        		return -1;
        	}
        }
	}

	return 1;
}

void bruteForce()
{
	FILE *fp = fopen("results.txt", "w");

	
	int mSIZEkey = 17;


	/*
	int mSIZE = 17;
	unsigned char claro[mSIZE] = "Texto para téste";
	unsigned char cifrado[mSIZE];
	unsigned char key[17] = "Key2Group17";
	key[11] = 33;
	key[12] = 33;
	key[13] = 33;
	key[14] = 34;
	key[15] = 33;
	AES_KEY aes_key;
	AES_set_encrypt_key(key, 128, &aes_key);
	AES_ecb_encrypt(claro, cifrado, &aes_key, AES_ENCRYPT);
	*/


	int mSIZE = (AES_BLOCK_SIZE * 42) + 1;
	unsigned char cifrado[mSIZE] = "5D80B22B7AE8ECD2FE85DB34AF46436069F1959B24998C569078BDB9B137E7B7C098A1866273C219EAAF296B68EE224565A3D704BDEC51638A880002DC6188A97D007FD1D4F58C2794017272433F7235C31344841374F957485B39AA8D3DF4A2C6DE4332405BE51C065D38106840674C775C343D8068C5AEE95327B57DF0955C4C8B340B5C9848540DCD0494BAAB2ABBDC8D4D92105F757C02B6BB3189298BE172FF4D6B40435134FC677047C44D440C3D8D5E62FD8A2340085C93AFC53EF733FBA235553C89CCDFF3D478BAF467D3F15859643DF3CD2BFA74A561F8A8F822AE8FF5F3827BBA50AFC39CB2E390CAC23A2A9A291072E21186D5E144CAB7B3FE06EB0D68B27D5BD8E0A2EA37AD3AEC4F1E657264F53D53C45C81DFD9DAE9A8B1F3606E229B6F3DB0EC43949101110E7667AB33A862B82C5CB44694224099E2C8AA63704ACCDB22CDCE266B636CC400485C";



	AES_KEY aes_keytest;
	unsigned char keytest[17] = "Key2Group17";
	unsigned char teste[mSIZE];
	
	for(int i1=33; i1<=126; i1++)
	{
		printf("i1 = %d\n", i1);

		keytest[11] = (char) i1;

		for(int i2=33; i2<=126; i2++)
		{
			keytest[12] = (char) i2;

			for(int i3=33; i3<=126; i3++)
			{
				keytest[13] = (char) i3;

				for(int i4=33; i4<=126; i4++)
				{
					keytest[14] = (char) i4;

					for(int i5=33; i5<=126; i5++)
					{
						keytest[15] = (char) i5;

						AES_set_decrypt_key(keytest, 128, &aes_keytest);
						AES_ecb_encrypt(cifrado, teste, &aes_keytest, AES_DECRYPT);

						if (verifica(teste, mSIZE) > 0) 
						{
							fwrite(keytest, sizeof(char), mSIZEkey, fp);
							fwrite("\n", sizeof(char), 1, fp);
							fwrite(teste, sizeof(char), mSIZE, fp);
							fwrite("\n\n\n", sizeof(char), 3, fp);

							printf("\n\n\n---------------\n");
							printf("ACHOU!!!!\nKEY=%d %d %d %d %d\nTEXTO=\n", i1, i2, i3, i4, i5);
							print3(teste, mSIZE);
							print2(teste, mSIZE);
							printf("\n\n");
						}
					}
				}
			}
		}
	}
	fclose(fp);
}

void bruteForce2(int x)
{
	char filename[100];
	sprintf(filename, "results_%d.txt\0", x);

	FILE *fp = fopen(filename, "w");

	
	int mSIZEkey = 17;


	/*
	int mSIZE = 17;
	unsigned char claro[mSIZE] = "Texto para téste";
	unsigned char cifrado[mSIZE];
	unsigned char key[17] = "Key2Group17";
	key[11] = 33;
	key[12] = 33;
	key[13] = 33;
	key[14] = 34;
	key[15] = 33;
	AES_KEY aes_key;
	AES_set_encrypt_key(key, 128, &aes_key);
	AES_ecb_encrypt(claro, cifrado, &aes_key, AES_ENCRYPT);
	*/


	int mSIZE = (AES_BLOCK_SIZE * 42) + 1;
	unsigned char cifrado[mSIZE] = "5D80B22B7AE8ECD2FE85DB34AF46436069F1959B24998C569078BDB9B137E7B7C098A1866273C219EAAF296B68EE224565A3D704BDEC51638A880002DC6188A97D007FD1D4F58C2794017272433F7235C31344841374F957485B39AA8D3DF4A2C6DE4332405BE51C065D38106840674C775C343D8068C5AEE95327B57DF0955C4C8B340B5C9848540DCD0494BAAB2ABBDC8D4D92105F757C02B6BB3189298BE172FF4D6B40435134FC677047C44D440C3D8D5E62FD8A2340085C93AFC53EF733FBA235553C89CCDFF3D478BAF467D3F15859643DF3CD2BFA74A561F8A8F822AE8FF5F3827BBA50AFC39CB2E390CAC23A2A9A291072E21186D5E144CAB7B3FE06EB0D68B27D5BD8E0A2EA37AD3AEC4F1E657264F53D53C45C81DFD9DAE9A8B1F3606E229B6F3DB0EC43949101110E7667AB33A862B82C5CB44694224099E2C8AA63704ACCDB22CDCE266B636CC400485C";



	AES_KEY aes_keytest;
	unsigned char keytest[17] = "Key2Group17";
	unsigned char teste[mSIZE];
	
	//for(int i1=33; i1<=126; i1++)
	//{
	int i1 = x;

		printf("i1 = %d\n", i1);

		keytest[11] = (char) i1;

		for(int i2=33; i2<=126; i2++)
		{
			printf("  i2 = %d\n", i2);

			keytest[12] = (char) i2;

			for(int i3=33; i3<=126; i3++)
			{
				keytest[13] = (char) i3;

				for(int i4=33; i4<=126; i4++)
				{
					keytest[14] = (char) i4;

					for(int i5=33; i5<=126; i5++)
					{
						keytest[15] = (char) i5;

						AES_set_decrypt_key(keytest, 128, &aes_keytest);
						AES_ecb_encrypt(cifrado, teste, &aes_keytest, AES_DECRYPT);

						if (verifica(teste, mSIZE) > 0) 
						{
							fwrite(keytest, sizeof(char), mSIZEkey, fp);
							fwrite("\n", sizeof(char), 1, fp);
							fwrite(teste, sizeof(char), mSIZE, fp);
							fwrite("\n\n\n", sizeof(char), 3, fp);

							printf("\n\n\n---------------\n");
							printf("ACHOU!!!!\nKEY=%d %d %d %d %d\nTEXTO=\n", i1, i2, i3, i4, i5);
							print3(teste, mSIZE);
							print2(teste, mSIZE);
							printf("\n\n");
						}
					}
				}
			}
		}
	
	fclose(fp);
}

int main(int argc, char *argv[])
{
	printf("Hi\n");

	char *p;
	long conv = strtol(argv[1], &p, 10);
	int x = conv;

	// testaCorretude();
	bruteForce2(x);

    return 0;
}