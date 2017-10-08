
// MainFrm.h : CMainFrame 클래스의 인터페이스
//

#pragma once
#include "KsooPixelDrawView.h"

const short ZOOMSIZE[8] = {1, 2, 5, 10, 15, 20, 30, 50}; //ZOOM SIZE

class CKsooPixelDrawView ;

class CMainFrame : public CFrameWnd
{
	
protected: // serialization에서만 만들어집니다.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
public:
   CKsooPixelDrawView *m_pView;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 생성된 메시지 맵 함수
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


