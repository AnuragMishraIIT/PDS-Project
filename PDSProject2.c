#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const unsigned char sbox[16][16] = // Tushar Jawane
    //     0     1     2    3      4     5     6     7     8     9     a     b     c    d      e     f
    {
        {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76}, // 0
        {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0}, // 1
        {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15}, // 2
        {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75}, // 3
        {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84}, // 4
        {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf}, // 5
        {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8}, // 6
        {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2}, // 7
        {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73}, // 8
        {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb}, // 9
        {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79}, // a
        {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08}, // b
        {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a}, // c
        {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e}, // d
        {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf}, // e
        {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}  // f
};

const unsigned char inSbox[16][16] =
    //     0     1     2    3      4     5     6     7     8     9     a     b     c    d      e     f
    {
        {0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb}, // 0
        {0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb}, // 1
        {0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e}, // 2
        {0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25}, // 3
        {0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92}, // 4
        {0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84}, // 5
        {0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06}, // 6
        {0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b}, // 7
        {0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73}, // 8
        {0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e}, // 9
        {0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b}, // a
        {0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4}, // b
        {0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f}, // c
        {0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef}, // d
        {0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61}, // e
        {0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d}  // f
};

const unsigned char roundconstants[11] = // Anurag Mishra
    {
        0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36
    };

// Anurag Mishra

void shiftRows2(unsigned char array[4][4]) // A numx4x4 array is received
{
    int k, i, j, index;
    char temp[3];

    for (i = 0; i < 4; i++) // This loop takes account of the row being worked upon
    {
        for (j = 0; j < i; j++)
        {
            temp[j] = array[i][j];
        }

        for (j = 0; j < 4 - i; j++)
        {
            array[i][j] = array[i][j + i];
        }

        for (index = 0, j = 4 - i; j < 4; j++, index++)
        {

            array[i][j] = temp[index];
        }
    }
}

void inv_ShiftRows(unsigned char array[4][4]) // A numx4x4 array is received
{
    int i, j, index;
    char temp[3];
    for (i = 0; i < 4; i++) // This loop takes account of the row being worked upon
    {
        for (index = 0, j = 4 - i; j < 4; index++, j++)
        {
            temp[index] = array[i][j];
        }

        for (j = 3 - i; j >=0; j--)
        {
            array[i][j + i] = array[i][j];
        }

        for (j =0; j < i; j++)
        {
            array[i][j] = temp[j];
        }
    }
    
}

void rotword(unsigned char temp_vector[]) // Anurag Mishra
{
    int temp = temp_vector[0];
    for (int i = 0; i < 3; i++)
    {
        temp_vector[i] = temp_vector[i + 1];
    }
    temp_vector[3] = temp;
}

void subword(unsigned char temp_vector[]) // Anurag Mishra
{
    for (int i = 0; i < 4; i++) // Hexadecimal digit of the form 0x(XY)
    {
        int Y = temp_vector[i] & ((1 << 4) - 1);
        int X = (temp_vector[i]) >> 4;

        temp_vector[i] = sbox[X][Y];
    }
}

void subBytes(unsigned char temp_vector[4][4]) // Anurag Mishra
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++) // Hexadecimal digit of the form 0x(XY)
        {
            int Y = temp_vector[row][col] & ((1 << 4) - 1);
            int X = temp_vector[row][col] >> 4;
            temp_vector[row][col] = sbox[X][Y];
        }
    }
}

void inv_subBytes(unsigned char temp_vector[4][4]) // Anurag Mishra
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++) // Hexadecimal digit of the form 0x(XY)
        {
            int Y = temp_vector[row][col] & ((1 << 4) - 1);
            int X = temp_vector[row][col] >> 4;
            temp_vector[row][col] = inSbox[X][Y];
        }
    }
}

void roundConst(unsigned char temp_vector[], int keynum) // Anurag Mishra
{
    temp_vector[0] = temp_vector[0] ^ roundconstants[keynum];
}

void finalRoundKey(unsigned char temp_vector[], unsigned char r_keys[][4][4], int keynum) // Anurag Mishra
{
    for (int i = 0; i < 4; i++)
    {
        r_keys[keynum][i][0] = temp_vector[i] ^ r_keys[keynum - 1][i][0];
    }

    for (int j = 1; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            r_keys[keynum][i][j] = r_keys[keynum][i][j - 1] ^ r_keys[keynum - 1][i][j];
        }
    }
}

void keySchedule(unsigned char r_keys[][4][4], unsigned char ciph_key[4][4]) // Anurag Mishra
{
    unsigned char temp_vect[4]; // a 4x1 column vector to be intialized with 4th column of kth round key
    for (int i = 0; i < 4; i++) // Assigning Cipher key to the zeroth key
    {
        for (int j = 0; j < 4; j++)
        {
            r_keys[0][i][j] = ciph_key[i][j];
        }
    }

    for (int k = 1; k < 11; k++) // Generating kth key where k>0
    {
        for (int i = 0; i < 4; i++)
        {
            temp_vect[i] = r_keys[k - 1][i][3]; // Key k>0 is derived from previous round key k-1
        }

        rotword(temp_vect);
        subword(temp_vect);
        roundConst(temp_vect, k);
        finalRoundKey(temp_vect, r_keys, k);
    }
}
/*
unsigned char multiply(unsigned char a, unsigned char b)
{ // Note: Bits numbering starts from the right to the left from 0 to 7 (since there are only 8 bits in char)
    unsigned char p = 0;
    unsigned char high_bit_set;
    for (int i = 0; i < 8; i++)
    {
        if ((b & 1) != 0)
        {
            p ^= a;
        }
        high_bit_set = a & 0x80; // Checks if the 7th bit is on or off for 'a'

        a <<= 1; // Soon 'b' will be right shifted to cancel effects in polynomial multiplication. Old 7th bit is removed.

        if (high_bit_set != 0) // If 7th bit of old 'a' (Or the 8th bit of new 'a') was (is) on.
        {
            a ^= 0x1B; // 0x1B is the irreducible polynomial in GF(2^8)
            // 0x1B is equivalent to x^8 + x^4 + x^3 + x + 1
            // Toggles the values corresponding to the 4th,3rd,1st and 0th bits (Which is irreducible polynomial theorem itself)
        }
        b >>= 1; // Cancels effect of shifting of 'a' in polynomial multiplication
    }
    return p;
}*/


unsigned char multiply(unsigned char a, unsigned char b)
{
    unsigned short int temp_multiply=0;//Stores temporary multiplication of a and b in 16 bits

    for(int i=0;i<8;i++) //Traverses 8 bits of 'a'
    {
        for(int j=0;j<8;j++) //Traverses 8 bits of 'b'
        {
            if(((a&(1<<i))==(1<<i))&&((b&(1<<j))==(1<<j)))
            temp_multiply=temp_multiply^(1<<(i+j));
        }
    }
    unsigned short int irreducible_poly=0x1B;
    for(int k=8;k<15;k++)
    {   
        if((temp_multiply&(1<<k))==(1<<k))
        {
            temp_multiply=temp_multiply^irreducible_poly;
        }
        irreducible_poly=irreducible_poly<<1;
    }
    unsigned char multiply=temp_multiply&0xFF; //Extracts the last 8 bits
    return (multiply);
}

void mixcolumns(unsigned char state[4][4])
{
    unsigned char matrix[4][4] =
        {
            {0x02, 0x03, 0x01, 0x01},
            {0x01, 0x02, 0x03, 0x01},
            {0x01, 0x01, 0x02, 0x03},
            {0x03, 0x01, 0x01, 0x02}};

    unsigned char result[4][4];

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            result[i][j] = multiply(matrix[i][0], state[0][j]) ^
                           multiply(matrix[i][1], state[1][j]) ^
                           multiply(matrix[i][2], state[2][j]) ^
                           multiply(matrix[i][3], state[3][j]);
        }
    }
    // Copy result back to state matrix
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            state[i][j] = result[i][j];
        }
    }
}

void inv_MixColumns(unsigned char state[4][4])
{
    unsigned char matrix[4][4] =
        {
            {0x0e, 0x0b, 0x0d, 0x09},
            {0x09, 0x0e, 0x0b, 0x0d},
            {0x0d, 0x09, 0x0e, 0x0b},
            {0x0b, 0x0d, 0x09, 0x0e}};

    unsigned char result[4][4];

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            result[i][j] = multiply(matrix[i][0], state[0][j]) ^
                           multiply(matrix[i][1], state[1][j]) ^
                           multiply(matrix[i][2], state[2][j]) ^
                           multiply(matrix[i][3], state[3][j]);
        }
    }
    // Copy result back to state matrix
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            state[i][j] = result[i][j];
        }
    }
}


void addRoundKey(unsigned char ptext[4][4], unsigned char roundKey[4][4])
{
    for (int col = 0; col < 4; col++)
    {
        for (int row = 0; row < 4; row++)
        {
            ptext[row][col] ^= roundKey[row][col];
        }
    }
}

void block_generate(int block, char txt[], unsigned char array[][4][4])
{   
    int flag=0; //Checks if we have started padding
    for (int i = 0, c = 0; i < block; i++)
    {
        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {   
                if(txt[c]=='\0'||flag==1)
                {
                    flag=1;//Padding
                    array[i][row][col] = ' ';
                }
                else
                {
                array[i][row][col] = txt[c];
                }
                c++;
            }
        }
    }
}

void inverse_Cypher(char *txt,unsigned char roundkeys[][4][4])
{

    int size=strlen(txt);
    int blocks=((size%16)?(size/16+1):(size/16));
    unsigned char encrypted_text[blocks][4][4];

    //now fill the 3d array with the encrypted text
    block_generate(blocks,txt,encrypted_text);

    //Printing the blocks containing the encrypted text
    for (int k = 0; k < blocks; k++)
	{
		printf("\nEncrypted block %d:\n\n", k + 1);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				printf("%c ", encrypted_text[k][i][j]);
			printf("\n"); 
		}
		printf("\n");
	}

    //beginning decryption process here

    for(int current_block=0;current_block<blocks;current_block++)
	{
		//encrypted_text is the 3d matrix having the different blocks
		addRoundKey(encrypted_text[current_block], roundkeys[10]);
		// Main rounds
		for (int round = 9; round > 0; round--)
		{
            inv_ShiftRows(encrypted_text[current_block]);
            inv_subBytes(encrypted_text[current_block]);
			addRoundKey(encrypted_text[current_block], roundkeys[round]);
            inv_MixColumns(encrypted_text[current_block]);
		}

		// Final round
		inv_ShiftRows(encrypted_text[current_block]);
        inv_subBytes(encrypted_text[current_block]);
		addRoundKey(encrypted_text[current_block], roundkeys[0]);
	}

    //Printing the blocks containing the decrypted text
    printf("Decrypted text:\n");
    for (int k = 0; k < blocks; k++)
    {
        printf("\nArray %d:\n\n", k + 1);
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                printf("%c ", encrypted_text[k][i][j]);
            printf("\n");
        }
        printf("\n");
    }
}

void encrypt_cypher(char *txt,unsigned char roundkeys[][4][4])
{
    int size=strlen(txt);
    int blocks=((size%16)?(size/16+1):(size/16));
    unsigned char ptext[blocks][4][4];

    //now fill the 3d array with the encrypted text
    block_generate(blocks,txt,ptext);

    //Printing the blocks containing the plain text
    for (int k = 0; k < blocks; k++)
    {
        printf("\nArray %d:\n\n", k + 1);
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                printf("%c ", ptext[k][i][j]);
            printf("\n");
        }
        printf("\n");
    }

    //Encryption process starts here
    for (int current_block = 0; current_block < blocks; current_block++)
    {
        addRoundKey(ptext[current_block], roundkeys[0]);
        // Main rounds
        for (int round = 1; round < 10; round++)
        {
            subBytes(ptext[current_block]);
            shiftRows2(ptext[current_block]);
            mixcolumns(ptext[current_block]);
            addRoundKey(ptext[current_block], roundkeys[round]);
        }

        // Final round
        subBytes(ptext[current_block]);
        shiftRows2(ptext[current_block]);
        addRoundKey(ptext[current_block], roundkeys[10]);
    }   


    //Print the blocks containing the encrypted text
    printf("Encrypted text:\n");
    for (int k = 0; k < blocks; k++)
    {
        printf("\nArray %d:\n\n", k + 1);
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                printf("%c ", ptext[k][i][j]);
            printf("\n");
        }
        printf("\n");
    }
}


int main()
{
    unsigned char roundkeys[11][4][4]; // Stores the 11 4x4 round keys
    char cipher_key[] = "abcdefghijklmnop";
    unsigned char cipher_key_final[4][4];

    int c = 0;
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            cipher_key_final[row][col] = cipher_key[c++];
        }
    }

    keySchedule(roundkeys, cipher_key_final);


    //###################################################################################################
    //#####################   ENCRYPTION HERE    ########################################################
    //###################################################################################################
    //Input string
    printf("Enter string to be encrypted:\n");
    char *str = (char *)malloc(4096 * sizeof(char));
    scanf("%[^\n]s", str);
    str = realloc(str, (strlen(str) + 1) * sizeof(char));
    
    //CALLING ENCRYPTION FUNCTION
    encrypt_cypher(str,roundkeys);
    free(str);

    //###################################################################################################
    //#####################   DECRYPTION HERE    ########################################################
    //###################################################################################################

    printf("Enter encrypted string:");
    getchar();
    char *txt=(char*)malloc(4096*sizeof(char));
    scanf("%[^\n]s",txt);
    txt=realloc(txt,(strlen(txt)+1)*sizeof(char));

    //CALLING DECRYPTION FUNCTION
    inverse_Cypher(txt,roundkeys);
    free(txt);

    return 0;
}

