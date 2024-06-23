#pragma once

#include <iostream>
#include <fstream>
#include <openssl/md5.h>
#include <string>
#include <sstream>

class ComputeMD5
{
public:
	ComputeMD5()  = default;

	void compute(const std::stringstream &buffer, unsigned char* md5_digest);

private:
	MD5_CTX ctx;
};