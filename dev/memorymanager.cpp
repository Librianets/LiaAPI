#include <cstdlib>		//c++
#include <cstring>		//c++
#include <cwchar>			//c++

#include "memorymanager.hpp"


CMemoryManager::CMemoryManager (int iNumMember) 
{
	if (!(iNumMember <= 0 || iNumMember > iMaxNumMember)) 
		{iDefNumMember = iNumMember;} 
		else {SetStatusClass(1);}
	classinitialization();
}

void CMemoryManager::classinitialization(void)
{
	lpInfoPointer = (pInfoPointer)calloc(sizeof(InfoPointer), iDefNumMember);
	if (lpInfoPointer == NULL || lpInfoPointer == 0) {return; SetStatusClass(1);} else {}
	iCurNumMember = iDefNumMember;
	InfoPointer testinfo;
	for (int i = 0; i < iCurNumMember; i++)
	{
		memcpy(	(void*)&lpInfoPointer[i], \
				(void*)&testinfo, \
				sizeof(InfoPointer));
	}
}

void CMemoryManager::classdeinitialization(void)
{
	deallocateall();
	if (lpInfoPointer != NULL) {::free(lpInfoPointer);} else {SetStatusClass(0);}

}

CMemoryManager::pInfoPointer CMemoryManager::allocate(int iSize)
{
	if (iSize > (iMaxAllocatedSize) || iSize <= 0) {return 0; SetStatusClass(0);} else {}
	if (iAllocateCount == 0) {} else {}
	void *pAdress = malloc(iSize);
	if (pAdress == NULL || pAdress == 0) {return 0; SetStatusClass(1);} else {}
	
	void *TempAdress = memset(pAdress, 0x00, iSize);
	if (TempAdress != pAdress){return 0; SetStatusClass(3);} else {}

	lpInfoPointer[iAllocateCount].pAdress = pAdress;
	lpInfoPointer[iAllocateCount].iSizeData = iSize;
	lpInfoPointer[iAllocateCount].iNumPointer = iAllocateCount;
	lpInfoPointer[iAllocateCount].bStatusUse = true;
	lpInfoPointer[iAllocateCount].bStatusFree = false;
	
	return &lpInfoPointer[iAllocateCount++];
}



void CMemoryManager::reallocate(void)
{
	
	
}

void CMemoryManager::deallocate(int iNumPointer)
{
	if (iNumPointer < 0 || iNumPointer > (iCurNumMember-1)) {return; SetStatusClass(0);} else {}
	
		if (lpInfoPointer[iNumPointer].bStatusFree == false && lpInfoPointer[iNumPointer].pAdress != NULL)
		{
			::free(lpInfoPointer[iNumPointer].pAdress);
			lpInfoPointer[iNumPointer].bStatusFree = true;
			iAllocateCount--;
		} else {}
}
	
void CMemoryManager::deallocateall(void)
{
	for (int i = 0; i < iCurNumMember; i++)
	{
		deallocate(iCurNumMember);
	}
}