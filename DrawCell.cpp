#include "StdAfx.h"
#include "DrawCell.h"
#include "atlbase.h"

CDrawCell::CDrawCell(void)
{
	m_iAmountX = 100;
	m_iAmountY = 100;
	m_iCellSize = 10;

	m_iFirstX = 0;
	m_iLastX = 0;
	m_iFirstY = 0;
	m_iLastY = 0;

	m_bCell = true;
	m_bCharacter = true;

	//---------------------------------------------cks
    Singleton *sing = (Singleton *)Singleton::getInstance();

	sing->g_oldAmountWidth = sing->g_AmountWidth;
	sing->g_oldAmountHeight = sing->g_AmountHeight;

	sing->g_AmountWidth = m_iAmountX;
	sing->g_AmountHeight = m_iAmountY;

	//Original Color Refresh
	sing->refresh();
	sing->copyOriColor();

    for(int y=0; y<sing->g_AmountHeight; y++)
	{
		for(int x=0; x<sing->g_AmountWidth; x++)
		{
			sing->g_oriColor[y][x].r = 255;
			sing->g_oriColor[y][x].g = 255;
			sing->g_oriColor[y][x].b = 255;
		}
	}
	//---------------------------------------------cks

}

CDrawCell::~CDrawCell(void)
{

}

bool CDrawCell::Draw(CDC *pDC)
{
	Graphics    grp(pDC->m_hDC);

	DrawCell(&grp);
	
	return true;
}

void CDrawCell::DrawCell(Graphics *g)
{
	Singleton *sing = (Singleton *)Singleton::getInstance();

	CString str;
	
	byte byteR = 0; 
	byte byteG = 0; 
	byte byteB = 0;

	//Font 설정
	Gdiplus::Font font10(L"Times New Roman", 7, FontStyleBold); //10 Size
	Gdiplus::Font font15(L"Times New Roman", 8, FontStyleBold); //15 Size
	Gdiplus::Font font20(L"Times New Roman", 10, FontStyleBold); //20 Size
	Gdiplus::Font font30(L"Times New Roman", 12, FontStyleBold); //30 Size
	Gdiplus::Font font50(L"Times New Roman", 15, FontStyleBold); //50 Size

	//배경색
	SolidBrush brush(Color(255, 255, 255));
	SolidBrush brushFont(Color(255, 255, 255)); //Font를 위한 Brush

	if(m_iLastY < 1 ) m_iLastY = 1;
	if(m_iLastX < 1) m_iLastX = 1;
	
	//예외처리
	try{
		for(int y=0+m_iFirstY; y<=m_iAmountY-m_iLastY; y++)
		{
			for(int x=0+m_iFirstX; x<=m_iAmountX-m_iLastX; x++)
			{
				//색실 채크박스에 채크되어 있으면
				if(m_bCell){

					brush.SetColor(Color((byte)sing->g_oriColor[y][x].r,
						                 (byte)sing->g_oriColor[y][x].g, 
										 (byte)sing->g_oriColor[y][x].b));

					g->FillRectangle(&brush, Rect(x*m_iCellSize,
						                          y*m_iCellSize, 
						                          m_iCellSize, 
												  m_iCellSize));
				}

				if(sing->g_cellSize == 5) continue;

			}
		}
	}
	catch(...)
	{
		TRACE("배열의 영역을 벗어남\n");
	}
}

void CDrawCell::SetDrawItem(int AmtX, int AmtY, int cs)
{
	m_iAmountX = AmtX;
	m_iAmountY = AmtY;
	m_iCellSize = cs;
}
