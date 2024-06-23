#ifndef PUB_HPP
#define PUB_HPP

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>

#include <string>

#include <ctime>     
#include <iomanip>
#include <cmath>

#include "IDL_TypeSupport.h"

#include "compute_md5.hpp"
#include "threadpool.h"

extern "C" int publisher_main(int domainId, int sample_count,int string_lenth);

#endif