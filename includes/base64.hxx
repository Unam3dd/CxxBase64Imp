#pragma once
#include <iostream>
#include <cstdint>

using namespace std;

#define DECODING_TABLE_IS_NULL (DECODING_TABLE == NULL)

static char BASE64_TABLE[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};

static unsigned char *DECODING_TABLE = NULL;

void make_decoding_table(void);
void free_decoding_table(void);

class Base64
{
    public:
        string encode(string str);
        string decode(string str);
        uint64_t get_base64_encoded_size(string str);
        long long get_base64_decoded_size(string str);
};