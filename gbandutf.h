#ifndef TRANSFORM
#define TRANSFORM
#include <map>
#ifdef WIN32
#include <STDDEF.H>
#include <STDLIB.H>
#else
#include "msystem.h"
#include "mtype.h"
#endif

using namespace std;
// 是否启用map转换，建议启用
// 使用map转换的话，同一个常量字符串不会做两次转换
//#define TEST_TYPE_MAP
/*
typedef map<const char*, const char*> strmap;
class CUtf8String
{
     public:
         inline CUtf8String(const char* gb2312)
         {
             m_bIsConst = true;
 #ifdef TEST_TYPE_MAP
             if (m[gb2312])
             {
                 m_utf8 = m[gb2312];
                 return ;
             }
 #endif
             buffLen = strlen(gb2312);
             WCHAR wbuff[5120];
             buffLen = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wbuff, 5120);
			 if(buffLen == 0)
				 TRACE0("error \r\n");
             buffLen = WideCharToMultiByte(CP_UTF8, 0, wbuff, -1, NULL, 0, 0, 0);
	//		 if(buffLen %2)
	//			 buffLen++;
             m_utf8 = new char[buffLen+3];
             WideCharToMultiByte(CP_UTF8, 0, wbuff, -1, (LPSTR)m_utf8, buffLen, 0, 0);
 #ifdef TEST_TYPE_MAP
             m[gb2312] = m_utf8;
 #endif
         }
 
         inline CUtf8String(char* gb2312)
         {
             m_bIsConst = false;
             buffLen = 0;
             WCHAR wbuff[5120];
             MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wbuff, 5120);
             buffLen = WideCharToMultiByte(CP_UTF8, 0, wbuff, -1, NULL, 0, 0, 0);
             m_utf8 = new char[buffLen+3];
             WideCharToMultiByte(CP_UTF8, 0, wbuff, -1, (LPSTR)m_utf8, buffLen, 0, 0);
         }
 
         inline ~CUtf8String()
             {
 #ifndef TEST_TYPE_MAP
             if (m_utf8)
             {
                 delete m_utf8;
                 m_utf8 = 0;
             }
 #else
             if (!m_bIsConst)
                 {
                 if (m_utf8)
                     {
                     delete m_utf8;
                     m_utf8 = 0;
                     }
                 }
 #endif
             }
 
         inline operator char*()
             {
             return (char*)m_utf8;
             }
		 inline int getbufflen(){return buffLen;}
     private:
		 int buffLen;
         char* m_utf8;
         bool m_bIsConst;
 #ifdef TEST_TYPE_MAP
         static strmap m;
 #endif
 };
 
 class CGb2312String
     {
     public:
         inline CGb2312String(const char* utf8)
             {
 #ifdef TEST_TYPE_MAP
             if (m[utf8])
             {
                 m_gb2312 = 0;
                 m_gb2312 = m[utf8];
             }
 #endif
             int buffLen = 0;
             WCHAR wbuff[5120];
             MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wbuff, 5120);
             buffLen = WideCharToMultiByte(CP_ACP, 0, wbuff, -1, NULL, 0, 0, 0);
             m_gb2312 = new char[buffLen+1];
             WideCharToMultiByte(CP_ACP, 0, wbuff, -1, (LPSTR)m_gb2312, buffLen, 0, 0);
 #ifdef TEST_TYPE_MAP
             m[utf8] = m_gb2312;
 #endif
         }
 
         inline CGb2312String(char* utf8)
         {
 #ifdef TEST_TYPE_MAP
             if (m[utf8])
             {
                 m_gb2312 = 0;
                 m_gb2312 = m[utf8];
             }
 #endif
             int buffLen = 0;
             WCHAR wbuff[5120];
             MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wbuff, 5120);
             buffLen = WideCharToMultiByte(CP_ACP, 0, wbuff, -1, NULL, 0, 0, 0)+2;
             m_gb2312 = new char[buffLen+1];
             WideCharToMultiByte(CP_ACP, 0, wbuff, -1, (LPSTR)m_gb2312, buffLen, 0, 0);
 #ifdef TEST_TYPE_MAP
             m[utf8] = m_gb2312;
 #endif
         }
 
         inline ~CGb2312String()
         {
 #ifndef TEST_TYPE_MAP
             if (m_gb2312)
                 {
                 delete m_gb2312;
                 m_gb2312 = 0;
                 }
 #endif
         }
 
         inline operator char*()
         {
             return (char*)m_gb2312;
         }
		 inline int getbufflen(){return buffLen;}
     private:
		 int buffLen;
         char* m_gb2312;
 #ifdef TEST_TYPE_MAP
         static strmap m;
 #endif
	 public:
 };
 
 #ifdef TEST_TYPE_MAP
 strmap CUtf8String::m;
 strmap CGb2312String::m;
 #endif

*/
// #define BUFF_SIZE 1024
extern wchar_t * ANSIToUnicode( const char* str,int& nLen );


extern char * UnicodeToANSI( const wchar_t* str ,int & nLen);


extern wchar_t * UTF8ToUnicode( const char* str ,int & len);


extern char * UnicodeToUTF8( const wchar_t* str ,int & len);

/*宽字符转换为多字符Unicode - ANSI*/
extern char* w2m(const wchar_t* wcs);

/*多字符转换为宽字符ANSI - Unicode*/
extern wchar_t* m2w(const char* mbs);


extern char* ANSIToUTF8(const char* str,int & len);


extern char* UTF8ToANSI(const char* str,int &len);


  //===================无聊的分割线==========================
 #define U   (CUtf8String)
 
 #define W   (CGb2312String)
#endif
 