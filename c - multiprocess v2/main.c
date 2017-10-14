#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <openssl/aes.h>

const int SIZE_HISTOGRAM = 40;
long long histogram[SIZE_HISTOGRAM];

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

signed int verifica(unsigned char* str, int size)
{
	for (int i=0; i<size; i++)
	{
		if(str[i] > 31)
		{
			continue;
		}
		if (str[i] == 0 || str[i] == 9 || str[i] == 10 || str[i] == 13)
    	{
    		continue;
    	}
        for (unsigned char EE=1; EE<=31; EE++)
        {
        	if (str[i] == EE) {
        		return 0;
        	}
        }
	}
	return 1;
}

void bruteForce2(int x)
{
	int valids = 0;

	// file
	char filename[100];
	sprintf(filename, "results_%d.txt\0", x);
	printf("FILENAME: %s\n", filename);
	FILE *fp = fopen(filename, "w");

	// dado para descriptofrafar
	int NUM_BLOCKS = 21;
	int BLOCO_SIZE = AES_BLOCK_SIZE * NUM_BLOCKS;
	char bloco_dados_string[BLOCO_SIZE*2+1] = "5D80B22B7AE8ECD2FE85DB34AF46436069F1959B24998C569078BDB9B137E7B7C098A1866273C219EAAF296B68EE224565A3D704BDEC51638A880002DC6188A97D007FD1D4F58C2794017272433F7235C31344841374F957485B39AA8D3DF4A2C6DE4332405BE51C065D38106840674C775C343D8068C5AEE95327B57DF0955C4C8B340B5C9848540DCD0494BAAB2ABBDC8D4D92105F757C02B6BB3189298BE172FF4D6B40435134FC677047C44D440C3D8D5E62FD8A2340085C93AFC53EF733FBA235553C89CCDFF3D478BAF467D3F15859643DF3CD2BFA74A561F8A8F822AE8FF5F3827BBA50AFC39CB2E390CAC23A2A9A291072E21186D5E144CAB7B3FE06EB0D68B27D5BD8E0A2EA37AD3AEC4F1E657264F53D53C45C81DFD9DAE9A8B1F3606E229B6F3DB0EC43949101110E7667AB33A862B82C5CB44694224099E2C8AA63704ACCDB22CDCE266B636CC400485C";
	//char bloco_dados_string[BLOCO_SIZE*2+1] = "2BE715515012DBD550072853F84E54C308060B0000000000AA04AE0000000000";
	unsigned char bloco_dados[BLOCO_SIZE];
	char* pos = bloco_dados_string;
	for(int count = 0; count < BLOCO_SIZE; count++) {
        sscanf(pos, "%2hhx", &bloco_dados[count]);
        pos += 2;
    }

    // key para testar
    int KEY_SIZE = 16;
	unsigned char keytest[KEY_SIZE] = "Key2Group17";
	int i1 = x;	
	printf(".i1 = %d\n", i1);
	keytest[11] = (unsigned char) i1;
	for(int i2=32; i2<=127; i2++)
	{
		printf("  .i2 = %d - valids = %d\n", i2, valids);
		keytest[12] = (unsigned char) i2;
		for(int i3=32; i3<=127; i3++)
		{
			keytest[13] = (unsigned char) i3;
			for(int i4=32; i4<=127; i4++)
			{
				keytest[14] = (unsigned char) i4;
				for(int i5=32; i5<=127; i5++)
				{
					keytest[15] = (unsigned char) i5;

					unsigned char bloco_claro[16];

					int passou = 1;
					for (int z=0; z<NUM_BLOCKS; z++)
					{
						unsigned char bloco[16];

						for(int b=0; b<16; b++) 
						{
							bloco[b] = bloco_dados[z*16+b];
						}

						// testa a key gerada
						AES_KEY aes_keytest;
						

						AES_set_decrypt_key(keytest, 128, &aes_keytest);

						AES_ecb_encrypt(bloco, bloco_claro, &aes_keytest, AES_DECRYPT);
				
						signed int mVerifica = verifica(bloco_claro, 16);

						if(mVerifica == 0) {
							passou = 0;
							break;
						}
					}

					if(passou == 1) {

							fwrite(keytest, sizeof(unsigned char), KEY_SIZE, fp);
							fwrite("\n", sizeof(unsigned char), 1, fp);
							fwrite(bloco_claro, sizeof(unsigned char), 16, fp);
							fwrite("\n\n\n", sizeof(unsigned char), 3, fp);

							printf("\n\n------------------------------ ACHOU:\n\n");
							printf("KEY=%d %d %d %d %d \nTEXTO= \n", i1, i2, i3, i4, i5);
							print3(bloco_claro, 16);
							printf("\n\n");
							print2(bloco_claro, 16);
							printf("\n\n");
							printf("\n\n------------------------------ fim\n\n");

							getchar();
						
					}
				}
			}
		}
	}

	// statistic
	/*
	for (int i=0; i<SIZE_HISTOGRAM; i++)
	{
		char texto[100];
		for(int y=0;y<100;y++) {
			texto[y] = 0;
		}
		sprintf(texto,"histogram[%d]=%ld\n",i,histogram[i]);
		fwrite(texto, sizeof(char), 100, fp);
		fwrite("\n", sizeof(unsigned char), 1, fp);
	}
	*/

	fclose(fp);
}

void ACHEI()
{
	// texto criptografado 21 blocos de 16
	int NUM_BLOCKS = 21;
	int BLOCO_SIZE = AES_BLOCK_SIZE * NUM_BLOCKS;
	char bloco_dados_string[BLOCO_SIZE*2+1] = "5D80B22B7AE8ECD2FE85DB34AF46436069F1959B24998C569078BDB9B137E7B7C098A1866273C219EAAF296B68EE224565A3D704BDEC51638A880002DC6188A97D007FD1D4F58C2794017272433F7235C31344841374F957485B39AA8D3DF4A2C6DE4332405BE51C065D38106840674C775C343D8068C5AEE95327B57DF0955C4C8B340B5C9848540DCD0494BAAB2ABBDC8D4D92105F757C02B6BB3189298BE172FF4D6B40435134FC677047C44D440C3D8D5E62FD8A2340085C93AFC53EF733FBA235553C89CCDFF3D478BAF467D3F15859643DF3CD2BFA74A561F8A8F822AE8FF5F3827BBA50AFC39CB2E390CAC23A2A9A291072E21186D5E144CAB7B3FE06EB0D68B27D5BD8E0A2EA37AD3AEC4F1E657264F53D53C45C81DFD9DAE9A8B1F3606E229B6F3DB0EC43949101110E7667AB33A862B82C5CB44694224099E2C8AA63704ACCDB22CDCE266B636CC400485C";
	unsigned char bloco_dados[BLOCO_SIZE];
	char* pos = bloco_dados_string;
	for(int count = 0; count < BLOCO_SIZE; count++) {
        sscanf(pos, "%2hhx", &bloco_dados[count]);
        pos += 2;
    }


    // key para testar
    int KEY_SIZE = 16;
	unsigned char keytest[KEY_SIZE] = "Key2Group17";

	keytest[11] = 87;
	keytest[12] = 68;
	keytest[13] = 45;
	keytest[14] = 38;
	keytest[15] = 104;


	for (int z=0; z<NUM_BLOCKS; z++)
	{
		unsigned char bloco[16];
		unsigned char bloco_claro[16];

		for(int b=0; b<16; b++) 
		{
			bloco[b] = bloco_dados[z*16+b];
		}

		// testa a key gerada
		AES_KEY aes_keytest;
		AES_set_decrypt_key(keytest, 128, &aes_keytest);
		AES_ecb_encrypt(bloco, bloco_claro, &aes_keytest, AES_DECRYPT);

		for(int b=0; b<16; b++) 
		{
			printf("%c", bloco_claro[b]);
		}
		printf("\n");
	}

}

int main(int argc, char *argv[])
{
	//char *p; long conv = strtol(argv[1], &p, 10); int x = conv; bruteForce2(x);
	ACHEI();
    return 0;
}