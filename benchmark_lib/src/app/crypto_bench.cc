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
#include "../../../common_include/my_util.h"
#include "../../../common_include/c_my_data_struct.h"

#define MODULE_ID "CryptoBench"
#define TEST_FILE_SIZE ((1ULL << 20) * 512)

typedef struct {
    uint64_t chunk_size;
    ENCRYPT_TYPE_T cipher_type;
    HASH_TYPE_T hash_type;
} INPUT_PARAM_T;

typedef struct {
    double enc_time;
    double dec_time;
    double hash_time;
} OUTPUT_PARAM_T;

void Usage()
{
    fprintf(stdout, "%s -c [cipher type] -h [hash type] "
        "-t [thread num] -s [chunk size (KiB)]\n"
        "-c [cipher type]:\n"
        "\tAES-256-GCM: 0\n"
        "\tAES-128-GCM: 1\n"
        "\tAES-256-CFB: 2\n"
        "\tAES-128-CFB: 3\n"
        "\tAES-256-CBC: 4\n"
        "\tAES-128-CBC: 5\n"
        "\tAES-256-CTR: 6\n"
        "\tAES-128-CTR: 7\n"
        "\tAES-256-ECB: 8\n"
        "\tAES-128-ECB: 9\n"
        "-h [hash type]:\n"
        "\tSHA-256: 0\n"
        "\tMD5: 1\n"
        "\tSHA-1: 2\n", MODULE_ID);
    return;
}

void CryptoTestOneThead(INPUT_PARAM_T *in_param, OUTPUT_PARAM_T *out_param)
{
    uint64_t chunk_size = in_param->chunk_size;
    ENCRYPT_TYPE_T cipher_type = in_param->cipher_type;
    HASH_TYPE_T hash_type = in_param->hash_type;
    pid_t thread_id = gettid();
    struct timeval start_time;
    struct timeval end_time;
    CryptoUtil *crypto_util;
    uint8_t iv[CRYPTO_BLOCK_SIZE] = { 1 };
    uint8_t hash[MAX_HASH_SIZE] = { 0 };
    uint8_t key[MAX_HASH_SIZE] = { 2 };
    uint8_t *input_buf = NULL;
    uint8_t *output_buf = NULL;
    uint8_t *tmp_data_buf = NULL;
    EVP_CIPHER_CTX *cipher_ctx = EVP_CIPHER_CTX_new();
    EVP_MD_CTX *md_ctx = EVP_MD_CTX_new();
    uint32_t enc_chunk_size = 0;

    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "start thread_id: %d\n", thread_id);

    crypto_util = new CryptoUtil(cipher_type, hash_type);
    input_buf = (uint8_t*)malloc(chunk_size);
    output_buf = (uint8_t*)malloc(chunk_size + CRYPTO_BLOCK_SIZE);
    tmp_data_buf = (uint8_t*)malloc(chunk_size);
    int rand_dev_fd = open("/dev/urandom", O_RDONLY);

    out_param->enc_time = 0;
    out_param->dec_time = 0;
    out_param->hash_time = 0;

    for (size_t idx = 0; idx < (TEST_FILE_SIZE / chunk_size); idx++) {
        read(rand_dev_fd, input_buf, chunk_size);

        gettimeofday(&start_time, NULL);
        enc_chunk_size = crypto_util->EncryptWithKeyIV(cipher_ctx, input_buf,
            chunk_size, key, iv, output_buf);
        gettimeofday(&end_time, NULL);
        out_param->enc_time += ZUORU_GetTimeDiff(start_time, end_time);

        gettimeofday(&start_time, NULL);
        crypto_util->GenerateHash(md_ctx, input_buf, chunk_size,
            hash);
        gettimeofday(&end_time, NULL);
        out_param->hash_time += ZUORU_GetTimeDiff(start_time, end_time);

        gettimeofday(&start_time, NULL);
        enc_chunk_size = crypto_util->DecryptWithKeyIV(cipher_ctx, output_buf,
            enc_chunk_size, key, iv, tmp_data_buf);
        gettimeofday(&end_time, NULL);
        out_param->dec_time += ZUORU_GetTimeDiff(start_time, end_time);
    }
    close(rand_dev_fd);

    delete crypto_util;
    free(input_buf);
    free(output_buf);
    free(tmp_data_buf);
    EVP_CIPHER_CTX_free(cipher_ctx);
    EVP_MD_CTX_free(md_ctx);

    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "finish thread_id: %d\n", thread_id);
    return;
}

int main(int argc, char *argv[])
{
    fprintf(stderr, MY_DATA_STRUCT_LOG_FMT "queue is full\n",
        MY_DATA_STRUCT_LOG_MSG);
    uint64_t chunk_size = 0;
    uint64_t thread_num = 0;
    const char opt_str[] = "c:h:t:s:";
    int opt;
    ENCRYPT_TYPE_T cipher_type;
    HASH_TYPE_T hash_type;
    vector<std::thread*> thread_list;
    std::thread* cur_thread = NULL;

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
            case 't':
                thread_num = atoi(optarg);
                break;
            case '?':
                ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_ID, "error optopt: %c\n", optopt);
                ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_ID, "error opterr: %d\n", opterr);
                Usage();
                return RETURN_ERROR;
        }
    }

    INPUT_PARAM_T in_param = { 0 };
    in_param.chunk_size = chunk_size;
    in_param.cipher_type = cipher_type;
    in_param.hash_type = hash_type;
    OUTPUT_PARAM_T *out_param_array = (OUTPUT_PARAM_T*)malloc(thread_num *
        sizeof(OUTPUT_PARAM_T));
    double total_enc_time = 0;
    double total_dec_time = 0;
    double total_hash_time = 0;

    for (size_t idx = 0; idx < thread_num; idx++) {
        cur_thread = new std::thread(CryptoTestOneThead, &in_param,
            &out_param_array[idx]);
        thread_list.push_back(cur_thread);
    }

    for (size_t idx = 0; idx < thread_num; idx++) {
        thread_list[idx]->join();
        delete thread_list[idx];
    }

    for (size_t idx = 0; idx < thread_num; idx++) {
        total_enc_time += out_param_array[idx].enc_time;
        total_dec_time += out_param_array[idx].dec_time;
        total_hash_time += out_param_array[idx].hash_time;
    }

    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "enc time: %lf\n",
        total_enc_time);
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "dec time: %lf\n",
        total_dec_time);
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "hash time: %lf\n",
        total_hash_time);

    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "enc speed: %lf (MiB/s)\n",
        TEST_FILE_SIZE * thread_num / MiB_2_B / total_enc_time);
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "dec speed: %lf (MiB/s)\n",
        TEST_FILE_SIZE * thread_num / MiB_2_B / total_dec_time);
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "hash speed: %lf (MiB/s)\n",
        TEST_FILE_SIZE * thread_num / MiB_2_B / total_hash_time);

    free(out_param_array);
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "total mem usage: %llu (KiB)\n",
        ZUORU_GetMemUsage());

    return RETURN_OK;
}
