#include "StdAfx.h"
#include "DrawGrid.h"
#include "WorkView.h"
#include "Singleton.h"

#include <gdiplus.h>
using namespace Gdiplus;

CDrawGrid::CDrawGrid(void):
m_penDrawLine(Color(GRID_LINECLR_R, GRID_LINECLR_G, GRID_LINECLR_B), 0.2f),
m_penDrawPointLine(Color(GRID_LINE_P_CLR_R, GRID_LINE_P_CLR_G, GRID_LINE_P_CLR_B), 0.2f),
m_colorBG(GRID_BG_COLOR_R, GRID_BG_COLOR_G, GRID_BG_COLOR_B),
m_lpGridGrp(NULL)
{
	m_iCellSize = CELL_SIZE;
	m_iAmountX = 0;
	m_iAmountY = 0;
	m_penDrawLine.SetStartCap(LineCapRound);
    m_penDrawLine.SetEndCap(LineCapRound);
	m_penDrawPointLine.SetStartCap(LineCapRound);
    m_penDrawPointLine.SetEndCap(LineCapRound);
}

CDrawGrid::~CDrawGrid(void)
{
	delete m_lpGridGrp;
}

void CDrawGrid::SetCellSize(int x)
{
	m_iCellSize = x;
}

void CDrawGrid::setAmountXY(int x, int y)
{
	m_iAmountX = x;
	m_iAmountY = y;
}

bool CDrawGrid::Draw(CDC* pDC)
{
	Graphics    grp(pDC->m_hDC);

	SetGridDrawLine(&grp);
 
	return true;
}

void CDrawGrid::CreateGridPage(CWorkView *pView, int xAmt, int yAmt, int cs)
{
	
	m_iAmountX = xAmt;
	m_iAmountY = yAmt;
	m_iCellSize = cs;
	m_cx = m_iAmountX*m_iCellSize+1;
	m_cy = m_iAmountY*m_iCellSize+1;

	pView->SetScrollSizes(MM_TEXT, CSize(m_cx, m_cy));
}

bool CDrawGrid::SetGridDrawLine(Graphics *g)
{	

	COLORREF v_line_color,v_origin_line_color;
	COLORREF v_point_line_color, v_origin_point_line_color;

	v_line_color = ((COLORREF)(((BYTE)(GRID_LINECLR_B)|((WORD)((BYTE)(GRID_LINECLR_G))<<8))|(((DWORD)(BYTE)(GRID_LINECLR_R))<<16)|(((DWORD)(BYTE)(0))<<24)));
	v_point_line_color = ((COLORREF)(((BYTE)(GRID_LINE_P_CLR_B)|((WORD)((BYTE)(GRID_LINE_P_CLR_G))<<8))|(((DWORD)(BYTE)(GRID_LINE_P_CLR_R))<<16)|(((DWORD)(BYTE)(0))<<24)));
	
	v_origin_line_color = ((COLORREF)(((BYTE)(GRID_LINECLR_B)|((WORD)((BYTE)(GRID_LINECLR_G))<<8))|(((DWORD)(BYTE)(GRID_LINECLR_R))<<16)|(((DWORD)(BYTE)(255))<<24)));
	v_origin_point_line_color = ((COLORREF)(((BYTE)(GRID_LINE_P_CLR_B)|((WORD)((BYTE)(GRID_LINE_P_CLR_G))<<8))|(((DWORD)(BYTE)(GRID_LINE_P_CLR_R))<<16)|(((DWORD)(BYTE)(255))<<24)));

	if ( m_iCellSize < 10 ) 
	{
	  m_penDrawLine.SetColor(v_line_color);
	} else {
	  m_penDrawLine.SetColor(v_origin_line_color);
	}

	if ( m_iCellSize < 2 ) 
	{
	  m_penDrawPointLine.SetColor( v_point_line_color);
	} else {
	  m_penDrawPointLine.SetColor( v_origin_point_line_color);
	}

	//실제 Line 그려주기 -GDI+ 이용
	for(int i=0; i<m_iAmountX; i++)
	{
		if(i == 0)
		{
			g->DrawLine(&m_penDrawPointLine, 0, 0, 0, m_cy);
			continue;
		}
		else if(i % GRID_SEPERATE_LINE == 0)
		{
			g->DrawLine(&m_penDrawPointLine, m_iCellSize*i, 0, m_iCellSize*i, m_cy);
			continue;
		}
		g->DrawLine(&m_penDrawLine, m_iCellSize*i, 0, m_iCellSize*i, m_cy);
	}
	for(int i=0; i<m_iAmountY; i++)
	{
		if( i == 0)
		{
			g->DrawLine(&m_penDrawPointLine, 0, 0, m_cx, 0);
			continue;
		}
		else if( i % GRID_SEPERATE_LINE ==  0)
		{
			g->DrawLine(&m_penDrawPointLine, 0, m_iCellSize*i, m_cx, m_iCellSize*i);
			continue;
		}
		g->DrawLine(&m_penDrawLine, 0, m_iCellSize*i, m_cx, m_iCellSize*i);
	}
	g->DrawLine(&m_penDrawPointLine, 0, m_cy-1, m_cx, m_cy-1);
	g->DrawLine(&m_penDrawPointLine, m_cx-1, 0, m_cx-1, m_cy);
	g->Flush();
	
	return false;
}
