#include "StdAfx.h"
#include "TextImage.h"
#include "ImageFileOpen.h"
#include "atlimage.h"
#include "Singleton.h"

CTextImage::CTextImage(void)
{
}

CTextImage::CTextImage(CKsooPixelDrawView *pView, CString p_text_string)
{

	CString v_bmp_path_name;
	v_bmp_path_name = _T("c:\\temp\\test.bmp");

    CPaintDC pdc( pView );
    
	CDC clTempDc;    
	CBitmap clBitmap;
    
	//----------------------------------------
	// DC�� �����ؼ� bitmap�� ����
	//----------------------------------------
    clTempDc.CreateCompatibleDC( &pdc );

	//----------------------------------------
    // Set Font
	//----------------------------------------

	TEXTMETRICA t;
    GetTextMetrics(clTempDc,&t);
    SetTextColor(clTempDc, RGB(0,0,0));
    SetBkColor(clTempDc, RGB(255, 255, 255));

	SIZE stHangulSize;
	SIZE stEnglishSize;
	int v_bmp_width, v_bmp_height;

	CFont newFont;

	newFont.CreateFontIndirect(&pView->m_log);
	clTempDc.SelectObject(newFont);

	//�ؽ�Ʈ�� ������ �˾ƿ�
	GetTextExtentPoint32( clTempDc, "A", 1, &stEnglishSize );
    GetTextExtentPoint32( clTempDc, "��", 2, &stHangulSize );

	v_bmp_width = stHangulSize.cx * p_text_string.GetLength() / 2;
	v_bmp_height = stHangulSize.cy;

	//----------------------------------------
    // ��Ʈ�� ����
	//----------------------------------------
	// �ؽ�Ʈ�� ����� �°� ��Ʈ�� ����
    clBitmap.CreateCompatibleBitmap( &clTempDc, v_bmp_width, v_bmp_height );
	clTempDc.PatBlt(0,0,v_bmp_width, v_bmp_height, WHITENESS);

	//�޸�dc�� ��Ʈ�� ����
	 clTempDc.SelectObject(clBitmap);

	// �ؽ�Ʈ �׸�
	TextOut(clTempDc, 0, 0, p_text_string, lstrlen(p_text_string)); 

	//----------------------------------------
	// �̹��� ���� ����
	//----------------------------------------
	CImage image;
	image.Attach(clBitmap);
    image.Save(v_bmp_path_name);

	newFont.DeleteObject();
	DeleteObject(clBitmap);
	DeleteDC(clTempDc);
	DeleteDC(pdc);

	//----------------------------------------
    // �̹��� ���� �б�
	//----------------------------------------

	// �̹��� ���� �б�
	CImageFileOpen(pView,v_bmp_path_name);

	/*

	//CFont* pOldFont=pDC.SelectObject (pView->m_fontText);
	//TEXTMETRIC tm;
	//pDC->GetTextMetrics (&tm);

	//v_bmp_height = tm.tmHeight +tm.tmExternalLeading ;
    //v_bmp_width =	tm.tmAveCharWidth * p_text_string.GetLength() + 20 ;

	clTempDc.FillSolidRect(0,0,v_bmp_width,v_bmp_height,RGB(255,255,255));

	//CString clsData;
    //clsData.Format( "English Font Pixel %dx%d, Hangul Font Pixel %dx%d, BMP %dx%d", 
	//		stEnglishSize.cx, stEnglishSize.cy, stHangulSize.cx, stHangulSize.cy,v_bmp_width, v_bmp_height );

	//AfxMessageBox(clsData);	

	//Set text color
	clTempDc.SetTextColor(RGB(0,0,0));
	
	//draw the text
	clTempDc.SetBkMode(TRANSPARENT);


	CRect rect;
	rect.SetRect (0,0,v_bmp_width,v_bmp_height);

	clTempDc.DrawText(p_text_string,-1, &rect, DT_LEFT|DT_VCENTER );

	//ReleaseDC(&MemDC);

	*/
}





CTextImage::~CTextImage(void)
{
}

