// Don't modify this file as it will be overwritten.
//
#include "IDL_UserDataType.h"

UserDataType::UserDataType(const UserDataType &IDL_s){
  send_counter = IDL_s.send_counter;
  md5_str = IDL_s.md5_str;
  time = IDL_s.time;
  file_content = IDL_s.file_content;
}

UserDataType& UserDataType::operator= (const UserDataType &IDL_s){
  if (this == &IDL_s) return *this;
  send_counter = IDL_s.send_counter;
  md5_str = IDL_s.md5_str;
  time = IDL_s.time;
  file_content = IDL_s.file_content;
  return *this;
}

void UserDataType::Marshal(CDR *cdr) const {
  cdr->PutLong(send_counter);
  cdr->PutString(md5_str);
  cdr->PutLong(time);
  cdr->PutString(file_content);
}

void UserDataType::UnMarshal(CDR *cdr){
  cdr->GetLong(send_counter);
  {
    char *IDL_str;
    cdr->GetString(IDL_str);
    if(md5_str != NULL )
    {
        delete md5_str;
        md5_str = NULL;
    }
    md5_str = IDL_str;
  }
  cdr->GetLong(time);
  {
    char *IDL_str;
    cdr->GetString(IDL_str);
    if(file_content != NULL )
    {
        delete file_content;
        file_content = NULL;
    }
    file_content = IDL_str;
  }
}

