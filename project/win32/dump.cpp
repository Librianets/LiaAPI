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
//// liasteria api - dump module											////
////																		////
////////////////////////////////////////////////////////////////////////////////

#include <windows.h>		//win
//#include <DbgHelp.h>		//win

#include <cstdio>			//c++
#include <cwchar>			//c++
#include <csignal>			//c++

#include <dump.hpp>			//liapi
//#include <debug.hpp>		//liapi
//#include <winmain.hpp>	//liapi

namespace LIAPI
{
namespace DUMP
{


const unsigned int iCountLpFunc = 0x10;
unsigned int iCountLpFuncCurrect = 0;
lp_func_other_class lp_func [iCountLpFunc] = {NULL};
void *lp_func2 [iCountLpFunc] = {NULL};

void AddFuncExec (void *AdressFunc)
{
	if (iCountLpFuncCurrect == (iCountLpFunc-1)) {return;} else {}
	lp_func[iCountLpFuncCurrect] == AdressFunc;
	iCountLpFuncCurrect++;	
}

void DeleteFuncExec (void)
{
	if (iCountLpFuncCurrect == 0 && lp_func[iCountLpFuncCurrect] == NULL) {return;} else {}
	lp_func[iCountLpFuncCurrect] == NULL;
	if (iCountLpFuncCurrect == 0) {} else {iCountLpFuncCurrect--;}
}

void ResetFuncExec (void)
{
	for (unsigned int x = 0; x < iCountLpFunc; x++)
	{
		lp_func[x] == NULL;
	}
}


void ExecuteFunc (void)
{
	for (unsigned int x = 0; x < iCountLpFunc; x++)
	{
		if (lp_func[x] != NULL)
		{
			lp_func[x] ();
		} else {}	
	}
}


void DumpStart (void)
{
	signal(SIGSEGV, SigException);
}

void DumpStop (void)
{
	signal(SIGSEGV, SIG_DFL);
}


void SigException(int signum)
{
	ExecuteFunc();	
	DumpStop();
	exit(3);
}
	




//#include <signal.h>
//void(*signal(int signr, void(*sighandler)(int)))(int);
//typedef void signalfunction(int);
//signalfunction *signal(int signr, signalfunction *sighandler);
//LIAPI::CDUMP::SigException» из типа «void (LIAPI::CDUMP::)(int)» в тип «__p_sig_fn_t {aka void (*)(int)}»
//typedef	void (*__p_sig_fn_t)(int);
//#define SIG_DFL (__p_sig_fn_t)0
//__p_sig_fn_t __cdecl signal(int _SigNum,__p_sig_fn_t _Func);

void Test_Segmentation_Fault(void)
{
	int *False_pointer = NULL;
	*False_pointer = 13;
}
} // namespace DUMP
} // namespace LIAPI






















/*
void Sig_exception(int signum)
{
	//HANDLE hFile = CreateFileA("qwfffe.dmp", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//BOOL qweqwe = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), (HANDLE)hFile, MINIDUMP_TYPE(MiniDumpNormal), NULL, NULL, NULL);
	//CloseHandle(hFile);
	
/* MiniDumpNormal,
 MiniDumpWithDataSegs,
 MiniDumpWithFullMemory,
 MiniDumpWithHandleData,
 MiniDumpFilterMemory,
 MiniDumpScanMemory,
 MiniDumpWithUnloadedModules,
 MiniDumpWithIndirectlyReferencedMemory,
 MiniDumpFilterModulePaths,
 MiniDumpWithProcessThreadData,
 MiniDumpWithPrivateReadWriteMemory,
 MiniDumpWithoutOptionalData,
 MiniDumpWithFullMemoryInfo,
 MiniDumpWithThreadInfo,
 MiniDumpWithCodeSegs,
 MiniDumpWithoutAuxiliaryState,
 MiniDumpWithFullAuxiliaryState,
 MiniDumpWithPrivateWriteCopyMemory,
 MiniDumpIgnoreInaccessibleMemory,
 MiniDumpWithTokenInformation,
 MiniDumpWithModuleHeaders,
 MiniDumpFilterTriage,
 MiniDumpWithAvxXStateContext,
 MiniDumpWithIptTr

 signal(signum, SIG_DFL);
	exit(3);
}*/