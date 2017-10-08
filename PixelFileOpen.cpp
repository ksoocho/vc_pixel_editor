#include "StdAfx.h"
#include "PixelFileOpen.h"
#include "Singleton.h"
#include "MainFrm.h"

CPixelFileOpen::CPixelFileOpen(void)
{
}

CPixelFileOpen::CPixelFileOpen(CString str, CKsooPixelDrawView *pView)
{
	Singleton *sing = (Singleton *)Singleton::getInstance();
	
	CString tmp;
	char flag;
	int total = 0;
	FILE *ifp;

	fopen_s(&ifp, (LPCSTR)str, "rb");

	fread(&flag, sizeof(char), 1, ifp);

	if(flag != '&')
	{
		AfxMessageBox("작업용 파일이 아닙니다");
		return;
	}

	fread(&sing->g_AmountWidth, sizeof(short), 1, ifp);
	fread(&sing->g_AmountHeight, sizeof(short), 1, ifp);

	sing->refresh();
	sing->copyOriColor();

	byte v_color_r, v_color_g, v_color_b;

	for(int y=0; y<sing->g_AmountHeight; y++)
	{
		for(int x=0; x<sing->g_AmountWidth; x++)
		{
	        fread(&v_color_r, sizeof(v_color_r), 1, ifp);
		    fread(&v_color_g, sizeof(v_color_g), 1, ifp);
			fread(&v_color_b, sizeof(v_color_b), 1, ifp);

			sing->g_oriColor[y][x].r = v_color_r;
			sing->g_oriColor[y][x].g = v_color_g;
			sing->g_oriColor[y][x].b = v_color_b;
		}
	}

	fclose(ifp);

	sing->g_oldAmountWidth = sing->g_AmountWidth;
	sing->g_oldAmountHeight = sing->g_AmountHeight;

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

	//작업용 이미지 복사
	sing->copyOriColor();
	
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	CString strStatus1, strStatus2;
	strStatus1.Format(" X 크기 : %d", sing->g_AmountWidth);
	strStatus2.Format(" Y 크기 : %d", sing->g_AmountHeight);
	pMainFrame->m_wndStatusBar.SetPaneText(1, strStatus1);
	pMainFrame->m_wndStatusBar.SetPaneText(2, strStatus2);
	pMainFrame->m_wndStatusBar.SetPaneText(3, " 이동 모드");
	
}


CPixelFileOpen::~CPixelFileOpen(void)
{
}

short CPixelFileOpen::ReTrans(char* b)
{
	return ((b[0] << 8) + (b[1] << 0));
}
