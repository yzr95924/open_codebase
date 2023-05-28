/**
 * @file crypto_bench.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief the main program for crypto bench
 * @version 0.1
 * @date 2023-05-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/crypto/crypto_util.h"

#define MODULE_ID "CryptoBench"
#define TEST_FILE_SIZE ((1ULL << 20) * 512)

void Usage()
{
    fprintf(stderr, "%s -c [cipher type] -h [hash type] "
        "-t [thread nums] -s [chunk size (KiB)]\n"
        "-c [cipher type]:\n"
        "\tAES-256-GCM: 0\n"
        "\tAES-128-GCM: 1\n"
        "\tAES-256-CFB: 2\n"
        "\tAES-128-CFB: 3\n"
        "\tAES-256-CBC: 4\n"
        "\tAES-128-CBC: 5\n"
        "\tAES-256-ECB: 6\n"
        "\tAES-128-ECB: 7\n"
        "\tAES-256-CTR: 8\n"
        "\tAES-128-CTR: 9\n"
        "-h [hash type]:\n"
        "\tSHA-256: 0\n"
        "\tMD5: 1\n"
        "\tSHA-1: 2\n", MODULE_ID);
}

int main(int argc, char *argv[])
{
    uint64_t chunk_size = 0;
    const char opt_str[] = "c:h:t:s:";
    int opt;
    ENCRYPT_TYPE_T cipher_type;
    HASH_TYPE_T hash_type;

    if (argc != sizeof(opt_str)) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_ID, "wrong argc num.\n");
        Usage();
        return RETURN_ERROR;
    }

    while ((opt = getopt(argc, argv, opt_str)) != -1) {
        switch (opt) {
            case 'c': {
                switch (atoi(optarg)) {
                    case AES_256_GCM: {
                        cipher_type = AES_256_GCM;
                        ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID,
                            "using AES-256-GCM.\n");
                        break;
                    }
                    case AES_128_GCM: {
                        cipher_type = AES_128_GCM;
                        ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID,
                            "using AES-128-GCM.\n");
                        break;
                    }
                    case AES_256_CFB: {
                        cipher_type = AES_256_CFB;
                        ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID,
                            "using AES-256-CFB.\n");
                        break;
                    }
                    case AES_128_CFB: {
                        cipher_type = AES_128_CFB;
                        ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID,
                            "using AES-128-CFB.\n");
                        break;
                    }
                    case AES_256_CBC: {
                        cipher_type = AES_256_CBC;
                        ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID,
                            "using AES-256-CBC.\n");
                        break;
                    }
                    case AES_128_CBC: {
                        cipher_type = AES_128_CBC;
                        ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID,
                            "using AES-128-CBC.\n");
                        break;
                    }
                    case AES_256_ECB: {
                        cipher_type = AES_256_ECB;
                        ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID,
                            "using AES-256-ECB.\n");
                        break;
                    }
                    case AES_128_ECB: {
                        cipher_type = AES_128_ECB;
                        ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID,
                            "using AES-128-ECB.\n");
                        break;
                    }
                    case AES_256_CTR: {
                        cipher_type = AES_256_CTR;
                        ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID,
                            "using AES-256-CTR.\n");
                        break;
                    }
                    case AES_128_CTR: {
                        cipher_type = AES_128_CTR;
                        ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID,
                            "using AES-128-CTR.\n");
                        break;
                    }
                    default: {
                        ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_ID,
                            "wrong cipher type.\n");
                        Usage();
                        return RETURN_ERROR;
                    }
                }
                break;
            }
            case 'h': {
                switch (atoi(optarg)) {
                    case SHA_256: {
                        hash_type = SHA_256;
                        ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID,
                            "using SHA-256.\n");
                        break;;
                    }
                    case MD5: {
                        hash_type = MD5;
                        ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID,
                            "using MD5.\n");
                        break;
                    }
                    case SHA_1: {
                        hash_type = SHA_1;
                        ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID,
                            "using SHA-1.\n");
                        break;
                    }
                    default: {
                        ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_ID,
                            "wrong hash type.\n");
                        Usage();
                        return RETURN_ERROR;
                    }
                }
                break;
            }
            case 's': {
                chunk_size = atoi(optarg) * 1024;
                if (chunk_size > TEST_FILE_SIZE) {
                    ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_ID,
                    "the input chunk size (%u) is higher than %u\n",
                        chunk_size, TEST_FILE_SIZE);
                    return RETURN_ERROR;
                }
                break;
            }
            case '?':
                ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_ID, "error optopt: %c\n", optopt);
                ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_ID, "error opterr: %d\n", opterr);
                Usage();
                return RETURN_ERROR;
        }
    }

    return RETURN_OK;
}
