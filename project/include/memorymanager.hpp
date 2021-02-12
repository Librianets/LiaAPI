
//-------------------------------------/Class CMemoryManager/-------------------------------------//
class CMemoryManager
{
//----------------------------------/Constructor and Destructor/----------------------------------//
public:
	CMemoryManager (){classinitialization();}
	CMemoryManager (int iNumMember);
	~CMemoryManager (){classdeinitialization();}
//--------------------------------------/Private variables /--------------------------------------//
private:
	int iAllocateCount = 0;
	int iNextAllocate = 0;
	bool bStatusNumMemory [1024]; // сделать менеджер
	void *ArrayMemoryPointer; // сделать менеджер
//It`s not over between us, you can`t run from me forever


//typedef struct infopointer InfoPointer;
//typedef struct &infopointer pInfoPointer;
//---------------------------------------/Public variables/---------------------------------------//
public:
	struct infopointer;
	typedef struct infopointer *pInfoPointer;
	typedef struct infopointer InfoPointer;
	int iMaxAllocatedSize = 1024*1024*256; // 256 мб
	int iMaxNumMember = 1024*1024*32; // 33 554 432
	pInfoPointer lpInfoPointer = NULL;
	int iDefNumMember = 1024;
	int iCurNumMember = 0;

//--------------------------------------/Private functions /--------------------------------------//
private:

//---------------------------------------/Public functions/---------------------------------------//
public:
	void classinitialization(void);
	void classdeinitialization(void);
	pInfoPointer allocate(int iSize);
	int callocate(int iSize);
	void reallocate(void);
	void deallocate(int iNumPointer);
	void deallocateall(void);
	int findfreeallocate();

//--------------------------------------/Diagnostic options/--------------------------------------//
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
//------------------------------------------/Error code/------------------------------------------//
#define LIAPI_MMM_INFOCLASS	 	0x00
#define LIAPI_MMM_FAIL_CALLOC_LP 	0x01
#define LIAPI_MMM_FAIL_CALLOC_BUF 	0x02
#define LIAPI_MMM_NOT_LOGLEVEL 	0x03
#define LIAPI_MMM_FAIL_SIZELEN		0x04
#define LIAPI_MMM_FAIL_REALLOC		0x05
#define LIAPI_MMM_FAIL_WRITELOG	0x06
	wchar_t strStatusClassInfo [10] [0xFF] =
	{
		L"Liasteria API - memory manager module",									//0 LIAPI_DBGM_INFOCLASS
		L"Не удалось выделить память под массив указателей на буферы", 				//1 LIAPI_DBGM_FAIL_CALLOC_LP
		L"Не удалось выделить память под буфер", 									//2 LIAPI_DBGM_FAIL_CALLOC_BUF
		L"LogLevel указан не верно. Сброшен до level = other", 						//3 LIAPI_DBGM_NOT_LOGLEVEL
		L"Не удалось вычислить размер строки, return = -1", 						//4 LIAPI_DBGM_FAIL_SIZELEN
		L"Не удалось перераспределить память. Превышен лимит перераспределений" 	//5 LIAPI_DBGM_FAIL_REALLOC
		L"Не удалось записать лог файл" 											//6 LIAPI_DBGM_FAIL_WRITELOG
	};
};

struct CMemoryManager::infopointer {
	void* pAdress = NULL;			//4
	int iNumPointer = 0; 			//4
	int iSizeData = 0; 				//4
	bool bStatusUse = false; 		//1
	bool bStatusFree = true; 		//1
	bool Reserved [2] = {false}; 	//2 //выравнивание
									//16
};