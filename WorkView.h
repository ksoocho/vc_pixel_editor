#pragma once

#include "DrawFreeLine.h"
#include "DrawGrid.h"
#include "DrawCell.h"

// CWorkView 뷰입니다.

#define INCR 1 
#define DECR -1 
#define PREDX 1 
#define PREDY 0 

class CWorkView : public CScrollView
{
	DECLARE_DYNCREATE(CWorkView)

protected:
	CWorkView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CWorkView();

public:
	CDrawGrid m_DrawGrid; //그리드 그리는 객체
	CDrawCell m_DrawCell; //셀 그리는 객체
	CDrawFreeLine m_FreeLine; //프리 라인을 그리는 객체

private:
	//브레젠햄 알고리즘
	CPoint m_Point, m_LPoint;
	int dx, dy, e, e_inc, e_noinc;
	
	//현재 포인트
	CPoint m_ptCurrent;
	
	//이동끌기 기능
	CPoint m_ptLBtnDown, m_ptLBtnUp;
	HCURSOR m_hIconThumb;
	HCURSOR m_hIconGrub;

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();     // 생성된 후 처음입니다.
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void CWorkView::BresenhamDraw(int x, int y);
	void CWorkView::drawline ( int x1, int y1, int x2, int y2, int pred, int incdec ) ;
	void CWorkView::Bresenham ( int x1, int y1, int x2, int y2 ) ;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


