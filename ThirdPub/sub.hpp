#ifndef SUB_HPP
#define SUB_HPP

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>

#include <string>
#include <iomanip>

/* IDL_TypeSupport.h中包含所有依赖的头文件 */
#include "IDL_TypeSupport.h"


extern "C" int subscriber_main(int domainId, int sample_count);

#endif