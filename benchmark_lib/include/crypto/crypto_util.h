/**
 * @file crypto_util.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief define interfaces of crypto module (hash&encryption)
 * @version 0.1
 * @date 2019-12-19
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPEN_NOTE_CRYPTO_UTIL_H
#define OPEN_NOTE_CRYPTO_UTIL_H

#include <openssl/evp.h>
#include <openssl/crypto.h>
#include <openssl/err.h>
#include "../../../common_include/cpp_c/cpp_include.h"
#include "../../../common_include/cpp_c/define_const.h"
#include "../../../common_include/cpp_c/logger.h"

using namespace std;

static const unsigned char gcm_aad[] = {
    0x4d, 0x23, 0xc3, 0xce, 0xc3, 0x34, 0xb4, 0x9b, 0xdb, 0x37, 0x0c, 0x43,
    0x7f, 0xec, 0x78, 0xde
};

#ifndef RETURN_LIB_CRYPTO_SUCC
#define RETURN_LIB_CRYPTO_SUCC 1
#endif

enum ENCRYPT_TYPE_T {
    AES_256_GCM = 0,
    AES_128_GCM,
    AES_256_CFB,
    AES_128_CFB,
    AES_256_CBC,
    AES_128_CBC,
    AES_256_CTR,
    AES_128_CTR,
    AES_256_ECB,
    AES_128_ECB,
};

enum HASH_TYPE_T {
    SHA_256 = 0,
    SHA_1,
    MD5,
};

class CryptoUtil {
    private:
        ENCRYPT_TYPE_T cipher_type_;
        HASH_TYPE_T hash_type_;
        int pad_flag_ = 1; // enable padding

        // update the pKey
        EVP_PKEY *p_key_;
    public:
        /**
         * @brief Construct a new CryptoUtil object
         *
         * @param cipher_type the cipher type
         * @param hash_type the hash type
         */
        CryptoUtil(ENCRYPT_TYPE_T cipher_type, HASH_TYPE_T hash_type);

        /**
         * @brief Destroy the Crypto Primitive object
         *
         */
        ~CryptoUtil();

        /**
         * @brief generate the hash
         *
         * @param ctx the hasher ctx
         * @param data the input data buffer
         * @param size the input data size
         * @param hash the output hash <return>
         */
        void GenerateHash(EVP_MD_CTX *ctx, uint8_t *data, uint32_t size, uint8_t *hash);

        /**
         * @brief encrypt the data with the key and iv
         *
         * @param ctx the cipher ctx
         * @param data the input data buffer
         * @param size the input data size
         * @param key the enc key
         * @param iv the input iv
         * @param cipher the output cipher <return>
         * @return uint32_t the cipher size
         */
        uint32_t EncryptWithKeyIV(EVP_CIPHER_CTX *ctx, uint8_t *data, uint32_t size,
            uint8_t *key, uint8_t *iv, uint8_t *cipher);

        /**
         * @brief decrypt the cipher with the key and iv
         *
         * @param ctx the cipher ctx
         * @param cipher the input cipher buffer
         * @param size the input cipher size
         * @param key the dec key
         * @param iv the input iv
         * @param data the output data <return>
         * @return uint32_t the data size
         */
        uint32_t DecryptWithKeyIV(EVP_CIPHER_CTX *ctx, uint8_t *cipher, const int size,
            uint8_t *key, uint8_t *iv, uint8_t *data);

        /**
         * @brief generate the hmac of the data
         *
         * @param ctx the hasher ctx
         * @param data the input data buffer
         * @param size the input data size
         * @param p_key the private key
         * @param hmac the output hmac <return>
         */
        void GenerateHMAC(EVP_MD_CTX *ctx, uint8_t *data, const int size,
            EVP_PKEY *p_key, uint8_t *hmac);
};

#endif
