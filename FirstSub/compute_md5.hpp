#include <iostream>
#include <fstream>
#include <openssl/md5.h>
#include <string>
#include <sstream>

#pragma comment(lib, "ssleay32MDd.lib")
#pragma comment(lib, "libeay32MDd.lib")

class ComputeMD5
{
public:
	ComputeMD5()  = default;

	void compute(const std::stringstream &buffer, unsigned char* md5_digest);

private:
	MD5_CTX ctx;
};