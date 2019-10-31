/************************************************************************ 
* �ļ�����    log.h 
* �ļ�������  ���ڼ�¼��־����CLog  
* �汾�ţ�    2.0 
* ��־��ʶ��  0085
************************************************************************/ 

#ifndef _MYLOG_H
#define _MYLOG_H

#include "boost/thread.hpp"

class CMyLog
{
public:
	CMyLog();
	~CMyLog();

public:
	void InitLog(const char* lpszLogPath = "./");		
	void Add(const char* fmt, ...);		//������֣������͸�printfһ��
	
protected:

	enum {BUFSIZE = 4096};  //����������
	char  m_tBuf[BUFSIZE];
	char m_strLogPath[256];
	boost::mutex mutex_;
};

#endif