#include "common.hpp"

ComputeMD5 md5_computer;
ThreadPool thread_pool(1);

bool is_to_send = true;

std::mutex send_mutex;
//是否需要发送数据


double MB = std::pow(2,20);

long global_counter = -1;
long recieve_counter = 0;
long file_len;

bool first_flag = true;