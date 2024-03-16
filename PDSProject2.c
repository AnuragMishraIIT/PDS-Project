#include <stdio.h>
#include <string.h>

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

const unsigned char roundconstants[11] = // Anurag Mishra
    {
        0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1B,0x36
    };

// Anurag Mishra
void shiftRows(unsigned char array[][4][4], int num) // A numx4x4 array is received
{
    int k, i, j, index;
    char temp[3];

    for (k = 0; k < num; k++) // This loop runs for each 4x4 block.
    {
        for (i = 0; i < 4; i++) // This loop takes account of the row being worked upon
        {
            for (j = 0; j < i; j++)
            {
                temp[j] = array[k][i][j];
            }

            for (j = 0; j < 4 - i; j++)     
            {
                array[k][i][j] = array[k][i][j + i];
            }

            for (index = 0, j = 4 - i; j < 4; j++, index++)
            {
                array[k][i][j] = temp[index];
            }
        }
    }
}

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

		for (j = 0; j < 4; j++)
		{
			array[i][j] = array[i][j + i];
		}

		index = 0;
		for (j = 4 - i; j < 4; j++, index++)
		{
			array[i][j] = temp[index];
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
        int Y = temp_vector[i] % 16;
        int X = temp_vector[i] / 16;

        temp_vector[i] = sbox[X][Y];
    }
}

void subBytes(unsigned char temp_vector[4][4]) //Anurag Mishra
{
	for(int row=0;row<4;row++)
	{
		for(int col=0;col<4;col++) //Hexadecimal digit of the form 0x(XY)
		{
		int Y=temp_vector[row][col]%16; 
		int X=temp_vector[row][col]/16;
		temp_vector[row][col]=sbox[X][Y];
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

unsigned char multiply(unsigned char a, unsigned char b) {
    unsigned char p = 0;
    unsigned char high_bit_set;
    for (int i = 0; i < 8; ++i) {
        if (b & 1) {
            p ^= a;
        }
        high_bit_set = a & 0x80;
        a <<= 1;
        if (high_bit_set) {
            a ^= 0x1B; // 0x1B is the irreducible polynomial in GF(2^8)
        }
        b >>= 1;
    }
    return p;
}

void mixcolumns(unsigned char state[4][4]) {
    unsigned char matrix[4][4] = 
    {
        {0x02, 0x03, 0x01, 0x01},
        {0x01, 0x02, 0x03, 0x01},
        {0x01, 0x01, 0x02, 0x03},
        {0x03, 0x01, 0x01, 0x02}
    };

    unsigned char result[4][4];

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result[i][j] = multiply(matrix[i][0], state[0][j]) ^
                           multiply(matrix[i][1], state[1][j]) ^
                           multiply(matrix[i][2], state[2][j]) ^
                           multiply(matrix[i][3], state[3][j]);
        }
    }
    // Copy result back to state matrix
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            state[i][j] = result[i][j];
        }
    }
}

void addRoundKey(unsigned char ptext[4][4], unsigned char roundKey[4][4]) 
{
	for (int col = 0; col < 4; col++) {
		for (int row = 0; row < 4; row++)
		{
			ptext[row][col] ^= roundKey[row][col];
		}
	}
}
int main()
{
    int num = 3;
    unsigned char roundkeys[11][4][4]; // Stores the 11 4x4 round keys
    unsigned char cipherkey[4][4] =    // Initial key or secret key or cipher key to make round keys
        {
            {0xAB, 0x5F, 0x72, 0xE3},
            {0x94, 0x2D, 0x8A, 0x6C},
            {0x3E, 0x11, 0x9B, 0xD8},
            {0x7A, 0x45, 0xF2, 0x81}
        };
    keySchedule(roundkeys, cipherkey);

    char* txt="HopThisisgoingtoworkperfectlynow";
	int blocks=strlen(txt)/16 ;
	unsigned char ptext[blocks][4][4];
	
	for(int i=0,c=0;i<blocks;i++)
	{
		for(int row=0;row<4;row++)
		{
			for(int col=0;col<4;col++)
			{
				ptext[i][row][col] = txt[c++];
			}
		}
	}

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
	
	for(int current_block=0;current_block<blocks;current_block++)
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
	for (int k = 0; k < blocks; k++)
	{
		printf("\nArray %d:\n\n", k + 1);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				printf("%x ", ptext[k][i][j]);
			printf("\n");
		}
		printf("\n");
	}
    return 0;
}
