
// MainFrm.h : CMainFrame Ŭ������ �������̽�
//

#pragma once
#include "KsooPixelDrawView.h"

const short ZOOMSIZE[8] = {1, 2, 5, 10, 15, 20, 30, 50}; //ZOOM SIZE

class CKsooPixelDrawView ;

class CMainFrame : public CFrameWnd
{
	
protected: // serialization������ ��������ϴ�.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Ư���Դϴ�.
public:
   CKsooPixelDrawView *m_pView;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �����Դϴ�.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

public:
	CStatusBar m_wndStatusBar;

public:
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


