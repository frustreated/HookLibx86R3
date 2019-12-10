#pragma once
/*
Author:��� QQ:471194425 Ⱥ�ţ�1026716399
*/
#include <Windows.h>
#include "HookEngine.h"

typedef struct _RegisterContext 
{
	ULONG EAX;
	ULONG ECX;
	ULONG EDX;
	ULONG EBX;
	ULONG ESP;
	ULONG EBP;
	ULONG ESI;
	ULONG EDI;
	ULONG EFLGS;
}RegisterContext,*PRegisterContext;

//JmpHookGetRegister ���͵�ԭ��
typedef ULONG(__stdcall *HookCallBack)(PRegisterContext registerContext);

class Hook
{
public:
	Hook();
	virtual ~Hook();
	//HOOK �����߲���Ҫ��������������˺����Ǹ������
	bool InstallHook(ULONG oldFunc,ULONG newFunc, HookType type = HookType::JmpHeadHook);
	
	//�Ƿ��Ѿ�HOOK
	bool isHook();

	//��ȡ��HOOK�ĺ�����ַ
	ULONG GetOldFunctionAddr();
	
	//��ȡ�µĺ�����ַ
	ULONG GetNewFuncAddress();

	//�����HookType::JmpHeadHook �ɵ��ô˺��� ��ȡ ��HOOK�ĺ�����ַ
	/*
		typedef HMODULE (WINAPI *LoadLibraryProc)(_In_ LPCSTR lpLibFileName);

		HMODULE WINAPI MyLoadLibraryA(_In_ LPCSTR lpLibFileName)
		{
			printf("MyLoadLibraryA %s\r\n", lpLibFileName);
			Hook * hook =HookEngine::GetInstance()->FindHookByNewFuncAddr((ULONG)MyLoadLibraryA);
			//����ԭ���ĺ���
			LoadLibraryProc func = (LoadLibraryProc)hook->GetCalloldFuncAddress();
			HMODULE hm = func(lpLibFileName);
			return hm;
		}
	*/
	
	//�����HookType::JmpHookGetRegister �����ͣ���ô�ǻ�����ص���ʼ��ַ
	ULONG GetCalloldFuncAddress();


	
protected:
	
	virtual bool JmpHeadHook(ULONG oldFunc, ULONG newFunc);
	virtual bool JmpHookGetRegister(ULONG oldFunc, ULONG newFunc);
	virtual bool UnInstallHook();
	virtual int  CopyMemcpy(void * desc, void *src, size_t size);
	virtual bool UpdatePageCopyMemcpy(void * desc, void *src, size_t size);

private:
	char * GetMemory(int allocSize, bool * isAlloc);
	char * CreateDispatchFunc();
	ULONG calcResetCode(ULONG oldFunc, ULONG hookCodeSize);
private:
	char orginCode[30];
	int orginLen;
	ULONG oldFuncAddress;
	ULONG oldFuncRetAddress;
	ULONG newFuncAddress;
	ULONG calloldFuncAddress;
	HookType type;
	bool isHookSuccess;
	bool isAllocMemory;
	bool isCreateDispatchFuncAllocMemory;
	char * templateCode;
	int templateLen;
};

