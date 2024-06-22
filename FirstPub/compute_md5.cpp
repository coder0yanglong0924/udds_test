#include "compute_md5.hpp"

void ComputeMD5::compute(const std::stringstream &buffer, unsigned char* md5_digest)
{

    MD5_Init(&ctx);

	std::string str = buffer.str();

	MD5_Update(&ctx,str.c_str(), str.size());

	MD5_Final(md5_digest, &ctx);

	return;
}