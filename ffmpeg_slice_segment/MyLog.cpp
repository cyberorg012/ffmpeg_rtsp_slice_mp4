#include "stdafx.h"
#include "MyLog.h"
#include "boost/date_time/posix_time/posix_time.hpp"

#include <stdarg.h>
#include <string.h>

CMyLog::CMyLog()  //���캯����������־�ļ���Ĭ��·��
{
	memset(m_strLogPath , 0, 256);
	strcpy(m_strLogPath,"./");
}

CMyLog::~CMyLog()
{
	
}

/*================================================================ 
* ��������    InitLog
* ������      LPCTST lpszLogPath
* ��������:   ��ʼ����־(������־�ļ���·��)
* ����ֵ��    void
================================================================*/ 
void CMyLog::InitLog(const char* lpszLogPath)   
{	
	strcpy(m_strLogPath,lpszLogPath);
}

void CMyLog::Add(const char* fmt, ...)
{
	boost::lock_guard<boost::mutex> lock_guard_(mutex_);

	try      
	{
		if ( strlen(m_strLogPath) == 0)
			return ;
		
		if ( fmt == NULL )
			return ;

        boost::posix_time::ptime t(boost::posix_time::microsec_clock::local_time());	
		std::string tmplogpath = m_strLogPath + boost::gregorian::to_iso_extended_string((t.date())) + ".log";
		
		try      
		{
			va_list argptr;          //�����ַ����ĸ�ʽ
			va_start(argptr, fmt);
			vsnprintf(m_tBuf, BUFSIZE, fmt, argptr);
			va_end(argptr);
		}
		catch (...)
		{
			m_tBuf[0] = 0;
		}
		
		FILE *fp = fopen(tmplogpath.c_str(), "a"); //����ӵķ�ʽ������ļ�
		if(fp != NULL && strlen(m_tBuf) > 0)
		{
			std::string str = boost::posix_time::to_simple_string(t.time_of_day());
			fprintf(fp,"%s : %s\n",str.c_str(), m_tBuf);

			std::cout << m_tBuf << std::endl;

			fclose(fp);
		}
	}
	catch (...){}
}


