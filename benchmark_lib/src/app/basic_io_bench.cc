/**
 * @file basic_io_bench.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief basic I/O benchmark
 * @version 0.1
 * @date 2023-06-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/basic_io/basic_io_w.h"

#define MODULE_ID "BasicIOBench"

using namespace std;

typedef struct {
    uint32_t idx;
    bool is_buffer;
} INPUT_PARAM_T;

typedef struct {
    double run_time;
} OUTPUT_PARAM_T;

void Usage()
{
    fprintf(stdout, "%s -t [thread num] -w [use buffer]\n"
        "\t use buffer: == 0: without, > 0 with",
        MODULE_ID);
    return;
}

void BasicWriteOneThread(INPUT_PARAM_T *in_param, OUTPUT_PARAM_T *out_param)
{
    BasicWriteUtil *writeUtil = new BasicWriteUtil();
    struct timeval stime;
    struct timeval etime;
    pid_t thread_id = gettid();

    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "start thread_id: %d\n",
        thread_id);
    out_param->run_time = 0;

    gettimeofday(&stime, NULL);
    if (in_param->is_buffer) {
        writeUtil->WriteWithBuf(in_param->idx);
    } else {
        writeUtil->WriteWithoutBuf(in_param->idx);
    }
    gettimeofday(&etime, NULL);
    out_param->run_time += ZUORU_GetTimeDiff(stime, etime);

    writeUtil->RemoveTestFile(in_param->idx, in_param->is_buffer);

    delete writeUtil;
}

int main(int argc, char *argv[])
{
    int opt;
    uint64_t thread_num = 0;
    bool use_buffer = false;
    std::thread* cur_thread = NULL;
    vector<thread*> thread_list;

    const char opt_str[] = "t:w:";
    if (argc != sizeof(opt_str)) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_ID, "wrong argc num.\n");
        Usage();
        return RETURN_ERROR;
    }

    while ((opt = getopt(argc, argv, opt_str)) != -1) {
        switch (opt) {
            case 'w':
                if (atoi(optarg) > 0) {
                    use_buffer = true;
                }
                break;
            case 't':
                thread_num = atoi(optarg);
                break;
            case '?':
                ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_ID, "error optopt: %c\n", optopt);
                ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_ID, "error opterrL %d\n", opterr);
                Usage();
                return RETURN_ERROR;
        }
    }

    INPUT_PARAM_T *in_param_array = (INPUT_PARAM_T*)malloc(thread_num *
        sizeof(INPUT_PARAM_T));
    OUTPUT_PARAM_T *out_param_array = (OUTPUT_PARAM_T*)malloc(thread_num *
        sizeof(OUTPUT_PARAM_T));
    double total_running_time = 0;

    for (size_t idx = 0; idx < thread_num; idx++) {
        in_param_array[idx].idx = idx;
        in_param_array[idx].is_buffer = use_buffer;
        cur_thread = new std::thread(BasicWriteOneThread, &in_param_array[idx],
            &out_param_array[idx]);
        thread_list.push_back(cur_thread);
    }

    for (size_t idx = 0; idx < thread_num; idx++) {
        thread_list[idx]->join();
        delete thread_list[idx];
    }

    for (size_t idx = 0; idx < thread_num; idx++) {
        total_running_time += out_param_array[idx].run_time;
    }

    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "total time: %lf\n",
        total_running_time);
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "speed: %lf (MiB/s)\n",
        thread_num * WRITE_ONCE_BYTE_SIZE * WRITE_IO_COUNT / MiB_2_B /
            total_running_time);

    free(in_param_array);
    free(out_param_array);
    return 0;
}
