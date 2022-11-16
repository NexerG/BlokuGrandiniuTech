#include "sha256.h"
#include "ShaInline.h"

string Sha256(string zodis)
{
    vector<unsigned char> hash(picosha2::k_digest_size);
    picosha2::hash256(zodis.begin(), zodis.end(), hash.begin(), hash.end());

    string hex_str = picosha2::bytes_to_hex_string(hash.begin(), hash.end());
    return hex_str;
}
