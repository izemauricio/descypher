#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <openssl/aes.h>

inline unsigned char verifica(unsigned char* str, int size)
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

DWORD WINAPI bruteForce3(LPVOID arg)
{
	int x = *((int*)arg);

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
	keytest[11] = (unsigned char) i1;
	for(int i2=33; i2<=126; i2++)
	{
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

					int retorno = verifica(bloco_claro, BLOCO_SIZE);

					if (retorno > 0)
					{
						fwrite(keytest, sizeof(unsigned char), KEY_SIZE, fp);
						fwrite("\n", sizeof(unsigned char), 1, fp);
						fwrite(bloco_claro, sizeof(unsigned char), BLOCO_SIZE, fp);
						fwrite("\n\n\n", sizeof(unsigned char), 3, fp);
					}
				}
			}
		}
	}

	fclose(fp);
}

int main()
{
	HANDLE thread[128-33];
	int argthread[128-33];

	printf("Hi\n");
	for(int i=33; i<128; i++)
	{
		argthread[i] = i;
		thread[i] = CreateThread(NULL, 0, bruteForce3, &(argthread[i]), 0, NULL);
	}
	for(int i=33; i<128; i++)
	{
		WaitForSingleObject(thread[i], INFINITE);
	}
	printf("Bye\n");
    return 0;
}