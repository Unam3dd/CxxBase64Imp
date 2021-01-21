#include "base64.hxx"


void make_decoding_table(void)
{
    DECODING_TABLE = (unsigned char *)malloc(0x100);

    for (int i = 0; i < 64; i++)
        DECODING_TABLE[(unsigned char)BASE64_TABLE[i]] = i;
}

void free_decoding_table(void)
{
    free(DECODING_TABLE);
}

uint64_t Base64::get_base64_encoded_size(string str)
{
    return (((str.size())+2 / 3) << 2);
}

long long Base64::get_base64_decoded_size(string str)
{
    return ((str.size() % 4 != 0) ? -1 : ((str.size()) >> 2) * 3);
}

string Base64::encode(string str)
{
    uint64_t size = Base64::get_base64_encoded_size(str);
    string encoded = "";
    uint32_t bytes[3] = {0};
    uint64_t size_of_str = str.size();
    uint32_t sum = 0;
    uint32_t padding[3] = {0, 2, 1};

    for (int i = 0; i < size_of_str; i += 3) {
        bytes[0] = (i < size_of_str) ? (unsigned char) str.at(i) : 0; 
        bytes[1] = (i+1 < size_of_str) ? (unsigned char) str.at(i+1) : 0;
        bytes[2] = (i+2 < size_of_str) ? (unsigned char) str.at(i+2) : 0;

        sum = (bytes[0] << 0x10) | (bytes[1] << 0x8) | (bytes[2]);

        encoded += BASE64_TABLE[ ((sum) >> 0x12) & 0x3F ];
        encoded += BASE64_TABLE[ ((sum) >> 0xc) & 0x3F ];
        encoded += BASE64_TABLE[ ((sum) >> 0x6) & 0x3F ];
        encoded += BASE64_TABLE[ (sum) & 0x3F];
    }

    // calculating the padding

    for (int i = 0; i < padding[size_of_str % 3]; i++) {
        encoded.pop_back();
        encoded.push_back('=');
    }
    

    return (encoded);
}

string Base64::decode(string str)
{
    string decoded = "";
    size_t size = str.size();
    uint32_t bytes[4] = {0};
    uint32_t sum = 0;
    
    if (size % 4 != 0)
        return (decoded);
    
    while (str.at(size - 1) == '=') {
        str.pop_back();
        size--;
    }

    if (DECODING_TABLE_IS_NULL)
        make_decoding_table();

    for (int i = 0; i < size;) {

        bytes[0] = (i < size) ? DECODING_TABLE[str.at(i++)] : 0;
        bytes[1] = (i < size) ? DECODING_TABLE[str.at(i++)] : 0;
        bytes[2] = (i < size) ? DECODING_TABLE[str.at(i++)] : 0;
        bytes[3] = (i < size) ? DECODING_TABLE[str.at(i++)] : 0;

        sum = (bytes[0] << 0x12) | (bytes[1] << 0xc) | (bytes[2] << 0x6) | (bytes[3]);

        decoded += (sum >> 0x10) & 0xFF;
        decoded += (sum >> 0x8) & 0xFF;
        decoded += (sum) & 0xFF;
    }

    free_decoding_table();
    
    return (decoded);
}