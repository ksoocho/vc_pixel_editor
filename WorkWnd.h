#pragma once

#include "WorkView.h"

// CWorkWnd

class CWorkWnd : public CWnd
{
	DECLARE_DYNAMIC(CWorkWnd)

public:
	CWorkWnd();
	virtual ~CWorkWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

public:
	CWorkView* m_wndView;

public:
	CWorkView* CreateView(CRuntimeClass * pViewClass, const RECT & lprect, CCreateContext * pContext);
	void RecalcLayout(void);
	CWorkView* GetActiveView(void);
};


