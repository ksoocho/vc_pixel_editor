#include "StdAfx.h"
#include "ImageFileOpen.h"
#include "atlimage.h"
#include "Singleton.h"


CImageFileOpen::CImageFileOpen(void)
{
}

CImageFileOpen::CImageFileOpen(CKsooPixelDrawView *pView, CString p_image_file_path)
{
	CImage Image;

	// 이미지 파일 LOAD
	HRESULT hResult = Image.Load(p_image_file_path);

	if(FAILED(hResult))
	{
		CString strtmp = _T("ERROR - Failed to load!!");
		strtmp += p_image_file_path + _T("\n");
		TRACE(strtmp);
		return;
	}

	// 이미지 정보 읽기
	Singleton *sing = (Singleton *)Singleton::getInstance();

	 sing->g_oldAmountWidth = sing->g_AmountWidth;
	sing->g_oldAmountHeight = sing->g_AmountHeight;
	
	// Image Width/Height
	sing->g_AmountWidth = Image.GetWidth();
	sing->g_AmountHeight = Image.GetHeight();

	//-------------Original Color
    sing->refresh();

	COLORREF rgb;

	 for(int y=0; y<sing->g_AmountHeight; y++)
	{
		for(int x=0; x<sing->g_AmountWidth; x++)
		{
			rgb = Image.GetPixel( x, y );

			sing->g_oriColor[y][x].r = GetRValue(rgb);
			sing->g_oriColor[y][x].g = GetGValue(rgb);
			sing->g_oriColor[y][x].b = GetBValue(rgb);

		}
	}

    pView->m_wndPixel.m_wndView->m_DrawGrid.CreateGridPage
		                                    (pView->m_wndPixel.m_wndView, 
		                                     sing->g_AmountWidth, 
											 sing->g_AmountHeight, 
											 sing->g_cellSize
											);

	if(sing->g_oriColor != NULL){
		pView->m_wndPixel.m_wndView->m_DrawCell.SetDrawItem
			                                     (sing->g_AmountWidth, 
												  sing->g_AmountHeight, 
												  sing->g_cellSize
												 );
	}

	pView->m_pDrawMeasure->m_iUnitSize = sing->g_cellSize;
	pView->m_wndPixel.m_wndView->Invalidate();
	pView->Invalidate();

	sing->g_bStart = false;

    sing->copyOriColor();
	//-----------------

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	CString strStatus1, strStatus2;
	strStatus1.Format(" X 크기 : %d", sing->g_AmountWidth);
	strStatus2.Format(" Y 크기 : %d", sing->g_AmountHeight);
	pMainFrame->m_wndStatusBar.SetPaneText(1, strStatus1);
	pMainFrame->m_wndStatusBar.SetPaneText(2, strStatus2);
	pMainFrame->m_wndStatusBar.SetPaneText(3, " 이동 모드");


}

CImageFileOpen::~CImageFileOpen(void)
{
}
