#pragma once

#include "DrawFreeLine.h"
#include "DrawGrid.h"
#include "DrawCell.h"

// CWorkView ���Դϴ�.

#define INCR 1 
#define DECR -1 
#define PREDX 1 
#define PREDY 0 

class CWorkView : public CScrollView
{
	DECLARE_DYNCREATE(CWorkView)

protected:
	CWorkView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CWorkView();

public:
	CDrawGrid m_DrawGrid; //�׸��� �׸��� ��ü
	CDrawCell m_DrawCell; //�� �׸��� ��ü
	CDrawFreeLine m_FreeLine; //���� ������ �׸��� ��ü

private:
	//�극���� �˰���
	CPoint m_Point, m_LPoint;
	int dx, dy, e, e_inc, e_noinc;
	
	//���� ����Ʈ
	CPoint m_ptCurrent;
	
	//�̵����� ���
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
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();     // ������ �� ó���Դϴ�.
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void CWorkView::BresenhamDraw(int x, int y);
	void CWorkView::drawline ( int x1, int y1, int x2, int y2, int pred, int incdec ) ;
	void CWorkView::Bresenham ( int x1, int y1, int x2, int y2 ) ;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


