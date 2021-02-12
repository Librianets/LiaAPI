////////////////////////////////////////////////////////////////////////////////
//// Liasteria (creative group). File created Librianets					////
//// Liasteria (творческая группа). Фаил создан Librianets					////
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
////////////////////////////////////////////////// /////////////////////////////
////																		////
//// liasteria api - debug module											////
////																		////
////////////////////////////////////////////////////////////////////////////////

#ifndef DEBUG_HPP
#define DEBUG_HPP

namespace LIAPI
{
//------------------------------------ Class CDEBUG ------------------------------------//
class CDEBUG
{
public:
//------------------------------------ Constructor ------------------------------------//
	CDEBUG(void) {Init();}
	~CDEBUG(void) {Deinit();}
//----------------------------- Class diagnostic options -----------------------------//
public:

	inline unsigned int GetStatusClass(void) {return iStatusClass;}
	unsigned int GetPrevStatusClass(void) 
		{if (iErrorCount == 0) {return iErrorHistory[iErrorCount];} else 
			{return iErrorHistory[iErrorCount-1];}}
			
	unsigned int GetOtherStatusClass(int iOtherStatusClass) 
		{if (iOtherStatusClass > 0xFE || iOtherStatusClass < 0) {iOtherStatusClass == 0;} else {} 
			return iErrorHistory[iOtherStatusClass];}
			
	wchar_t* GetInfoStatusClass(unsigned int iStatusClass) 
		{return &strStatusClassInfo[iStatusClass][0];}
		
	int GetErrorCount (void) {return iErrorCount;}
	wchar_t* GetInfoClass(void) {return &strStatusClassInfo[0][0];}

private:
	unsigned int iStatusClass = 0;
	int iErrorHistory [0xFF] = {0};
	int iErrorCount = 0; // 
	int iErrorCountHistory = 0; //
	int iCountCritical = 0; // заменить
	
	void SetStatusClass(unsigned int iNewStatusClass) 
	{
		iStatusClass = iNewStatusClass;
		iErrorHistory[iErrorCountHistory] = iNewStatusClass;
		iErrorCountHistory++;
		iErrorCount++;
		if (iErrorCountHistory == 0xFF) {iErrorCountHistory = 0;} else {}
	}		

	void ClearStatusClass(void) {iStatusClass = 0;}
//------------------------------------ Error code ------------------------------------//
#define LIAPI_DBGM_INFOCLASS	 	0x00
#define LIAPI_DBGM_FAIL_CALLOC_LP 	0x01
#define LIAPI_DBGM_FAIL_CALLOC_BUF 	0x02
#define LIAPI_DBGM_NOT_LOGLEVEL 	0x03
#define LIAPI_DBGM_FAIL_SIZELEN		0x04
#define LIAPI_DBGM_FAIL_REALLOC		0x05
#define LIAPI_DBGM_FAIL_WRITELOG	0x06
	wchar_t strStatusClassInfo [10] [0xFF] =
	{
		L"Liasteria API - debug module",											//0 LIAPI_DBGM_INFOCLASS
		L"Не удалось выделить память под массив указателей на буферы", 				//1 LIAPI_DBGM_FAIL_CALLOC_LP
		L"Не удалось выделить память под буфер", 									//2 LIAPI_DBGM_FAIL_CALLOC_BUF
		L"LogLevel указан не верно. Сброшен до level = other", 						//3 LIAPI_DBGM_NOT_LOGLEVEL
		L"Не удалось вычислить размер строки, return = -1", 						//4 LIAPI_DBGM_FAIL_SIZELEN
		L"Не удалось перераспределить память. Превышен лимит перераспределений" 	//5 LIAPI_DBGM_FAIL_REALLOC
		L"Не удалось записать лог файл" 											//6 LIAPI_DBGM_FAIL_WRITELOG
	};
//-------------------------------------------------------------------------------------//

private:
//------------------------------- Private variables -----------------------------------//
	int iLogging = 0;
	int iDebug = 0;
	int iError = 0;
	int iInfo = 0;
	int iWriteAlways = 0;
	
	#define LIAPI_DBGM_BUF_DEBUG	0x00
	#define LIAPI_DBGM_BUF_INFO		0x01
	#define LIAPI_DBGM_BUF_WARNING	0x02
	#define LIAPI_DBGM_BUF_ERROR	0x03
	#define LIAPI_DBGM_BUF_OTHER	0x04
	static const int iCountBuf = 5; 	// Количество буф. 0 - Debug, 1 - Info, 2 - Warning, 
														// 3 - Error, 4 - Other	
	int iNumSymPage = 262144; 	// Количество байт в странице 256кб

	//int iSizePageInit[iCountBuf] = {524288, 102400, 10240, 10240, 10240};
	
	int iSizeBuf = sizeof(wchar_t) * iNumSymPage; 	// размер страницы в буфере с учетом wchar_t
													// перевести на void бы...
	void** lpBuf = NULL;

	int iPosCurBuf[5] = {0}; 		// позиция "курсора" в буфере
	int iPosWriteBuf[5] = {0}; 		// позиция записи в файл
	int iBufSize[5] = {0};			// Текущий размер буфера
	int iCountResizeBuf[5] = {0}; 	// количество перераспределений для конкретного буфера
	int iMaxResizeBuf = 50;			// максимальное количество перераспределений
	//int iMaxResizeBuf[iCountBuf] = {100, 5, 5, 5, 5};			// максимальное количество перераспределений
	
	unsigned int 	iSignUTF8 		= 0xEFBBBF;
	unsigned short 	iSignUTF16BE 	= 0xFEFF;
	unsigned short 	iSignUTF16LE	= 0xFFFE;
	unsigned int	iSignUTF32BE 	= 0x0000FEFF;
	unsigned int 	iSignUTF32LE	= 0x0000FFFE;
	//little endian big endian
	
	//wchar_t NewLine = 0x0A00;
	//wchar_t ReturnLine = 0x0D00;
	
	char strCriticalLogFile[0xF] 	= "liapi.log";
	char strDefaultLogFile[0x50]	= "debug.log";
	char *lpLogFile = strDefaultLogFile;
	
//------------------------------- Private functions -----------------------------------//
	void Init(void);
	void Deinit(void);
	void dbgcalloc(void);
	void dbgfree(void);
	void dbgrealloc(int iNumBuf);

public:
//------------------------------- Public functions -----------------------------------//
	void Log(int iLogLevel, const wchar_t *strFormat, ...);
	void LowDebugLog(const wchar_t *ErrorInfo); // Вызывается явно, если ошибка модуля.
												// Прямая запись в файл liapi.log
	void WriteAllErrorClass(void);
	void SetPath(const wchar_t *strPath);
	void WriteLog(void);
	
	
	wchar_t *data (void);
	wchar_t *time (void);
	
	void EnableLogging (void) {iLogging = 1;}
	void DisableLogging (void) {iLogging = 0;}
	void EnableDebugLv (void) {iDebug = 1;}
	void DisableDebugLv (void) {iDebug = 0;}
	void EnableErrorLv (void) {iError = 1;}
	void DisableErrorLv (void) {iError = 0;}
	void EnableInfoLv (void) {iInfo = 1;}
	void DisableInfoLv (void) {iInfo = 0;}
	void EnableWriteAlways (void) {iWriteAlways = 1;}
	void DisableWriteAlways (void) {iWriteAlways = 0;}
//------------------------------- Public variables -----------------------------------//

	
};
} //namespace
#endif //DEBUG_HPP