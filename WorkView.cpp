// WorkView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "KsooPixelDraw.h"
#include "KsooPixelDrawView.h"
#include "WorkView.h"


// CWorkView

IMPLEMENT_DYNCREATE(CWorkView, CScrollView)

CWorkView::CWorkView()
{

}

CWorkView::~CWorkView()
{
}


BEGIN_MESSAGE_MAP(CWorkView, CScrollView)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CWorkView 그리기입니다.

void CWorkView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	m_hIconThumb =::LoadIcon(AfxGetInstanceHandle() ,MAKEINTRESOURCE(IDI_ICON_THUMB));
	m_hIconGrub =::LoadIcon(AfxGetInstanceHandle() ,MAKEINTRESOURCE(IDI_ICON_GRUB));

	m_DrawGrid.CreateGridPage(this, 100, 100, 10);
}

void CWorkView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.

	//줄자 그리기
	Singleton *sing = (Singleton *)Singleton::getInstance();
	CKsooPixelDrawView *pView = (CKsooPixelDrawView *)this->GetParent()->GetParent();

	int pos1 = this->GetScrollPos(SB_HORZ);

	pView->m_iScrollPosX = pos1;

	m_DrawCell.m_iFirstX = (int)(pos1/sing->g_cellSize);
	int tmp1 = (int)(sing->g_cellSize*sing->g_AmountWidth/sing->g_cellSize);

	m_DrawCell.m_iLastX = (int)(tmp1 - (int)(PIXEL_VIEW_WIDTH/sing->g_cellSize))-m_DrawCell.m_iFirstX;
	
	//특정 영역만 Invalidate - 깜빡임 방지
	CRect rect1;
	rect1.SetRect(0, 0, PIXEL_VIEW_LEFTTOP_X+PIXEL_VIEW_RIGHTBOTTOM_X, PIXEL_VIEW_LEFTTOP_Y);
	pView->InvalidateRect(&rect1);

	int pos2 = this->GetScrollPos(SB_VERT);
	pView->m_iScrollPosY = pos2;

	pView->m_wndPreview.Invalidate(false);

	m_DrawCell.m_iFirstY = (int)(pos2/sing->g_cellSize);
	int tmp2 = (int)(sing->g_cellSize*sing->g_AmountHeight/sing->g_cellSize);
	m_DrawCell.m_iLastY = (int)(tmp2 - (int)(PIXEL_VIEW_HEIGHT/sing->g_cellSize))-m_DrawCell.m_iFirstY;

	//특정 영역만 Invalidate - 깜빡임 방지
	CRect rect2;	
	rect2.SetRect(0, 0, PIXEL_VIEW_LEFTTOP_Y, PIXEL_VIEW_LEFTTOP_Y+PIXEL_VIEW_RIGHTBOTTOM_Y);
	pView->InvalidateRect(&rect2);

	CDC         dc;
	CDC*        pDrawDC = pDC;
	CBitmap     bitmap;
	CBitmap*    pOldBitmap = 0;

	CRect       client, rect;
	CClientDC   clientDC(this);

    // 그려줘야 할 부분.
	pDC->GetClipBox(client);
	rect = client;
	OnPrepareDC(&clientDC, NULL);
	clientDC.LPtoDP(rect);
	rect.NormalizeRect();

    // 배경색 칠하기
	CBrush brush;
	if (!brush.CreateSolidBrush(m_DrawGrid.GetColorBG().ToCOLORREF()))
		return;

	brush.UnrealizeObject();
	pDrawDC->FillRect(client, &brush);

	//-------------------------------
	// Draw Cell
	//-------------------------------
	m_DrawCell.Draw(pDrawDC);

	//-------------------------------
	// Draw Grid
	//-------------------------------
    m_DrawGrid.Draw(pDrawDC);

	if ( pDrawDC != pDC )
	{
		pDC->SetViewportOrg(0, 0);
		pDC->SetWindowOrg(0, 0);
		pDC->SetMapMode(MM_TEXT);
		dc.SetViewportOrg(0, 0);
		dc.SetWindowOrg(0, 0);
		dc.SetMapMode(MM_TEXT);
		pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &dc, 0, 0, SRCCOPY);
		dc.SelectObject(pOldBitmap);
	}
}


// CWorkView 진단입니다.

#ifdef _DEBUG
void CWorkView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CWorkView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// CWorkView 메시지 처리기입니다.


void CWorkView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CWorkView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CWorkView::BresenhamDraw(int x, int y)
{
	CKsooPixelDrawView *pView = (CKsooPixelDrawView *)this->GetParent()->GetParent();
	
	Singleton *sing = (Singleton *)Singleton::getInstance();

	//---------------------------------------------
    // 있으면 지우고 없으면 그린다.
	//---------------------------------------------
	byte v_color_r, v_color_g, v_color_b;

	if(sing->g_oriColor[y][x].r == 0 &&
	   sing->g_oriColor[y][x].g == 0 &&
	   sing->g_oriColor[y][x].b == 0 ) 
	{
		v_color_r = 255;
		v_color_g = 255;
		v_color_b = 255;
	} else { 
		v_color_r = 0;
		v_color_g = 0;
		v_color_b = 0;
	}

	sing->g_oriColor[y][x].r = v_color_r;
	sing->g_oriColor[y][x].g = v_color_g;
	sing->g_oriColor[y][x].b = v_color_b;

	Invalidate();
	
	pView->m_wndPreview.Invalidate();
}

void CWorkView::drawline ( int x1, int y1, int x2, int y2, int pred, int incdec ) 
{ 
	CClientDC dc(this);
	int i, start, end, var ; 

	if ( pred == PREDX ) 
	{ 
		start = x1 ;  end = x2 ;  var = y1 ; 
	} 

	else 
	{ 
		start = y1 ;  end = y2 ;  var = x1 ; 
	} 

	for ( i = start ; i <= end ; i++ ) 
	{ 
		if ( pred == PREDY ) 
			BresenhamDraw(var, i); 
		else 
			BresenhamDraw(i, var); 

		if ( e < 0 )  e += e_noinc ; 
		else 
		{ 
			var += incdec ; 
			e += e_inc ; 
		} 
	} 

} 

void CWorkView::Bresenham ( int x1, int y1, int x2, int y2 ) 
{ 
	CClientDC dc(this);
	int t, i ; 
	if ( x1 > x2 ) 
	{ 
		t = x1 ; x1 = x2 ; x2 = t ; 
		t = y1 ; y1 = y2 ; y2 = t ; 
	} 

	dx = x2 - x1 ; dy = y2 - y1 ; 

	if ( dx == 0 ) /* vertical line */ 
	{ 

		if ( y1 > y2 ) 
		{ 
			t = y1 ; y1 = y2 ; y2 = t ; 
		} 
		for ( i = y1 ; i <= y2 ; i++ ) 
			BresenhamDraw(x1, i); 
	return ; 
	} 

  

	if ( dy == 0 )  /* horizontal line */ 
	{ 
		for ( i = x1 ; i < x2 ; i++ ) 
			BresenhamDraw(i, y1);
	return ; 

	} 

	/* 0 < m < 1 */ 
	if ( dy < dx && dy > 0 ) 
	{ 
		e_noinc = 2 * dy ; 
		e = 2 * dy - dx ; 
		e_inc = 2 * ( dy - dx ) ; 
		drawline ( x1, y1, x2, y2, PREDX, INCR ) ; 
	} 

	/* m = 1 */ 
	if ( dy == dx && dy > 0 ) 
	{ 
		e_noinc = 2 * dy ; 
		e = 2 * dy - dx ; 
		e_inc = 2 * ( dy - dx ) ; 
		drawline ( x1, y1, x2, y2, PREDX, INCR ) ; 
	} 

	/* 1 < m < infinity */ 
	if ( dy > dx && dy > 0 ) 
	{ 
		e_noinc = 2 * dx ; 
		e = 2 * dx - dy ; 
		e_inc = 2 * ( dx - dy ) ; 
		drawline ( x1, y1, x2, y2, PREDY, INCR ) ; 
	} 

	/* 0 > m > -1 */ 
	if ( -dy < dx && dy < 0 ) 
	{ 
		dy = -dy ; 
		e_noinc = 2 * dy ; 
		e = 2 * dy - dx ; 
		e_inc = 2 * ( dy - dx ) ; 
		drawline ( x1, y1, x2, y2, PREDX, DECR ) ; 
	} 

	/* m = -1 */ 
	if ( dy == -dx && dy < 0 ) 
	{ 
		dy = -dy ; 
		e_noinc = ( 2 * dy ) ; 
		e = 2 * dy - dx ; 
		e_inc = 2 * ( dy - dx ) ; 
		drawline ( x1, y1, x2, y2, PREDX, DECR ) ; 
	} 

	/* -1 > m > 0 */ 
	if ( -dy > dx && dy < 0 ) 
	{ 
		dx = -dx ; 
		e_noinc = - ( 2*dx ) ; e = 2 * dx - dy ; 
		e_inc = - 2 * ( dx - dy ) ; 
		drawline ( x2, y2, x1, y1, PREDY, DECR ) ; 
	} 

} 

void CWorkView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(m_ptCurrent == point){
		return;
	}
	m_ptCurrent = point;

	Singleton *sing = (Singleton *)Singleton::getInstance();

	CPoint pt;
	CKsooPixelDrawView *pView = (CKsooPixelDrawView *)this->GetParent()->GetParent();
	pt.x = pView->m_iScrollPosX+point.x;
	pt.y = pView->m_iScrollPosY+point.y;
	
	int tmpX, tmpY;
	tmpX = (int)(pt.x/sing->g_cellSize);
	tmpY = (int)(pt.y/sing->g_cellSize);
	
	//TRACE("%d %d\n", tmpX, tmpY);
	//pView->m_wndSatus.m_point.x = tmpX;
	//pView->m_wndSatus.m_point.y = tmpY;
	//pView->m_wndSatus.Invalidate();

	if(sing->g_bDrawMode){
		try{
			if(nFlags == MK_LBUTTON){
				m_Point = m_LPoint;
				m_LPoint.x = tmpX;
				m_LPoint.y = tmpY;

				Bresenham(m_Point.x, m_Point.y, m_LPoint.x, m_LPoint.y);

			}
		}catch(...)
		{
			TRACE("...");
		}
	}
	else
	{
		::SetCursor(m_hIconThumb);
		if(nFlags == MK_LBUTTON){
			::SetCursor(m_hIconGrub);
			m_ptLBtnUp = m_ptLBtnDown;
			m_ptLBtnDown = point;
			int nDifX = m_ptLBtnUp.x - m_ptLBtnDown.x ;
			int nDifY =  m_ptLBtnUp.y - m_ptLBtnDown.y;

			int iCurPosY = this->GetScrollPos(SB_VERT);
			int iCurPosX = this->GetScrollPos(SB_HORZ);

			this->SetScrollPos(SB_VERT, iCurPosY+nDifY);
			this->SetScrollPos(SB_HORZ, iCurPosX+nDifX);
			Invalidate(true);
			//TRACE("%d %d\n", iCurPosX+nDifX, iCurPosY+nDifY);
		}
	}
	//m_FreeLine.MouseMove(nFlags, pt);


	CScrollView::OnMouseMove(nFlags, point);
}


void CWorkView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	Singleton *sing = (Singleton *)Singleton::getInstance();
	
	CString msg;

	sing->g_bStart = false;
	
	if(sing->g_bDrawMode){
		
		CPoint pt;
		CKsooPixelDrawView *pView = (CKsooPixelDrawView *)this->GetParent()->GetParent();
		pt.x = pView->m_iScrollPosX+point.x;
		pt.y = pView->m_iScrollPosY+point.y;
		
		int tmpX, tmpY;
		tmpX = (int)(pt.x/sing->g_cellSize);
		tmpY = (int)(pt.y/sing->g_cellSize);
		
		m_Point.x = tmpX;
		m_Point.y = tmpY;
		m_LPoint = m_Point;

		//msg.Format(_T("Position값: %d, %d "), m_Point.x, m_Point.y);
		//AfxMessageBox(msg);

		BresenhamDraw(tmpX, tmpY);
	}
	else
	{
		::SetCursor(m_hIconThumb);
		m_ptLBtnDown = point;
		m_ptLBtnUp = point;
	}


	CScrollView::OnLButtonDown(nFlags, point);
}


void CWorkView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	Singleton *sing = (Singleton *)Singleton::getInstance();
	
	if(!sing->g_bDrawMode){
		::SetCursor(m_hIconThumb);
	}


	CScrollView::OnLButtonUp(nFlags, point);
}
