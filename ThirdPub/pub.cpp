/**********************************************************
*****************发布端程序publisher.cpp********************
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>

#include <string>
#include <cstdlib>  
#include <ctime>     
#include <iomanip>
#include <cmath>

/* IDL_TypeSupport.h中包含所有依赖的头文件 */
#include "IDL_TypeSupport.h"

#include "compute_md5.hpp"
#include "threadpool.h"

ThreadPool threadpool(1);

ComputeMD5 md5_computer;
long send_counter = 0;

const double MB = std::pow(2,20);

// 生成单个随机字符
char getRandomChar() {
    int randomIndex = rand() % 26;  // 生成0到25之间的随机数
    char randomChar = 'a' + randomIndex;
    return randomChar;
}

// 生成随机字符串
string generateRandomString(int length) {
    string randomString;
    for (int i = 0; i < length; ++i) {
        randomString += getRandomChar();
    }
    return randomString;
}

/* 删除所有实体 */
static int publisher_shutdown(DomainParticipant *participant)
{
	ReturnCode_t retcode; 
	int status = 0;

	if (participant != NULL) {
		retcode = participant->delete_contained_entities();
		if (retcode != RETCODE_OK) {
			fprintf(stderr, "delete_contained_entities error %d\n", retcode);
			status = -1;
		}

		retcode = DomainParticipantFactory::get_instance()->delete_participant(participant);
		if (retcode != RETCODE_OK) {
			fprintf(stderr, "delete_participant error %d\n", retcode);
			status = -1;
		}
	}

	return status;
}

/* 发布者函数 */
extern "C" int publisher_main(int domainId, int sample_count,int string_lenth)
{
	DomainParticipant *participant = NULL;
	Publisher *publisher = NULL;
	Topic *topic = NULL;
	DataWriter *writer = NULL;
	UserDataTypeDataWriter * UserDataType_writer = NULL;
	UserDataType *instance = NULL;
	ReturnCode_t retcode;
	InstanceHandle_t instance_handle = HANDLE_NIL;
	const char *type_name = NULL;
	int count = 0;

	/* 1. 创建一个participant，可以在此处定制participant的QoS */
	/* 建议1：在程序启动后优先创建participant，进行资源初始化*/
	/* 建议2：相同的domainId只创建一次participant，重复创建会占用大量资源 */ 
	participant = DomainParticipantFactory::get_instance()->create_participant(
		domainId, PARTICIPANT_QOS_DEFAULT/* participant默认QoS */,
		NULL /* listener */, STATUS_MASK_NONE);
	if (participant == NULL) {
		fprintf(stderr, "create_participant error\n");
		publisher_shutdown(participant);
		return -1;
	}

	/* 2. 创建一个publisher，可以在创建publisher的同时定制其QoS  */
	/* 建议1：在程序启动后优先创建publisher */
	/* 建议2：一个participant下创建一个publisher即可，无需重复创建 */
	publisher = participant->create_publisher(
		PUBLISHER_QOS_DEFAULT /* 默认QoS */, 
		NULL /* listener */, STATUS_MASK_NONE);
	if (publisher == NULL) {
		fprintf(stderr, "create_publisher error\n");
		publisher_shutdown(participant);
		return -1;
	}

	/* 3. 在创建主题之前注册数据类型 */
	/* 建议1：在程序启动后优先进行注册 */
	/* 建议2：一个数据类型注册一次即可 */
	type_name = UserDataTypeTypeSupport::get_type_name();
	retcode = UserDataTypeTypeSupport::register_type(
		participant, type_name);
	if (retcode != RETCODE_OK) {
		fprintf(stderr, "register_type error %d\n", retcode);
		publisher_shutdown(participant);
		return -1;
	}

	/* 4. 创建主题，并定制主题的QoS  */
	/* 建议1：在程序启动后优先创建Topic */
	/* 建议2：一种主题名创建一次即可，无需重复创建 */
	topic = participant->create_topic(
		"Example UserDataType"/* 主题名 */,
		type_name /* 类型名 */, TOPIC_QOS_DEFAULT/* 默认QoS */,
		NULL /* listener */, STATUS_MASK_NONE);
	if (topic == NULL) {
		fprintf(stderr, "create_topic error\n");
		publisher_shutdown(participant);
		return -1;
	}

	/* 5. 创建datawriter，并定制datawriter的QoS  */
	/* 建议1：在程序启动后优先创建datawriter */
	/* 建议2：创建一次即可，无需重复创建 */
	/* 建议3：在程序退出时再进行释放 */
	/* 建议4：避免打算发送数据时创建datawriter，发送数据后删除，该做法消耗资源，影响性能 */
	writer = publisher->create_datawriter(
		topic , DATAWRITER_QOS_DEFAULT/* 默认QoS */,
		NULL /* listener */, STATUS_MASK_NONE);
	if (writer == NULL) {
		fprintf(stderr, "create_datawriter error\n");
		publisher_shutdown(participant);
		return -1;
	}
	UserDataType_writer = UserDataTypeDataWriter::narrow(writer);
	if (UserDataType_writer == NULL) {
		fprintf(stderr, "DataWriter narrow error\n");
		publisher_shutdown(participant);
		return -1;
	}

	/* 6. 创建一个数据样本 */
	/* 建议：该数据为new出来的，使用后用户需要调用delete_data进行释放内存*/
	instance = UserDataTypeTypeSupport::create_data();
	if (instance == NULL) {
		fprintf(stderr, "UserDataTypeTypeSupport::create_data error\n");
		publisher_shutdown(participant);
		return -1;
	}

	srand(time(0));  

	
	// std::string file_path = "/root/test.txt";

	// fstream input_file(file_path, ios::binary);
    // if (input_file.is_open()) {
    //     cerr << "Error opening file." << endl;
    //     return 1;
    // }

	
	std::string md5_str;
	long time;
	std::string file_content;

	/* 7. 主循环 ，发送数据 */
	for (count = 0; (sample_count == 0) || (count < sample_count); ++count) 
	{
		/* 在此处修改数据 */
//		instance->color = new char[100];		
//		instance->x =  count;
//		instance->y = 1 + count;
//		strcpy(instance->color, "red");

        // int length = 50;  // 指定随机字符串的长度
        string randomString = generateRandomString(string_lenth);

		std::stringstream buffer;
	    buffer << randomString;
	    unsigned char md5_digest[MD5_DIGEST_LENGTH];

	    md5_computer.compute(buffer,md5_digest);

		std::ostringstream md5_str;
        for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
            md5_str << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(md5_digest[i]);
        }

         std::string tmp_str = md5_str.str();
		//  std::cout<< "md5 = " << tmp_str  << std::endl;


		// std::cout << "random string: " << randomString << std::endl;

		// std::cout << "send counter = " << send_counter << std::endl;

		instance->send_counter = send_counter++;
		instance->md5_str = const_cast<char *>(tmp_str.c_str());
		instance->time = 0;
		instance->file_content =const_cast<char *>(randomString.c_str());

		
		retcode = UserDataType_writer->write(*instance, instance_handle);
		if (retcode != RETCODE_OK) {
			// fprintf(stderr, "write error %d\n", retcode);
		}
		// else
			// fprintf(stderr, "%d : write  successfully . . \n", count);
		//  usleep(200);//沉睡1秒		
	}

	/* 8. 删除数据样本 */
	retcode = UserDataTypeTypeSupport::delete_data(instance);
	if (retcode != RETCODE_OK) {
		fprintf(stderr, "UserDataTypeTypeSupport::delete_data error %d\n", retcode);
	}

	/* 9. 删除所有实例 */
	return publisher_shutdown(participant);
}

int main(int argc, char *argv[])
{
	int string_lenth = 10;
	if(argc > 1)
	{
		string_lenth = std::atoi(argv[1]);
		if (string_lenth < 0 || string_lenth > 100) {
        cerr << "Error:Input Integer must be between 0 and 100." << endl;
        return 1;
    }
	}

	int domain_id = 0;
	int sample_count = 0; /* 无限循环 */

	if (argc > 2) {
		sample_count = atoi(argv[2]);   /* 发送至域domain_id */
	}
	// if (argc >= 3) {
	// 	sample_count = atoi(argv[2]); /* 发送sample_count次 */
	// }

	threadpool.enqueue([](long * send_counter,int string_lenth)
		{
			while(1)
			{
				long last_counter = *send_counter;
				sleep(1);
				long current_counter = *send_counter;

				std::cout << "last_counter = " << last_counter << std::endl;
			std::cout << "current_counter = " << current_counter << std::endl;
			std::cout << "current_counter - last_counter = " << current_counter - last_counter << std::endl;

                //(当前的包计数器 - 1秒前的包计数器) * 每个包的长度 * 8 / 2的20次方
				std::cout << "发送端吞吐量：" << static_cast<double>((current_counter - last_counter) * string_lenth * 8) / MB << " Mbytes" << std::endl;
			}
		},&send_counter,string_lenth);

	return publisher_main(domain_id, sample_count,string_lenth);
}
