
// libeventclinet.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// ClibeventclinetApp: 
// �йش����ʵ�֣������ libeventclinet.cpp
//

class ClibeventclinetApp : public CWinApp
{
public:
	ClibeventclinetApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern ClibeventclinetApp theApp;