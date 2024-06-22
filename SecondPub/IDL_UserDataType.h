// Don't modify this file as it will be overwritten.
//
#include "CDR/CDR.h"
#include "ReturnCode.h"
#include "BasicTypes.h"

#ifndef IDL_UserDataType_hh
#define IDL_UserDataType_hh

#ifndef UserDataType_defined
#define UserDataType_defined

struct UserDataType {
  UserDataType()
	{
		send_counter = 0;
		md5_str = new char[255];
		md5_str[0]= '\0';
		time = 0;
		file_content = new char[255];
		file_content[0]= '\0';
	}

  UserDataType(const UserDataType  &IDL_s);

  ~UserDataType(){
		delete md5_str;
		md5_str = NULL;
		delete file_content;
		file_content = NULL;
	}

  	int StructSize()
	{
		int strSize = 0;
		strSize += sizeof(UserDataType);
		strSize += strlen(md5_str);
		strSize += strlen(file_content);
		return strSize;
	}
  UserDataType& operator= (const UserDataType &IDL_s);

  void Marshal(CDR *cdr) const;
  void UnMarshal(CDR *cdr);

  long send_counter;
char* md5_str;
long time;
char* file_content;
  
};

typedef sequence<UserDataType> UserDataTypeSeq;

#endif




#endif /*IDL_UserDataType_hh */
