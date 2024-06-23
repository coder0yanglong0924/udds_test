#include "common.hpp"

ComputeMD5 md5_computer;
ThreadPool thread_pool(1);

bool is_to_send = false;

std::mutex send_mutex;
//是否需要发送数据


double MB = std::pow(2,20);

long global_counter = -1;
long recieve_counter = 0;
long file_len;

bool first_flag = true;
int communite_counter = -1;

std::chrono::time_point<std::chrono::steady_clock> start;
std::chrono::time_point<std::chrono::steady_clock> end_;