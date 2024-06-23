#ifndef COMMON_HPP
#define COMMON_HPP

#include "compute_md5.hpp"
#include "threadpool.h"
#include <mutex>
#include <cmath>

extern ComputeMD5 md5_computer;
extern ThreadPool thread_pool;

extern bool is_to_send;

extern std::mutex send_mutex;
//是否需要发送数据


extern double MB;

extern long global_counter;
extern long recieve_counter;
extern long file_len;

extern bool first_flag;

#endif