////////////////////////////////////////////////////////////////////////////////
//// Liasteria (creative group, created by Librianets)						////
//// Liasteria (творческая группа, созданная Librianets)					////
////																		////
//// Intellectual property rights belong Liasteria							////
//// Права на интеллектуальную собственность принадлежат Liasteria			////
//// 																		////
//// Use with copyright is permitted without agreement						////
//// Использование с сохраниением копирайта разрешается без согласования	////
//// 																		////
//// Programming is an art													////
//// Everyone has the right to creative freedom								////
//// I create as I see														////
////																		////
//// For all questions, as well as suggestions for improving the code:		////
//// По всем вопросам, а также с предложениями улучшения кода:				////
//// librianets@gmail.com													////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////																		////
//// liasteria api - debug module											////
////																		////
////////////////////////////////////////////////////////////////////////////////

#include <cstdio>		//c++
#include <cwchar>		//c++
#include <cstdlib>		//c++
#include <cstdarg>		//c++
#include <ctime>		//c++
#include <cstring>		//c++

#include <debug.hpp>	//project-liapi

namespace LIAPI
{
	void CDEBUG::dbgcalloc(void)
	{
		lpBuf = (void**)calloc(iCountBuf, sizeof(void*));
		if (lpBuf == NULL) {SetStatusClass(LIAPI_DBGM_FAIL_CALLOC_LP); return;} else {}
		for (int ii = 0; ii < iCountBuf; ii++)
		{
			*(lpBuf+ii) = (void*)calloc(iNumSymPage, sizeof(wchar_t));
			if (*(lpBuf+ii) == NULL) {SetStatusClass(LIAPI_DBGM_FAIL_CALLOC_BUF); return;} else {}
			iBufSize[ii] = iSizeBuf;
		}
	}

	void CDEBUG::dbgfree(void)
	{
		for (int ii = 0; ii < iCountBuf; ii++)
		{
			if (*(lpBuf+ii)) {free(*(lpBuf+ii));} else {}
		}
		free(lpBuf);
	}
	
	void CDEBUG::dbgrealloc(int iNumBuf)
	{
		ClearStatusClass(); 
		void* pTemp = NULL;
		if (iCountResizeBuf[iNumBuf] < iMaxResizeBuf)
		{
			pTemp = (void*) realloc(*(lpBuf+iNumBuf), iSizeBuf*iCountResizeBuf[iNumBuf]);
		} else {SetStatusClass(LIAPI_DBGM_FAIL_REALLOC); return;}
		
		if (pTemp) 
			{*(lpBuf+iNumBuf) = pTemp; iBufSize[iNumBuf]= iSizeBuf*iCountResizeBuf[iNumBuf];}
				else {}
	}	

	void CDEBUG::Init(void)
	{
		dbgcalloc();
	}

	void CDEBUG::Deinit(void)
	{
		dbgfree();
	}	
	
	void CDEBUG::Log(int iLogLevel, const wchar_t *strFormat, ...)
	{
		if (iLogging) {} else {return;}
		if (iLogLevel == LIAPI_DBGM_BUF_DEBUG && !iDebug) {return;} else {}
		if (iLogLevel == LIAPI_DBGM_BUF_ERROR && !iError) {return;} else {}
		if (iLogLevel == LIAPI_DBGM_BUF_INFO && !iInfo) {return;} else {}
		ClearStatusClass();
		
		if (iLogLevel < 0 || iLogLevel >= iCountBuf) 
			{SetStatusClass(LIAPI_DBGM_NOT_LOGLEVEL);	iLogLevel = (iCountBuf-1);} else {}
		
		va_list arglist;
		va_start(arglist, strFormat);
		int iNumSym = 0;
		iNumSym = _vscwprintf(strFormat, arglist); // iNumSym без \0
		if (iNumSym == -1) {SetStatusClass(LIAPI_DBGM_FAIL_SIZELEN); va_end(arglist); return;} else {}
		
		++iNumSym *= sizeof(wchar_t);
		int iBalanceSize = iBufSize[iLogLevel]-iPosCurBuf[iLogLevel]; // остаток места в буфере
		if (iBalanceSize < iNumSym)
		{
			dbgrealloc(iLogLevel);
			if (GetStatusClass() == LIAPI_DBGM_FAIL_REALLOC) {dbgrealloc(iLogLevel);} else {}// повторная попытка выделить память
			if (GetStatusClass() == LIAPI_DBGM_FAIL_REALLOC) 
				{va_end(arglist); return;}
					else {iBalanceSize = iBufSize[iLogLevel]-iPosCurBuf[iLogLevel];}
		} else {}
		
		iNumSym = _vsnwprintf((*((wchar_t**)lpBuf+iLogLevel)+iPosCurBuf[iLogLevel]), iBalanceSize, strFormat, arglist);

		if (iNumSym >=0) {iPosCurBuf[iLogLevel] += iNumSym;} else {} //*sizeof(wchar_t);
		
		va_end(arglist);
		if (iWriteAlways) {WriteLog();} else {}
		return;
	}
	
	void CDEBUG::WriteLog(void)
	{
		ClearStatusClass();
		
		FILE *logfile;
		int iFlagExist = 0;
		logfile = fopen(lpLogFile, "r");
		if (logfile) {iFlagExist = 1; fclose(logfile);} else {}
		
		logfile = fopen(lpLogFile, "ab+");
		if (!iFlagExist) 
			{fwrite(&iSignUTF16BE, 1, sizeof(iSignUTF16BE), logfile);} else {} 
		
		for (int i = 0; i < iCountBuf; i++)
		{
			int iCountWriteSym = iPosCurBuf[i]-iPosWriteBuf[i];
		
			if (iCountWriteSym > 0)
			{
				//int iCountWriteSym = 0;
				iCountWriteSym = fwrite((*((wchar_t**)lpBuf+i)+iPosWriteBuf[i]), sizeof(wchar_t), iCountWriteSym, logfile);
				if (iCountWriteSym >= 0)
				{
					
					iPosWriteBuf[i] += iCountWriteSym;		
				} else {SetStatusClass(LIAPI_DBGM_FAIL_WRITELOG);}
			} else {continue;}
		}
		fclose(logfile);
		return;
	}
		
	void CDEBUG::LowDebugLog(const wchar_t *ErrorInfo)
	{
		FILE *criticalerrorfile;
		criticalerrorfile = fopen(strCriticalLogFile, "ab+");
		if (criticalerrorfile == NULL) {return;}
		fwrite(ErrorInfo, sizeof(wchar_t), wcslen(ErrorInfo), criticalerrorfile);
		wchar_t NewLen [0x10] = L"\r\n";
		fwrite(NewLen, sizeof(wchar_t), wcslen(NewLen), criticalerrorfile);		
		fclose(criticalerrorfile);
	}
	
	wchar_t *CDEBUG::data (void)
	{
		/*
		Member		Type	Meaning						Range
		tm_sec		int		seconds after the minute	0-60*
		tm_min		int		minutes after the hour		0-59
		tm_hour		int		hours since midnight		0-23
		tm_mday		int		day of the month			1-31
		tm_mon		int		months since January		0-11
		tm_year		int		years since 				1900	
		tm_wday		int		days since Sunday			0-6
		tm_yday		int		days since January 1		0-365
		tm_isdst	int		Daylight Saving Time flag	
		*/
		time_t rawtime;
		struct tm *timeinfo;
		std::time ( &rawtime );
		timeinfo = localtime ( &rawtime );
		static wchar_t strData [0xFF] = {0};
		static const wchar_t day_name[7][0x4] = {L"Вс", L"Пн", L"Вт", L"Ср", L"Чт", L"Пт", L"Сб"};
		static const wchar_t mon_name[12][0x20] = {L"Январь", L"Февраль", L"Март", L"Апрель", 
													L"Май", L"Июнь", L"Июль", L"Август", 
													L"Сентябрь", L"Октябрь", L"Ноябрь", L"Декабрь"};
											
		int val = swprintf(strData, 0xFF, L"%ls месяц, %i число, %i г.", mon_name[timeinfo->tm_mon], timeinfo->tm_mon, 1900 + timeinfo->tm_year);
		if (val < 0) {memset(strData, 0xFF, sizeof(wchar_t));} else {}
		return strData; 
	}

	wchar_t *CDEBUG::time (void)
	{
		time_t rawtime;
		struct tm *timeinfo;
		std::time ( &rawtime );
		timeinfo = localtime ( &rawtime );
		static wchar_t strTime [0xFF] = {0};
		int val = swprintf(strTime, 0xFF, L"%i:%i:%i", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
		
		if (val < 0) {memset(strTime, 0xFF, sizeof(wchar_t));} else {}
		return strTime;
	}

} //namespace