
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "KsooPixelDraw.h"
#include "PixelFileOpen.h"
#include "PixelFileSave.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_COMMAND(ID_FILE_NEW, &CMainFrame::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CMainFrame::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CMainFrame::OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &CMainFrame::OnFileSaveAs)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_SEPARATOR,           // 상태 줄 표시기
	//ID_SEPARATOR,           // 상태 줄 표시기
	//ID_SEPARATOR,           // 상태 줄 표시기
	//ID_INDICATOR_CAPS,
	//ID_INDICATOR_NUM,
	//ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{

	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.style &= ~FWS_ADDTOTITLE ; 

	//cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
	//	 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기


void CMainFrame::OnFileNew()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMainFrame::OnFileOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_pView->cmdFileOpen();
}


void CMainFrame::OnFileSave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_pView->cmdFileSave();
}


void CMainFrame::OnFileSaveAs()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	this->SetWindowText("CKS Pixel Editor Version 1.0");

	SetMenu(NULL);

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndStatusBar.SetPaneInfo(1, ID_SEPARATOR, SBPS_NORMAL, 100);
	m_wndStatusBar.SetPaneInfo(2, ID_SEPARATOR, SBPS_NORMAL, 100);
	m_wndStatusBar.SetPaneInfo(3, ID_SEPARATOR, SBPS_NORMAL, 80);
	
	Singleton *sing = (Singleton *)Singleton::getInstance();
	CString strStatus1, strStatus2;
	strStatus1.Format(" X 크기 : %d", sing->g_AmountWidth);
	strStatus2.Format(" Y 크기 : %d", sing->g_AmountHeight);
	m_wndStatusBar.SetPaneText(1, strStatus1);
	m_wndStatusBar.SetPaneText(2, strStatus2);
	m_wndStatusBar.SetPaneText(3, " 이동 모드");

	return 0;
}
