#pragma once
/*
Author:��� QQ:471194425 Ⱥ�ţ�1026716399
*/
#include <iostream>
#include <map>
#include <Windows.h>
enum HookType
{
	JmpHeadHook, //һ������ Hook ͷ�� 
	JmpHookGetRegister, //һ�������޸ļĴ�����HOOK
};

class Hook;

class HookEngine
{
public:
	virtual ~HookEngine();
	static HookEngine * GetInstance();
	static void  DistoryInstance();

	//���HOOK 
	/*
	@param oldFunc  HOOK�ĺ�����ַ
	@param newFunc  �µĺ�����ַ
	@param type     Hook������
	*/
	bool AddHook(ULONG oldFunc, ULONG newFunc, HookType type = HookType::JmpHeadHook);

	//�����滻 ������ַ ���ҵ�HOOK ����
	Hook * FindHookByNewFuncAddr(ULONG newFunc);

	//����HOOK ������ַ ���ҵ�HOOK ����
	Hook * FindHookByOldFuncAddr(ULONG oldFunc);

	//���� �滻������ַ ɾ��
	bool removeHook(ULONG newFunc);

	//ɾ������ HOOK
	void removeAllHook();
private:
	HookEngine();
private:
	static HookEngine * hookEngine;
	std::map<ULONG, Hook*> hookMaps;
};

