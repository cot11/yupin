
// Server.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CServerApp:
// �� Ŭ������ ������ ���ؼ��� Server.cpp�� �����Ͻʽÿ�.
//

class CServerApp : public CWinApp
{
public:
	CServerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CServerApp theApp;