#include "StdAfx.h"
#include "DrawMeasure.h"
#include "BasicSet.h"

CDrawMeasure::CDrawMeasure(void)
:m_penDrawLine(Color(GRID_LINECLR_R, GRID_LINECLR_G, GRID_LINECLR_B), 1.0f),
m_penDrawPointLine(Color(GRID_LINE_P_CLR_R, GRID_LINE_P_CLR_G, GRID_LINE_P_CLR_B), 1.0f)
{
	m_penDrawLine.SetStartCap(LineCapRound);
    m_penDrawLine.SetEndCap(LineCapRound);
	m_penDrawPointLine.SetStartCap(LineCapRound);
    m_penDrawPointLine.SetEndCap(LineCapRound);
	m_iUnitSize = CELL_SIZE;
	m_iLineAmountX = PIXEL_VIEW_WIDTH/CELL_SIZE;
	m_iLineAmountY = PIXEL_VIEW_HEIGHT/CELL_SIZE;

	m_iStartPointX = 0;
	m_iStartPointY = 0;

	m_Font = new Gdiplus::Font(L"Times New Roman", 7);
	m_Brush = new SolidBrush(Color(0, 0, 0));
}


CDrawMeasure::~CDrawMeasure(void)
{
	delete m_Font;
	delete m_Brush;
}

bool CDrawMeasure::Draw(CDC* pDC, int scrX, int scrY)
{

	Gdiplus::Graphics    grp(pDC->m_hDC);
	MeasureDraw(&grp, scrX, scrY);
 
	return true;
}

void CDrawMeasure::MeasureDraw(Graphics* g, int scrX, int scrY)
{


    

	g->Clear(Color(255, 255, 255));
	m_iStartPointX = (int)(scrX/m_iUnitSize);

	int iDetailX = scrX%m_iUnitSize;

	if(scrX == 0)
	{	
		PointF ptF(48, 17);
		
		g->DrawString(L"0", -1, m_Font, ptF, m_Brush );

		g->DrawLine(&m_penDrawPointLine, 
			        PIXEL_VIEW_LEFTTOP_Y+2, 
					PIXEL_VIEW_LEFTTOP_Y-20, 
					PIXEL_VIEW_LEFTTOP_Y+2, 
					PIXEL_VIEW_LEFTTOP_Y-5);
	}

	if(scrY == 0)
	{
		PointF ptF(17, 46);

		g->DrawString(L"0", -1, m_Font, ptF, m_Brush );

		g->DrawLine(&m_penDrawPointLine, 
			        PIXEL_VIEW_LEFTTOP_X-20, 
					PIXEL_VIEW_LEFTTOP_Y+2, 
					PIXEL_VIEW_LEFTTOP_X-5, 
					PIXEL_VIEW_LEFTTOP_Y+2);
	}

	int v_gap = 10;

	if (m_iUnitSize == 1)
	{
		v_gap = 50;
	} else if (m_iUnitSize == 2) {
		v_gap = 10;
	} else {
		v_gap = 5;
	}

	for(int i=PIXEL_VIEW_LEFTTOP_X-iDetailX+2+m_iUnitSize, ct = m_iStartPointX+1; i<=PIXEL_VIEW_RIGHTBOTTOM_X-m_iUnitSize; i+=m_iUnitSize, ct++)
	{
		if(ct%v_gap == 0)
		{
			//unicode·Î conversion
			CString str;
			str.Format("%d", ct);
			USES_CONVERSION;

			WCHAR *string = A2W((LPCSTR)str);
			
			PointF ptF((float)i-(str.GetLength()*m_Font->GetSize())/2, 
				       (float)PIXEL_VIEW_LEFTTOP_Y-34);
			
			g->DrawString(string, -1, m_Font, ptF, m_Brush );

			g->DrawLine(&m_penDrawPointLine, 
				        i, 
						PIXEL_VIEW_LEFTTOP_Y-20, 
						i, 
						PIXEL_VIEW_LEFTTOP_Y-5);
			continue;
		}
		g->DrawLine(&m_penDrawLine, 
			        i, 
					PIXEL_VIEW_LEFTTOP_Y-15, 
					i, 
					PIXEL_VIEW_LEFTTOP_Y-5);
	}

	m_iStartPointY = (int)(scrY/m_iUnitSize);

	int iDetailY = scrY%m_iUnitSize;

	for(int i=PIXEL_VIEW_LEFTTOP_Y-iDetailY+2+m_iUnitSize, ct = m_iStartPointY+1; i<=PIXEL_VIEW_RIGHTBOTTOM_Y-m_iUnitSize; i+=m_iUnitSize, ct++)
	{
		if(ct%v_gap == 0)		{
			CString str;
			str.Format("%d", ct);
			USES_CONVERSION;
			WCHAR *string = A2W((LPCSTR)str);
			
			PointF ptF((float)PIXEL_VIEW_LEFTTOP_Y-34, 
				       (float)i-(str.GetLength()*m_Font->GetSize())/2);

			g->DrawString(string, -1, m_Font, ptF, m_Brush );

			g->DrawLine(&m_penDrawPointLine, 
				        PIXEL_VIEW_LEFTTOP_X-20, 
						i, 
						PIXEL_VIEW_LEFTTOP_X-5, 
						i);
			continue;
		}

		g->DrawLine(&m_penDrawLine, 
			        PIXEL_VIEW_LEFTTOP_X-15, 
					i, 
					PIXEL_VIEW_LEFTTOP_X-5, 
					i);
	}

	g->Flush();
}
