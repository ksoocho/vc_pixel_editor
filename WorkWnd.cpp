// WorkWnd.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "KsooPixelDraw.h"
#include "WorkWnd.h"


// CWorkWnd

IMPLEMENT_DYNAMIC(CWorkWnd, CWnd)

CWorkWnd::CWorkWnd()
{

}

CWorkWnd::~CWorkWnd()
{
}


BEGIN_MESSAGE_MAP(CWorkWnd, CWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CWorkWnd 메시지 처리기입니다.




int CWorkWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CRect rect;
	GetClientRect(rect);

	CRuntimeClass* pNewViewClass;
	pNewViewClass =	RUNTIME_CLASS(CWorkView);

	//-------------------------------------------------
	// 작업영역 뷰 생성
	//-------------------------------------------------
	CCreateContext context;
	context.m_pNewViewClass = pNewViewClass;


	CWorkView* pNewView = CreateView(pNewViewClass, rect,  &context);

	if (pNewView != NULL)
	{
		pNewView->ShowWindow(SW_SHOW);
		pNewView->OnInitialUpdate();
		pNewView->SetActiveWindow();

		RecalcLayout();
	}

	return 0;
}


CWorkView* CWorkWnd::CreateView(CRuntimeClass * pViewClass, const RECT & lprect, CCreateContext * pContext)
{
#ifdef _DEBUG
	ASSERT_VALID(this);
	ASSERT(pViewClass != NULL);
	ASSERT(pViewClass->IsDerivedFrom(RUNTIME_CLASS(CWnd)));
	ASSERT(AfxIsValidAddress(pViewClass, sizeof(CRuntimeClass), FALSE));
#endif
	
	BOOL bSendInitialUpdate = FALSE;

	CCreateContext contextT;
	if (pContext == NULL)
	{
		CWorkView* pOldView = NULL;

		if (pOldView != NULL && pOldView->IsKindOf(RUNTIME_CLASS(CWorkView)))
		{
			ASSERT(contextT.m_pCurrentFrame == NULL);
			contextT.m_pLastView = pOldView;
			contextT.m_pCurrentDoc = pOldView->GetDocument();
			if (contextT.m_pCurrentDoc != NULL)
				contextT.m_pNewDocTemplate =
				contextT.m_pCurrentDoc->GetDocTemplate();
		}
		pContext = &contextT;
		bSendInitialUpdate = TRUE;
	}

	CWnd* pWnd;
	TRY
	{
		pWnd = (CWnd*)pViewClass->CreateObject();
		if (pWnd == NULL)
			AfxThrowMemoryException();
	}
	CATCH_ALL(e)
	{
		TRACE0("Out of memory creating a splitter pane.\n");
		return (CWorkView*) NULL;
	}
	END_CATCH_ALL

		ASSERT_KINDOF(CWnd, pWnd);
	ASSERT(pWnd->m_hWnd == NULL);       // 아직 생성되지 않음

	DWORD dwStyle = WS_VISIBLE | WS_CHILD | WS_BORDER;

	CRect rect(lprect);
	if (!pWnd->Create(NULL, NULL, dwStyle,
		rect, this, 0, pContext))
	{
		TRACE0("Warning: couldn't create client pane for splitter.\n");

		return (CWorkView*) NULL;
	}

	m_wndView = (CWorkView*) pWnd;
	return m_wndView;
}

CWorkView* CWorkWnd::GetActiveView(void)
{
	return m_wndView;
}


void CWorkWnd::RecalcLayout(void)
{
	CWnd* pWnd = (CWnd*) GetActiveView();
	CRect rect;
	GetClientRect(&rect);
}