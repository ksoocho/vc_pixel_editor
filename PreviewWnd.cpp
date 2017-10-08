// PreviewWnd.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "KsooPixelDraw.h"
#include "PreviewWnd.h"

#include "KsooPixelDrawView.h"
#include "BasicSet.h"
#include <gdiplus.h>
using namespace Gdiplus;
#include "Singleton.h"

// CPreviewWnd
#define SCREEN_SIZEY	58 //스크린 사이즈 격자 갯수
#define SCREEN_SIZEX	70 //스크린 사이즈 격자 갯수

IMPLEMENT_DYNAMIC(CPreviewWnd, CWnd)

CPreviewWnd::CPreviewWnd()
{

}

CPreviewWnd::~CPreviewWnd()
{
}


BEGIN_MESSAGE_MAP(CPreviewWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CPreviewWnd 메시지 처리기입니다.




void CPreviewWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CWnd::OnPaint()을(를) 호출하지 마십시오.


	CKsooPixelDrawView *pView = (CKsooPixelDrawView *)this->GetParent();
	
	Singleton *sing = (Singleton *)Singleton::getInstance();
	
	int pos1 = pView->m_wndPixel.m_wndView->GetScrollPos(SB_HORZ);
	int pos2 = pView->m_wndPixel.m_wndView->GetScrollPos(SB_VERT);

	m_X = (int)(pos1/sing->g_cellSize);
	m_Y = (int)(pos2/sing->g_cellSize);

	int tmpCX = 0;
	int tmpCY = 0;
	double tmpPtX = 0;
	double tmpPtY = 0;

	double rate = 0;
	
	Graphics gClear(dc);
	gClear.Clear(Color(255, 255, 255));

	if(sing->g_bStart){
		HBITMAP hBtm = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_BITMAP_AW));
		Bitmap btmlogo(hBtm, NULL);
		Graphics g(dc);
		g.DrawImage(&btmlogo, 0, 30);

		m_start = true;
		return;
	}
	
	if(m_start == true)
	{
		Graphics g(dc);
		g.Clear(Color(255, 255, 255));
		m_start = false;
	}

	if(sing->g_AmountWidth > PREVIEW_WND_WIDTH || sing->g_AmountHeight > PREVIEW_WND_HEIGHT){
		
		//Preview 이미지 Size 계산 
		if(sing->g_AmountWidth >= sing->g_AmountHeight)
		{
			double tmpA=0; double tmpB=0;

			tmpA = PREVIEW_WND_WIDTH;  
			tmpB = sing->g_AmountWidth; 
			tmpCX = PREVIEW_WND_WIDTH; 
			rate = tmpA/tmpB;
			tmpCY = (int)(sing->g_AmountHeight*rate);

			tmpPtY = (PREVIEW_WND_HEIGHT-tmpCY)/2;
		}
		else if(sing->g_AmountWidth < sing->g_AmountHeight)
		{
			double tmpA=0; double tmpB=0;
			tmpA = PREVIEW_WND_HEIGHT;
			tmpB = sing->g_AmountHeight;
			tmpCY = PREVIEW_WND_HEIGHT;
			rate = tmpA/tmpB;
			tmpCX = (int)(sing->g_AmountWidth*rate);

			tmpPtX = (PREVIEW_WND_WIDTH-tmpCX)/2;
		}

		// Preview Image 원본 생성
		Bitmap btm(sing->g_AmountWidth, sing->g_AmountHeight, PixelFormat24bppRGB);
		try{
			for(int y=0; y<sing->g_AmountHeight; y++)
			{
				for(int x=0; x<sing->g_AmountWidth; x++)
				{
					btm.SetPixel(x, y, Color((byte)sing->g_oriColor[y][x].r, 
						(byte)sing->g_oriColor[y][x].g, (byte)sing->g_oriColor[y][x].b));
				}
			}
		}
		catch(...)
		{
			AfxMessageBox("파일 손상");
			return;
		}

		// Preview Image 크기에 맞게 조정
		Bitmap btm2(tmpCX, tmpCY,  PixelFormat24bppRGB);
		Graphics gp(&btm2);
		gp.DrawImage(&btm, 0, 0, tmpCX, tmpCY);
		Graphics g(dc);
		g.DrawImage(&btm2, PointF((float)tmpPtX, (float)tmpPtY));

		// 선택영역 표시
		Pen penRect2(Color(255, 0, 0), 2);

		double fScSizeX = SCREEN_SIZEX;
		double fScSizeY = SCREEN_SIZEY;
		double tmpSizeX = (fScSizeX*(PREVIEW_WND_WIDTH - 2*tmpPtX))/sing->g_AmountWidth;
		double tmpSizeY = (fScSizeY*(PREVIEW_WND_HEIGHT - 2*tmpPtY))/sing->g_AmountHeight;
		double tmpCodX = (m_X)*(tmpSizeX/fScSizeX);
		double tmpCodY = (m_Y)*(tmpSizeY/fScSizeY);
		double tmpCellSize = sing->g_cellSize;
		double tmpRealSizeX = tmpSizeX*(10/tmpCellSize);
		double tmpRealSizeY = tmpSizeY*(10/tmpCellSize);
		
		g.DrawRectangle(&penRect2, (int)(tmpPtX+tmpCodX)+1, (int)(tmpPtY+tmpCodY)+1, (int)tmpRealSizeX-1, (int)tmpRealSizeY-1);
	}
	else
	{
		Bitmap btm(sing->g_AmountWidth, sing->g_AmountHeight, PixelFormat24bppRGB);
		for(int y=0; y<sing->g_AmountHeight; y++)
		{
			for(int x=0; x<sing->g_AmountWidth; x++)
			{
				btm.SetPixel(x, y, Color((byte)sing->g_oriColor[y][x].r, 
					(byte)sing->g_oriColor[y][x].g, (byte)sing->g_oriColor[y][x].b));
			}
		}
		tmpPtX = (PREVIEW_WND_WIDTH - sing->g_AmountWidth)/2;
		tmpPtY = (PREVIEW_WND_HEIGHT - sing->g_AmountHeight)/2;
		Graphics g(dc);
		g.DrawImage(&btm, PointF((float)tmpPtX, (float)tmpPtY));
		
		Pen penRect1(Color(0, 0, 0), 1);
		Pen penRect2(Color(255, 0, 0), 2);

		//TRACE("%d %d\n", m_X, m_Y);
		m_X += (int)tmpPtX;
		m_Y += (int)tmpPtY;
		//TRACE("%d %d\n", m_X, m_Y);
		double fTen = 10;
		double fA = fTen/sing->g_cellSize;
		double fB = SCREEN_SIZEY;
		int tmpSize1 = (int)(fA*fB);
		fB = SCREEN_SIZEX;
		int tmpSize2 = (int)(fA*fB);

		g.DrawRectangle(&penRect1, (int)tmpPtX, (int)tmpPtY, sing->g_AmountWidth, sing->g_AmountHeight);
		g.DrawRectangle(&penRect2, m_X+1, m_Y+1, tmpSize2, tmpSize1);
	}
}


BOOL CPreviewWnd::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CWnd::OnEraseBkgnd(pDC);
}
