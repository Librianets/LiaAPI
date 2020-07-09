#include <windows.h>		//win
	#include <ctime>
#include <ratio>
#include <chrono>
#include <cwchar>			//c++
#include "memorymanager.hpp"

  using namespace std::chrono;

int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{

int iNumber = 1;



if (!(iNumber <=0))
{
	wprintf(L"%02X \n", iNumber);
} else wprintf(L"%ls \n", L"iNumber != 0");




//wprintf(L"%02X \n", ppp);
//wprintf(L"%02X \n", ppp.pAdress);
//wprintf(L"%02X \n", ppp->pAdress);
//wprintf(L"%02X \n", CMM.allocate(64));


//CMM.allocate(64);
/*
for (int i = 0; i < 16; i++)
{
	wprintf(L"%i::%02X, ", i, ((unsigned char*)CMM.lpInfoPointer)[i]);
}



wprintf(L"\n", L"");
wprintf(L"\n", L"");

for (int ii = 0; ii < 25; ii++)
{
	www[ii].pAdress = *(CMM.allocate(64))->pAdress;
	
	
for (int i = 0; i < 16; i++)
{
	wprintf(L"%i::%02X, ", i, ((unsigned char*)CMM.lpInfoPointer)[i]);
}
wprintf(L"\n", L"");
wprintf(L"\n", L"");

}*/


/*




int qqqq = 100000;
int iiii = 1000;
//10 000 000
int pppp = 1000;
int oooo = 100000;
// 10 000 000
	
	
	
void* ad[qqqq] = {NULL};
	
	
high_resolution_clock::time_point t1 = high_resolution_clock::now();
for (int ii = 0; ii < iiii; ii++)
{
	for (int i = 0; i < qqqq; i++)
	{
		
		ad[i]=malloc(4);
		free(ad[i]);
	}
}
high_resolution_clock::time_point t2 = high_resolution_clock::now();
duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
wprintf(L"time_span = %f\n", time_span.count());

t1 = high_resolution_clock::now();
for (int ii = 0; ii < oooo; ii++)
{
	CMemoryManager CMM;
	for (int i = 0; i < pppp; i++)
	{
		CMM.allocate(4);
	//	CMM.free(0);
	}
	CMM.~CMemoryManager();
}


t2 = high_resolution_clock::now();
time_span = duration_cast<duration<double>>(t2 - t1);
wprintf(L"time_span = %f\n", time_span.count());



*/
	
//wprintf(L"%i::%02X, ", i, ((unsigned char*)lpInfoPointer)[i]);






return 0;
}