// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Hook.h"
#include "HookEngine.h"

typedef HMODULE (WINAPI *LoadLibraryProc)(_In_ LPCSTR lpLibFileName);

HMODULE WINAPI MyLoadLibraryA(_In_ LPCSTR lpLibFileName)
{
	printf("MyLoadLibraryA %s\r\n", lpLibFileName);
	Hook * hook =HookEngine::GetInstance()->FindHookByNewFuncAddr((ULONG)MyLoadLibraryA);
	LoadLibraryProc func = (LoadLibraryProc)hook->GetCalloldFuncAddress();
	HMODULE hm = func(lpLibFileName);
	return hm;
}



ULONG __stdcall CallBack(PRegisterContext registerContext)
{
	
	printf("------------------------------------\r\n");
	return 0;
}

int main()
{
	//Hook ͷ�� ʾ��
	HMODULE hm = LoadLibraryA("ntdll.dll");
	auto hookengine = HookEngine::GetInstance();
	hookengine->AddHook((ULONG)LoadLibraryA, (ULONG)MyLoadLibraryA);
	hm = LoadLibraryA("kernel32.dll");
	

	//Hook �޸ļĴ���ʾ������
	PVOID p = GetProcAddress(hm, "LoadLibraryW");
	hookengine->AddHook((ULONG)GetProcAddress, (ULONG)CallBack, HookType::JmpHookGetRegister);
	p = GetProcAddress(hm, "LoadLibraryW");

	HookEngine::DistoryInstance();
    return 0;
}

