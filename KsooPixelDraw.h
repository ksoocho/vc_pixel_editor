
// KsooPixelDraw.h : KsooPixelDraw ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CKsooPixelDrawApp:
// �� Ŭ������ ������ ���ؼ��� KsooPixelDraw.cpp�� �����Ͻʽÿ�.
//

class CKsooPixelDrawApp : public CWinApp
{
public:
	CKsooPixelDrawApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CKsooPixelDrawApp theApp;
