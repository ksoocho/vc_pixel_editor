
// KsooPixelDrawView.cpp : CKsooPixelDrawView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "KsooPixelDraw.h"
#endif

#include "KsooPixelDrawDoc.h"
#include "KsooPixelDrawView.h"
#include "BasicSet.h"
#include "PixelFileOpen.h"
#include "PixelFileSave.h"
#include "GearDraw.h"
#include "ImageBinary.h"
#include "MainFrm.h"
#include "ImageFileOpen.h"
#include "TextImage.h"
#include "atlimage.h"
#include "PathGenerate.h"
#include "ShapeDraw.h"

#include <gdiplus.h>       
using namespace Gdiplus;  

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKsooPixelDrawView

IMPLEMENT_DYNCREATE(CKsooPixelDrawView, CView)

BEGIN_MESSAGE_MAP(CKsooPixelDrawView, CView)
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CKsooPixelDrawView ����/�Ҹ�

CKsooPixelDrawView::CKsooPixelDrawView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_pDrawMeasure = new CDrawMeasure;
	m_iScrollPosX = 0;
	m_iScrollPosY = 0;
}

CKsooPixelDrawView::~CKsooPixelDrawView()
{
}

BOOL CKsooPixelDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CKsooPixelDrawView �׸���

void CKsooPixelDrawView::OnDraw(CDC* pDC)
{
	CKsooPixelDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

	CDC         dc;
	CDC*        pDrawDC = pDC;
	CBitmap     bitmap;
	CBitmap*    pOldBitmap = 0;

	CRect       client, rect;
	CClientDC   clientDC(this);

	pDC->GetClipBox(client);
	rect = client;
	OnPrepareDC(&clientDC, NULL);
	clientDC.LPtoDP(rect);
	rect.NormalizeRect();
	
    // ���� ĥ�ϱ�
	CBrush brush;
	Color color(255, 255, 255);
	if (!brush.CreateSolidBrush(color.ToCOLORREF()))
		return;

	brush.UnrealizeObject();
	pDrawDC->FillRect(client, &brush);

	//--------------------------------------------------------
	//���ݱ׸���
	//--------------------------------------------------------
	m_pDrawMeasure->Draw(pDrawDC, m_iScrollPosX, m_iScrollPosY);

	//--------------------------------------------------------
	// ??
	//--------------------------------------------------------
	if ( pDrawDC != pDC )
	{
		pDC->SetViewportOrg(0, 0);
		pDC->SetWindowOrg(0, 0);
		pDC->SetMapMode(MM_TEXT);
		dc.SetViewportOrg(0, 0);
		dc.SetWindowOrg(0, 0);
		dc.SetMapMode(MM_TEXT);
		pDC->BitBlt(client.left, client.top,
			client.right, client.bottom,
			&dc, 0, 0, SRCCOPY);
		dc.SelectObject(pOldBitmap);
	}
}


// CKsooPixelDrawView ����

#ifdef _DEBUG
void CKsooPixelDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CKsooPixelDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKsooPixelDrawDoc* CKsooPixelDrawView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKsooPixelDrawDoc)));
	return (CKsooPixelDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CKsooPixelDrawView �޽��� ó����


void CKsooPixelDrawView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	//-------------------------------------------------
	// �۾�����
	//-------------------------------------------------
	CRect clientRect;
	clientRect.SetRect(PIXEL_VIEW_LEFTTOP_X, PIXEL_VIEW_LEFTTOP_Y, PIXEL_VIEW_RIGHTBOTTOM_X,  PIXEL_VIEW_RIGHTBOTTOM_Y);

	m_wndPixel.Create(NULL, _T("PixelView"), WS_VISIBLE | WS_CHILD , clientRect, this, 1234);

	//-------------------------------------------------
	// �̸����� ȭ��
	//-------------------------------------------------
	CRect clientPreviewRect;
	clientPreviewRect.SetRect(PREVIEW_WND_LEFTTOP_X, PREVIEW_WND_LEFTTOP_Y, PREVIEW_WND_RIGHTBOTTOM_X, PREVIEW_WND_RIGHTBOttOM_Y);

	m_wndPreview.CreateEx(WS_EX_CLIENTEDGE, NULL, "[ ��ü ���� ]", WS_CHILD | WS_VISIBLE, clientPreviewRect, this, 1235); //IDC_WNDPREVIEW

	//-------------------------------------------------
	// Status ȭ��
	//-------------------------------------------------
	//CRect statusRect;
	//statusRect.SetRect(STATUS_LEFTTOP_X, STATUS_LEFTTOP_Y, STATUS_RIGHTBOTTOM_X, STATUS_RIGHTBOTTOM_Y);
	//m_wndSatus.CreateEx(WS_EX_CLIENTEDGE   , NULL, "[ ��Ȳ ���� ]", WS_CHILD | WS_VISIBLE, statusRect, this, 1236); //ID_WND_STATUS

}


void CKsooPixelDrawView::DoDataExchange(CDataExchange* pDX)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	DDX_Text(pDX,2062,m_intModule );
	DDV_MinMaxInt(pDX,m_intModule,1,20 );

	DDX_Text(pDX,2064,m_intPitchNo );
	DDV_MinMaxInt(pDX,m_intPitchNo,4,100 );
	
	DDX_Text(pDX,2072,m_intBinaryUnity );
	DDV_MinMaxInt(pDX,m_intBinaryUnity,0,255 );

	DDX_Text(pDX,2082,m_intBinaryThreadLow );
	DDV_MinMaxInt(pDX,m_intBinaryThreadLow,0,255 );

	DDX_Text(pDX,2083,m_intBinaryThreadHigh );
	DDV_MinMaxInt(pDX,m_intBinaryThreadHigh,0,255 );

	DDX_Text(pDX,2026,m_intRotateDegree );
	DDV_MinMaxInt(pDX,m_intRotateDegree,0,360 );

	// Rectangle
	DDX_Text(pDX,2131,m_RectTopX );
	DDX_Text(pDX,2132,m_RectTopY );
	DDX_Text(pDX,2133,m_RectBottomX );
	DDX_Text(pDX,2134,m_RectBottomY );

	// Circle
	DDX_Text(pDX,2141,m_CircleX );
	DDX_Text(pDX,2142,m_CircleY );
	DDX_Text(pDX,2144,m_CircleR );

	DDX_Text(pDX,2111,m_strFontName );

	DDX_Text(pDX,2121,m_strTextString );

	// G-Code
	DDX_Text(pDX,3006,m_GcodeStartX);
	DDV_MinMaxInt(pDX,m_GcodeStartX,0,100 );

	DDX_Text(pDX,3007,m_GcodeStartY);
	DDV_MinMaxInt(pDX,m_GcodeStartY,0,100 );

	DDX_Text(pDX,3032,m_GcodeHorizonPart);
	DDV_MinMaxInt(pDX,m_GcodeHorizonPart,0,200 );

	DDX_Text(pDX,3035,m_GcodeVerticalPart);
	DDV_MinMaxInt(pDX,m_GcodeVerticalPart,0,200 );

	DDX_Text(pDX,3043,m_GcodeDrawlineThick);
	DDV_MinMaxInt(pDX,m_GcodeDrawlineThick,0,10 );

	DDX_Text(pDX,3046,m_GcodeScale);

	DDX_Text(pDX,3051,m_GcodeDepth);

	DDX_Text(pDX,3061,m_GcodeDepthCount);
	DDV_MinMaxInt(pDX,m_GcodeDepthCount,1,10 );

	DDX_Text(pDX,3071,m_GcodeToolNo);
	DDV_MinMaxInt(pDX,m_GcodeToolNo,1,10 );

	DDX_Text(pDX,3081,m_GcodeIdleTime);
	DDV_MinMaxInt(pDX,m_GcodeIdleTime,1,500 );

	CView::DoDataExchange(pDX);
}

int CKsooPixelDrawView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	// ������ ��ư ����
	m_font.CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,
                                    OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                    DEFAULT_PITCH | FF_SWISS, "����ü");


	//-------------------------------------------------
	// Path List / G Code List
	//-------------------------------------------------
	int list_top_x = PREVIEW_WND_LEFTTOP_X+220;
	int list_top_y = PREVIEW_WND_LEFTTOP_Y;
	int list_bottom_x = list_top_x + 100;
	int list_bottom_y = PREVIEW_WND_RIGHTBOttOM_Y;

	CRect rect_list = CRect(list_top_x, list_top_y, list_bottom_x, list_bottom_y);
	m_List = new CListBox;
	m_List->Create(WS_CHILD | WS_VISIBLE | WS_BORDER, rect_list, this, 1237);
	m_List->SetFont(&m_font, TRUE);
	m_List->AddString("");

	int glist_top_x = list_bottom_x + 10;
	int glist_top_y = list_top_y;
	int glist_bottom_x = glist_top_x + 120;
	int glist_bottom_y = list_bottom_y;

	CRect rect_glist = CRect(glist_top_x, glist_top_y, glist_bottom_x, glist_bottom_y);
	m_GList = new CListBox;
	m_GList->Create(WS_CHILD | WS_VISIBLE | WS_BORDER, rect_glist, this, 1238);
	m_GList->SetFont(&m_font, TRUE);
	m_GList->AddString("");

	//-------------------------------------------------
	// Button
	//-------------------------------------------------
	int l_btn_lefttop_x, l_btn_lefttop_y, l_btn_rightbottom_x, l_btn_rightbottom_y ;
	int r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y ;

	//--------------------------------------------------------
	// ���� ���� ��ư
	//--------------------------------------------------------
	l_btn_lefttop_x = BUTTON_LEFTTOP_X ;
	l_btn_lefttop_y = BUTTON_LEFTTOP_Y ;	
	l_btn_rightbottom_x = l_btn_lefttop_x + BUTTON_SMALL_WIDTH;
	l_btn_rightbottom_y = l_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect1 = CRect(l_btn_lefttop_x, l_btn_lefttop_y, l_btn_rightbottom_x, l_btn_rightbottom_y);
	btnFileOpen.Create(_T("File Open"), WS_CHILD|WS_VISIBLE, rect1, this, 2040);
	btnFileOpen.SetFont(&m_font, TRUE);

	//--------------------------------------------------------
	// ���� ���� ��ư
	//--------------------------------------------------------
	r_btn_lefttop_x = l_btn_rightbottom_x  + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = l_btn_lefttop_y ;	
	r_btn_rightbottom_x = r_btn_lefttop_x + BUTTON_SMALL_WIDTH;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect2 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	btnFileSave.Create(_T("File Save"), WS_CHILD|WS_VISIBLE, rect2, this, 2050);
	btnFileSave.SetFont(&m_font, TRUE);

	//--------------------------------------------------------
	// �����ư
	//--------------------------------------------------------
	r_btn_lefttop_x = r_btn_rightbottom_x  + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = r_btn_lefttop_y ;	
	r_btn_rightbottom_x = r_btn_lefttop_x + BUTTON_SMALL_WIDTH;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect99 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	btnExit.Create(_T("����"), WS_CHILD|WS_VISIBLE, rect99, this, 2999);
	btnExit.SetFont(&m_font, TRUE);

	//--------------------------------------------------------
	// ��庯ȯ��ư
	//--------------------------------------------------------
	l_btn_lefttop_x = l_btn_lefttop_x ;
	l_btn_lefttop_y = l_btn_rightbottom_y  + BUTTON_VERTICAL_SPACE ;	
	l_btn_rightbottom_x = l_btn_lefttop_x + BUTTON_SMALL_WIDTH;
	l_btn_rightbottom_y = l_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect3 = CRect(l_btn_lefttop_x, l_btn_lefttop_y, l_btn_rightbottom_x, l_btn_rightbottom_y);
	btnMode.Create(_T("���"), WS_CHILD|WS_VISIBLE, rect3, this, 2030);
	btnMode.SetFont(&m_font, TRUE);

	//--------------------------------------------------------
	// �̹��� Ȯ�� ��ư
	//--------------------------------------------------------
	r_btn_lefttop_x = l_btn_rightbottom_x  + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = l_btn_lefttop_y ;	
	r_btn_rightbottom_x = r_btn_lefttop_x + BUTTON_SMALL_WIDTH;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect41 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	btnBinLarge.Create(_T("Ȯ��"), WS_CHILD|WS_VISIBLE, rect41, this, 2010);
	btnBinLarge.SetFont(&m_font, TRUE);

	//--------------------------------------------------------
	// �̹��� ��� ��ư
	//--------------------------------------------------------
	r_btn_lefttop_x = r_btn_rightbottom_x  + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = r_btn_lefttop_y ;	
	r_btn_rightbottom_x = r_btn_lefttop_x + BUTTON_SMALL_WIDTH;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect42 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	btnBinSmall.Create(_T("���"), WS_CHILD|WS_VISIBLE, rect42, this, 2020);
	btnBinSmall.SetFont(&m_font, TRUE);

	//--------------------------------------------------------
	// �̹��� ���� ��ư
	//--------------------------------------------------------
	l_btn_lefttop_x = l_btn_lefttop_x ;
	l_btn_lefttop_y = l_btn_rightbottom_y  + BUTTON_VERTICAL_SPACE ;	
	l_btn_rightbottom_x = l_btn_lefttop_x + BUTTON_SMALL_WIDTH;
	l_btn_rightbottom_y = l_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect43 = CRect(l_btn_lefttop_x, l_btn_lefttop_y, l_btn_rightbottom_x, l_btn_rightbottom_y);
	btnBinReverse.Create(_T("����"), WS_CHILD|WS_VISIBLE, rect43, this, 2021);
	btnBinReverse.SetFont(&m_font, TRUE);

	//--------------------------------------------------------
	// �̹��� ���ϴ�Ī ��ư
	//--------------------------------------------------------
	r_btn_lefttop_x = l_btn_rightbottom_x  + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = l_btn_lefttop_y ;	
	r_btn_rightbottom_x = r_btn_lefttop_x + BUTTON_SMALL_WIDTH;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect44 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	btnBinMirrorTB.Create(_T("����"), WS_CHILD|WS_VISIBLE, rect44, this, 2022);
	btnBinMirrorTB.SetFont(&m_font, TRUE);

	//--------------------------------------------------------
	// �̹��� �¿��Ī ��ư
	//--------------------------------------------------------
	r_btn_lefttop_x = r_btn_rightbottom_x  + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = r_btn_lefttop_y ;	
	r_btn_rightbottom_x = r_btn_lefttop_x + BUTTON_SMALL_WIDTH;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect45 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	btnBinMirrorLR.Create(_T("�¿�"), WS_CHILD|WS_VISIBLE, rect45, this, 2023);
	btnBinMirrorLR.SetFont(&m_font, TRUE);

	//--------------------------------------------------------
	// �̹��� ȸ��
	//--------------------------------------------------------
	l_btn_lefttop_x = l_btn_lefttop_x ;
	l_btn_lefttop_y = l_btn_rightbottom_y  + BUTTON_VERTICAL_SPACE ;	
	l_btn_rightbottom_x = l_btn_lefttop_x + BUTTON_WIDTH;
	l_btn_rightbottom_y = l_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect46 = CRect(l_btn_lefttop_x, l_btn_lefttop_y, l_btn_rightbottom_x, l_btn_rightbottom_y);
	btnBinRotate.Create(_T("ȸ��"), WS_CHILD|WS_VISIBLE, rect46, this, 2024);
	btnBinRotate.SetFont(&m_font, TRUE);

	//---------------------------------
	// ȸ������
	//---------------------------------
	r_btn_lefttop_x = l_btn_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = l_btn_lefttop_y ;
	r_btn_rightbottom_x = r_btn_lefttop_x + 50;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect47 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	stRotateVal.Create(_T("����"), WS_CHILD|WS_VISIBLE, rect47, this, 2025);
	stRotateVal.SetFont(&m_font, TRUE);

	r_btn_lefttop_x = r_btn_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = r_btn_lefttop_y ;
	r_btn_rightbottom_x = r_btn_lefttop_x + 30;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect48 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	edtRotateVal.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_NUMBER, rect48, this, 2026);
	edtRotateVal.SetFont(&m_font, TRUE);

    //--------------------------------------------------------
	// �̹��� ��ư(9)
	//--------------------------------------------------------
	l_btn_lefttop_x = l_btn_lefttop_x ;
	l_btn_lefttop_y = l_btn_rightbottom_y  + BUTTON_VERTICAL_SPACE ;	
	l_btn_rightbottom_x = l_btn_lefttop_x + BUTTON_WIDTH;
	l_btn_rightbottom_y = l_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect9 = CRect(l_btn_lefttop_x, l_btn_lefttop_y, l_btn_rightbottom_x, l_btn_rightbottom_y);
	btnImageOpen.Create(_T("�̹�������"), WS_CHILD|WS_VISIBLE, rect9, this, 2090);
	btnImageOpen.SetFont(&m_font, TRUE);

	//--------------------------------------------------------
	// �������� Unit ��ư(7)
	//--------------------------------------------------------
	l_btn_lefttop_x = l_btn_lefttop_x ;
	l_btn_lefttop_y = l_btn_rightbottom_y  + BUTTON_VERTICAL_SPACE ;	
	l_btn_rightbottom_x = l_btn_lefttop_x + BUTTON_WIDTH;
	l_btn_rightbottom_y = l_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect7 = CRect(l_btn_lefttop_x, l_btn_lefttop_y, l_btn_rightbottom_x, l_btn_rightbottom_y);
	btnBinary.Create(_T("����(Unity)"), WS_CHILD|WS_VISIBLE, rect7, this, 2070);
	btnBinary.SetFont(&m_font, TRUE);

	//---------------------------------
	// �������� ���ϰ�
	//---------------------------------
	r_btn_lefttop_x = l_btn_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = l_btn_lefttop_y ;
	r_btn_rightbottom_x = r_btn_lefttop_x + 50;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect72 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	edtBinaryVal.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_NUMBER, rect72, this, 2072);
	edtBinaryVal.SetFont(&m_font, TRUE);

	//--------------------------------------------------------
	// �������� Thread ��ư(8)
	//--------------------------------------------------------
	l_btn_lefttop_x = l_btn_lefttop_x ;
	l_btn_lefttop_y = l_btn_rightbottom_y  + BUTTON_VERTICAL_SPACE ;	
	l_btn_rightbottom_x = l_btn_lefttop_x + BUTTON_WIDTH;
	l_btn_rightbottom_y = l_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect8 = CRect(l_btn_lefttop_x, l_btn_lefttop_y, l_btn_rightbottom_x, l_btn_rightbottom_y);
	btnBinaryThread.Create(_T("����(Thread)"), WS_CHILD|WS_VISIBLE, rect8, this, 2080);
	btnBinaryThread.SetFont(&m_font, TRUE);

	//---------------------------------
	// �������� Thread ��
	//---------------------------------
	r_btn_lefttop_x = l_btn_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = l_btn_lefttop_y ;
	r_btn_rightbottom_x = r_btn_lefttop_x + 50;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect82 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	edtBinaryThreadLow.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_NUMBER, rect82, this, 2082);
	edtBinaryThreadLow.SetFont(&m_font, TRUE);

	r_btn_lefttop_x = r_btn_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = r_btn_lefttop_y ;
	r_btn_rightbottom_x = r_btn_lefttop_x + 30;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;
	 
	CRect rect83 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	edtBinaryThreadHigh.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_NUMBER, rect83, this, 2083);
	edtBinaryThreadHigh.SetFont(&m_font, TRUE);

	//--------------------------------------------------------
	// ��� ����� ��ư(6)
	//--------------------------------------------------------
	l_btn_lefttop_x = l_btn_lefttop_x ;
	l_btn_lefttop_y = l_btn_rightbottom_y  + BUTTON_VERTICAL_SPACE ;	
	l_btn_rightbottom_x = l_btn_lefttop_x + BUTTON_WIDTH;
	l_btn_rightbottom_y = l_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect6 = CRect(l_btn_lefttop_x, l_btn_lefttop_y, l_btn_rightbottom_x, l_btn_rightbottom_y);
	btnGear.Create(_T("������"), WS_CHILD|WS_VISIBLE, rect6, this, 2060);
	btnGear.SetFont(&m_font, TRUE);

	//---------------------------------
	// ��� �Է°�(Module)
	//---------------------------------
	r_btn_lefttop_x = l_btn_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = l_btn_lefttop_y ;
	r_btn_rightbottom_x = r_btn_lefttop_x + 50;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect61 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	stGearModule.Create(_T("Module"), WS_CHILD|WS_VISIBLE, rect61, this, 2061);
	stGearModule.SetFont(&m_font, TRUE);

	r_btn_lefttop_x = r_btn_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = r_btn_lefttop_y ;
	r_btn_rightbottom_x = r_btn_lefttop_x + 30;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect62 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	edtGearModule.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_NUMBER, rect62, this, 2062);
	edtGearModule.SetFont(&m_font, TRUE);

	//---------------------------------
	// ��� �Է°�(Pitch)
	//---------------------------------
	r_btn_lefttop_x = r_btn_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = r_btn_lefttop_y ;
	r_btn_rightbottom_x = r_btn_lefttop_x + 40;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect63 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	stPitchNo.Create(_T("Pitch"), WS_CHILD|WS_VISIBLE, rect63, this, 2063);
	stPitchNo.SetFont(&m_font, TRUE);

	r_btn_lefttop_x = r_btn_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = r_btn_lefttop_y ;
	r_btn_rightbottom_x = r_btn_lefttop_x + 30;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect64 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	edtPitchNo.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_NUMBER, rect64, this, 2064);
	edtPitchNo.SetFont(&m_font, TRUE);

	//-------------------------------------------------------
	// �簢�� / ���� Position
	//--------------------------------------------------------
	// Top Prompt
	l_btn_lefttop_x = l_btn_lefttop_x ;
	l_btn_lefttop_y = l_btn_rightbottom_y  + BUTTON_VERTICAL_SPACE ;	
	l_btn_rightbottom_x = l_btn_lefttop_x + 40;
	l_btn_rightbottom_y = l_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect2135 = CRect(l_btn_lefttop_x, l_btn_lefttop_y, l_btn_rightbottom_x, l_btn_rightbottom_y);
	stRectTop.Create(_T("Top"), WS_CHILD|WS_VISIBLE, rect2135, this, 2135);
	stRectTop.SetFont(&m_font, TRUE);

	// Top X
	r_btn_lefttop_x = l_btn_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = l_btn_lefttop_y ;
	r_btn_rightbottom_x = r_btn_lefttop_x + 30;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect2131 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	edtRectTopX.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_NUMBER, rect2131, this, 2131);
	edtRectTopX.SetFont(&m_font, TRUE);

	// Top Y
    r_btn_lefttop_x = r_btn_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = r_btn_lefttop_y ;
	r_btn_rightbottom_x = r_btn_lefttop_x + 30;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect2132 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	edtRectTopY.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_NUMBER, rect2132, this, 2132);
	edtRectTopY.SetFont(&m_font, TRUE);

	// Bottom Prompt
    r_btn_lefttop_x = r_btn_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = r_btn_lefttop_y ;
	r_btn_rightbottom_x = r_btn_lefttop_x + 40;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect2136 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	stRectBottom.Create(_T("Bottom"), WS_CHILD|WS_VISIBLE, rect2136, this, 2136);
	stRectBottom.SetFont(&m_font, TRUE);

	// Bottom X
	r_btn_lefttop_x = r_btn_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = r_btn_lefttop_y ;
	r_btn_rightbottom_x = r_btn_lefttop_x + 30;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect2133 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	edtRectBottomX.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_NUMBER, rect2133, this, 2133);
	edtRectBottomX.SetFont(&m_font, TRUE);

	// Bottom Y
    r_btn_lefttop_x = r_btn_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = r_btn_lefttop_y ;
	r_btn_rightbottom_x = r_btn_lefttop_x + 30;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect2134 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	edtRectBottomY.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_NUMBER, rect2134, this, 2134);
	edtRectBottomY.SetFont(&m_font, TRUE);

	//-------------------------------------------------------
	// �簢�� �׸���
	//--------------------------------------------------------
	l_btn_lefttop_x = l_btn_lefttop_x ;
	l_btn_lefttop_y = l_btn_rightbottom_y  + BUTTON_VERTICAL_SPACE ;	
	l_btn_rightbottom_x = l_btn_lefttop_x + BUTTON_SMALL_WIDTH;
	l_btn_rightbottom_y = l_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect2130 = CRect(l_btn_lefttop_x, l_btn_lefttop_y, l_btn_rightbottom_x, l_btn_rightbottom_y);
	btnRect.Create(_T("Rect"), WS_CHILD|WS_VISIBLE, rect2130, this, 2130);
	btnRect.SetFont(&m_font, TRUE);

	//-------------------------------------------------------
	// ���� �׸���
	//--------------------------------------------------------
    r_btn_lefttop_x = l_btn_rightbottom_x  + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = l_btn_lefttop_y ;	
	r_btn_rightbottom_x = r_btn_lefttop_x + BUTTON_SMALL_WIDTH;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect2137 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	btnLine.Create(_T("Line"), WS_CHILD|WS_VISIBLE, rect2137, this, 2137);
	btnLine.SetFont(&m_font, TRUE);

	//-------------------------------------------------------
	// Round Rect �׸���
	//--------------------------------------------------------
    r_btn_lefttop_x = r_btn_rightbottom_x  + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = r_btn_lefttop_y ;	
	r_btn_rightbottom_x = r_btn_lefttop_x + BUTTON_SMALL_WIDTH;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect2138 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	btnRoundRect.Create(_T("Round"), WS_CHILD|WS_VISIBLE, rect2138, this, 2138);
	btnRoundRect.SetFont(&m_font, TRUE);

	//--------------------------------------------------------
	// �� �׸���
	//--------------------------------------------------------
	l_btn_lefttop_x = l_btn_lefttop_x ;
	l_btn_lefttop_y = l_btn_rightbottom_y  + BUTTON_VERTICAL_SPACE ;	
	l_btn_rightbottom_x = l_btn_lefttop_x + BUTTON_SMALL_WIDTH;
	l_btn_rightbottom_y = l_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect2140 = CRect(l_btn_lefttop_x, l_btn_lefttop_y, l_btn_rightbottom_x, l_btn_rightbottom_y);
	btnCircle.Create(_T("Circle"), WS_CHILD|WS_VISIBLE, rect2140, this, 2140);
	btnCircle.SetFont(&m_font, TRUE);

	// Circle X
	r_btn_lefttop_x = l_btn_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = l_btn_lefttop_y ;
	r_btn_rightbottom_x = r_btn_lefttop_x + 30;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect2141 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	edtCircleX.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_NUMBER, rect2141, this, 2141);
	edtCircleX.SetFont(&m_font, TRUE);

	// Circle Y
    r_btn_lefttop_x = r_btn_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = r_btn_lefttop_y ;
	r_btn_rightbottom_x = r_btn_lefttop_x + 30;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect2142 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	edtCircleY.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_NUMBER, rect2142, this, 2142);
	edtCircleY.SetFont(&m_font, TRUE);

	//---------------------------------
	// �� ������
	//---------------------------------
	r_btn_lefttop_x = r_btn_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = r_btn_lefttop_y ;
	r_btn_rightbottom_x = r_btn_lefttop_x + 40;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect2143 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	stCircleR.Create(_T("Radius"), WS_CHILD|WS_VISIBLE, rect2143, this, 2143);
	stCircleR.SetFont(&m_font, TRUE);

	r_btn_lefttop_x = r_btn_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = r_btn_lefttop_y ;
	r_btn_rightbottom_x = r_btn_lefttop_x + 30;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect2144 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	edtCircleR.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_NUMBER, rect2144, this, 2144);
	edtCircleR.SetFont(&m_font, TRUE);

    //--------------------------------------------------------
	// �ؽ�Ʈ Font ���� ��ư(10)
	//--------------------------------------------------------
	l_btn_lefttop_x = l_btn_lefttop_x ;
	l_btn_lefttop_y = l_btn_rightbottom_y  + BUTTON_VERTICAL_SPACE ;	
	l_btn_rightbottom_x = l_btn_lefttop_x + BUTTON_WIDTH;
	l_btn_rightbottom_y = l_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect101 = CRect(l_btn_lefttop_x, l_btn_lefttop_y, l_btn_rightbottom_x, l_btn_rightbottom_y);
	btnFontSelect.Create(_T("Font"), WS_CHILD|WS_VISIBLE, rect101, this, 2110);
	btnFontSelect.SetFont(&m_font, TRUE);

	// Font Disaplay
	r_btn_lefttop_x = l_btn_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = l_btn_lefttop_y ;
	r_btn_rightbottom_x = r_btn_lefttop_x + 150;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect1011 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	stFontName.Create(_T(""), WS_CHILD|WS_VISIBLE, rect1011, this, 2111);
	stFontName.SetFont(&m_font, TRUE);

    //--------------------------------------------------------
	// �ؽ�Ʈ �̹��� ��ȯ ��ư
	//--------------------------------------------------------
	l_btn_lefttop_x = l_btn_lefttop_x ;
	l_btn_lefttop_y = l_btn_rightbottom_y  + BUTTON_VERTICAL_SPACE ;	
	l_btn_rightbottom_x = l_btn_lefttop_x + BUTTON_WIDTH;
	l_btn_rightbottom_y = l_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect102 = CRect(l_btn_lefttop_x, l_btn_lefttop_y, l_btn_rightbottom_x, l_btn_rightbottom_y);
	btnTextImage.Create(_T("Text Image"), WS_CHILD|WS_VISIBLE, rect102, this, 2120);
	btnTextImage.SetFont(&m_font, TRUE);

	r_btn_lefttop_x = l_btn_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_btn_lefttop_y = l_btn_lefttop_y ;
	r_btn_rightbottom_x = r_btn_lefttop_x + 170;
	r_btn_rightbottom_y = r_btn_lefttop_y + BUTTON_HEIGHT;

	CRect rect103 = CRect(r_btn_lefttop_x, r_btn_lefttop_y, r_btn_rightbottom_x, r_btn_rightbottom_y);
	edtTextString.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER, rect103, this, 2121);
	edtTextString.SetFont(&m_font, TRUE);

	//--------------------------------------------------------
	// G Code ����
	//--------------------------------------------------------
	int l_gcode_lefttop_x, l_gcode_lefttop_y, l_gcode_rightbottom_x, l_gcode_rightbottom_y ;
	int r_gcode_lefttop_x, r_gcode_lefttop_y, r_gcode_rightbottom_x, r_gcode_rightbottom_y ;

	//--------------------------------------------------------
	// Path Save ��ư
	//--------------------------------------------------------
	l_gcode_lefttop_x = GCODE_LEFTTOP_X ;
	l_gcode_lefttop_y = GCODE_LEFTTOP_Y ;	
	l_gcode_rightbottom_x = l_gcode_lefttop_x + BUTTON_WIDTH;
	l_gcode_rightbottom_y = l_gcode_lefttop_y + BUTTON_HEIGHT;

	CRect rect3008 = CRect(l_gcode_lefttop_x, l_gcode_lefttop_y, l_gcode_rightbottom_x, l_gcode_rightbottom_y);
	btnPathFile.Create(_T("Path File"), WS_CHILD|WS_VISIBLE, rect3008, this, 3008);
	btnPathFile.SetFont(&m_font, TRUE);

	//--------------------------------------------------------
	// G-Code Save ��ư
	//--------------------------------------------------------
	r_gcode_lefttop_x = l_gcode_rightbottom_x  + BUTTON_HORIZON_SPACE;
	r_gcode_lefttop_y = l_gcode_lefttop_y ;	
	r_gcode_rightbottom_x = r_gcode_lefttop_x + BUTTON_WIDTH;
	r_gcode_rightbottom_y = r_gcode_lefttop_y + BUTTON_HEIGHT;

	CRect rect3009 = CRect(r_gcode_lefttop_x, r_gcode_lefttop_y, r_gcode_rightbottom_x, r_gcode_rightbottom_y);
	btnGcodeFile.Create(_T("G-Code File"), WS_CHILD|WS_VISIBLE, rect3009, this, 3009);
	btnGcodeFile.SetFont(&m_font, TRUE);

	//--------------------------------------------------------
	// Start Point 
	//--------------------------------------------------------
	l_gcode_lefttop_x = l_gcode_lefttop_x ;
	l_gcode_lefttop_y = l_gcode_rightbottom_y  + BUTTON_VERTICAL_SPACE ;	
	l_gcode_rightbottom_x = l_gcode_lefttop_x + BUTTON_WIDTH;
	l_gcode_rightbottom_y = l_gcode_lefttop_y + BUTTON_HEIGHT;

	CRect rect3005 = CRect(l_gcode_lefttop_x, l_gcode_lefttop_y, l_gcode_rightbottom_x, l_gcode_rightbottom_y);
	stGcodeStart.Create(_T("Start Point"), WS_CHILD|WS_VISIBLE, rect3005, this, 3005);
	stGcodeStart.SetFont(&m_font, TRUE);

	// Start Point - X
	r_gcode_lefttop_x = l_gcode_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_gcode_lefttop_y = l_gcode_lefttop_y ;
	r_gcode_rightbottom_x = r_gcode_lefttop_x + 30;
	r_gcode_rightbottom_y = r_gcode_lefttop_y + BUTTON_HEIGHT;

	CRect rect3006 = CRect(r_gcode_lefttop_x, r_gcode_lefttop_y, r_gcode_rightbottom_x, r_gcode_rightbottom_y);
	edtGcodeStartX.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_NUMBER, rect3006, this, 3006);
	edtGcodeStartX.SetFont(&m_font, TRUE);

	// Start Point - Y
	r_gcode_lefttop_x = r_gcode_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_gcode_lefttop_y = r_gcode_lefttop_y ;
	r_gcode_rightbottom_x = r_gcode_lefttop_x + 30;
	r_gcode_rightbottom_y = r_gcode_lefttop_y + BUTTON_HEIGHT;

	CRect rect3007 = CRect(r_gcode_lefttop_x, r_gcode_lefttop_y, r_gcode_rightbottom_x, r_gcode_rightbottom_y);
	edtGcodeStartY.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_NUMBER, rect3007, this, 3007);
	edtGcodeStartY.SetFont(&m_font, TRUE);

	//--------------------------------------------------------
	// Ⱦ�� ��ư
	//--------------------------------------------------------
	l_gcode_lefttop_x = l_gcode_lefttop_x ;
	l_gcode_lefttop_y = l_gcode_rightbottom_y  + BUTTON_VERTICAL_SPACE ;	
	l_gcode_rightbottom_x = l_gcode_lefttop_x + BUTTON_WIDTH;
	l_gcode_rightbottom_y = l_gcode_lefttop_y + BUTTON_HEIGHT;

	CRect rect3010 = CRect(l_gcode_lefttop_x, l_gcode_lefttop_y, l_gcode_rightbottom_x, l_gcode_rightbottom_y);
	btnGcodeHorizon.Create(_T("Horizon"), WS_CHILD|WS_VISIBLE, rect3010, this, 3010);
	btnGcodeHorizon.SetFont(&m_font, TRUE);

	//---------------------------------
	// Ⱦ�� Width
	//---------------------------------
	r_gcode_lefttop_x = l_gcode_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_gcode_lefttop_y = l_gcode_lefttop_y ;
	r_gcode_rightbottom_x = r_gcode_lefttop_x + 50;
	r_gcode_rightbottom_y = r_gcode_lefttop_y + BUTTON_HEIGHT;

	CRect rect3031 = CRect(r_gcode_lefttop_x, r_gcode_lefttop_y, r_gcode_rightbottom_x, r_gcode_rightbottom_y);
	stGcodeHorizonPart.Create(_T("Width"), WS_CHILD|WS_VISIBLE, rect3031, this, 3031);
	stGcodeHorizonPart.SetFont(&m_font, TRUE);

	r_gcode_lefttop_x = r_gcode_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_gcode_lefttop_y = r_gcode_lefttop_y ;
	r_gcode_rightbottom_x = r_gcode_lefttop_x + 30;
	r_gcode_rightbottom_y = r_gcode_lefttop_y + BUTTON_HEIGHT;

	CRect rect3032 = CRect(r_gcode_lefttop_x, r_gcode_lefttop_y, r_gcode_rightbottom_x, r_gcode_rightbottom_y);
	edtGcodeHorizonPart.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_NUMBER, rect3032, this, 3032);
	edtGcodeHorizonPart.SetFont(&m_font, TRUE);

	//--------------------------------------------------------
	// ���� ��ư
	//--------------------------------------------------------
	l_gcode_lefttop_x = l_gcode_lefttop_x ;
	l_gcode_lefttop_y = l_gcode_rightbottom_y  + BUTTON_VERTICAL_SPACE ;	
	l_gcode_rightbottom_x = l_gcode_lefttop_x + BUTTON_WIDTH;
	l_gcode_rightbottom_y = l_gcode_lefttop_y + BUTTON_HEIGHT;

	CRect rect3020 = CRect(l_gcode_lefttop_x, l_gcode_lefttop_y, l_gcode_rightbottom_x, l_gcode_rightbottom_y);
	btnGcodeVertical.Create(_T("Vertical"), WS_CHILD|WS_VISIBLE, rect3020, this, 3020);
	btnGcodeVertical.SetFont(&m_font, TRUE);

	//---------------------------------
	// ���� Height
	//---------------------------------
	r_gcode_lefttop_x = l_gcode_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_gcode_lefttop_y = l_gcode_lefttop_y ;
	r_gcode_rightbottom_x = r_gcode_lefttop_x + 50;
	r_gcode_rightbottom_y = r_gcode_lefttop_y + BUTTON_HEIGHT;

	CRect rect3034 = CRect(r_gcode_lefttop_x, r_gcode_lefttop_y, r_gcode_rightbottom_x, r_gcode_rightbottom_y);
	stGcodeVerticalPart.Create(_T("Height"), WS_CHILD|WS_VISIBLE, rect3034, this, 3034);
	stGcodeVerticalPart.SetFont(&m_font, TRUE);

	r_gcode_lefttop_x = r_gcode_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_gcode_lefttop_y = r_gcode_lefttop_y ;
	r_gcode_rightbottom_x = r_gcode_lefttop_x + 30;
	r_gcode_rightbottom_y = r_gcode_lefttop_y + BUTTON_HEIGHT;

	CRect rect3035 = CRect(r_gcode_lefttop_x, r_gcode_lefttop_y, r_gcode_rightbottom_x, r_gcode_rightbottom_y);
	edtGcodeVerticalPart.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_NUMBER, rect3035, this, 3035);
	edtGcodeVerticalPart.SetFont(&m_font, TRUE);


	//--------------------------------------------------------
	// �κ�Ⱦ��
	//--------------------------------------------------------
	//l_gcode_lefttop_x = l_gcode_lefttop_x ;
	//l_gcode_lefttop_y = l_gcode_rightbottom_y  + BUTTON_VERTICAL_SPACE ;	
	//l_gcode_rightbottom_x = l_gcode_lefttop_x + BUTTON_WIDTH;
	//l_gcode_rightbottom_y = l_gcode_lefttop_y + BUTTON_HEIGHT;

	//CRect rect3030 = CRect(l_gcode_lefttop_x, l_gcode_lefttop_y, l_gcode_rightbottom_x, l_gcode_rightbottom_y);
	//btnGcodeHorizonPart.Create(_T("�κ�Ⱦ��"), WS_CHILD|WS_VISIBLE, rect3030, this, 3030);
	//btnGcodeHorizonPart.SetFont(&m_font, TRUE);



	//--------------------------------------------------------
	// �κ�����
	//--------------------------------------------------------
	//l_gcode_lefttop_x = l_gcode_lefttop_x ;
	//l_gcode_lefttop_y = l_gcode_rightbottom_y  + BUTTON_VERTICAL_SPACE ;	
	//l_gcode_rightbottom_x = l_gcode_lefttop_x + BUTTON_WIDTH;
	//l_gcode_rightbottom_y = l_gcode_lefttop_y + BUTTON_HEIGHT;

	//CRect rect3033 = CRect(l_gcode_lefttop_x, l_gcode_lefttop_y, l_gcode_rightbottom_x, l_gcode_rightbottom_y);
	//btnGcodeVerticalPart.Create(_T("�κ�����"), WS_CHILD|WS_VISIBLE, rect3033, this, 3033);
	//btnGcodeVerticalPart.SetFont(&m_font, TRUE);

	//--------------------------------------------------------
	// OutLine
	//--------------------------------------------------------
	l_gcode_lefttop_x = l_gcode_lefttop_x ;
	l_gcode_lefttop_y = l_gcode_rightbottom_y  + BUTTON_VERTICAL_SPACE ;	
	l_gcode_rightbottom_x = l_gcode_lefttop_x + BUTTON_WIDTH;
	l_gcode_rightbottom_y = l_gcode_lefttop_y + BUTTON_HEIGHT;

	CRect rect3040 = CRect(l_gcode_lefttop_x, l_gcode_lefttop_y, l_gcode_rightbottom_x, l_gcode_rightbottom_y);
	btnGcodeOutline.Create(_T("Outline"), WS_CHILD|WS_VISIBLE, rect3040, this, 3040);
	btnGcodeOutline.SetFont(&m_font, TRUE);

	//--------------------------------------------------------
	// DrawLine
	//--------------------------------------------------------
	l_gcode_lefttop_x = l_gcode_lefttop_x ;
	l_gcode_lefttop_y = l_gcode_rightbottom_y  + BUTTON_VERTICAL_SPACE ;	
	l_gcode_rightbottom_x = l_gcode_lefttop_x + BUTTON_WIDTH;
	l_gcode_rightbottom_y = l_gcode_lefttop_y + BUTTON_HEIGHT;

	CRect rect3041 = CRect(l_gcode_lefttop_x, l_gcode_lefttop_y, l_gcode_rightbottom_x, l_gcode_rightbottom_y);
	btnGcodeDrawline.Create(_T("Drawline"), WS_CHILD|WS_VISIBLE, rect3041, this, 3041);
	btnGcodeDrawline.SetFont(&m_font, TRUE);

	r_gcode_lefttop_x = l_gcode_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_gcode_lefttop_y = l_gcode_lefttop_y ;
	r_gcode_rightbottom_x = r_gcode_lefttop_x + 50;
	r_gcode_rightbottom_y = r_gcode_lefttop_y + BUTTON_HEIGHT;

	CRect rect3043 = CRect(r_gcode_lefttop_x, r_gcode_lefttop_y, r_gcode_rightbottom_x, r_gcode_rightbottom_y);
	edtGcodeDrawlineThick.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_NUMBER, rect3043, this, 3043);
	edtGcodeDrawlineThick.SetFont(&m_font, TRUE);

	//---------------------------------
	// DrawLine Thick
	//---------------------------------
	//r_gcode_lefttop_x = l_gcode_rightbottom_x + BUTTON_HORIZON_SPACE;
	//r_gcode_lefttop_y = l_gcode_lefttop_y ;
	//r_gcode_rightbottom_x = r_gcode_lefttop_x + 50;
	//r_gcode_rightbottom_y = r_gcode_lefttop_y + BUTTON_HEIGHT;

	//CRect rect3042 = CRect(r_gcode_lefttop_x, r_gcode_lefttop_y, r_gcode_rightbottom_x, r_gcode_rightbottom_y);
	//stGcodeDrawlineThick.Create(_T("Thick"), WS_CHILD|WS_VISIBLE, rect3042, this, 3042);
	//stGcodeDrawlineThick.SetFont(&m_font, TRUE);

	//--------------------------------------------------------
	// Scale
	//--------------------------------------------------------
	l_gcode_lefttop_x = l_gcode_lefttop_x ;
	l_gcode_lefttop_y = l_gcode_rightbottom_y  + BUTTON_VERTICAL_SPACE ;	
	l_gcode_rightbottom_x = l_gcode_lefttop_x + BUTTON_WIDTH;
	l_gcode_rightbottom_y = l_gcode_lefttop_y + BUTTON_HEIGHT;

	CRect rect3045 = CRect(l_gcode_lefttop_x, l_gcode_lefttop_y, l_gcode_rightbottom_x, l_gcode_rightbottom_y);
	stGcodeScale.Create(_T("Scale(%)"), WS_CHILD|WS_VISIBLE, rect3045, this, 3045);
	stGcodeScale.SetFont(&m_font, TRUE);

	r_gcode_lefttop_x = l_gcode_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_gcode_lefttop_y = l_gcode_lefttop_y ;
	r_gcode_rightbottom_x = r_gcode_lefttop_x + 50;
	r_gcode_rightbottom_y = r_gcode_lefttop_y + BUTTON_HEIGHT;

	CRect rect3046 = CRect(r_gcode_lefttop_x, r_gcode_lefttop_y, r_gcode_rightbottom_x, r_gcode_rightbottom_y);
	edtGcodeScale.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_NUMBER, rect3046, this, 3046);
	edtGcodeScale.SetFont(&m_font, TRUE);


	//--------------------------------------------------------
	// �������
	//--------------------------------------------------------
	l_gcode_lefttop_x = l_gcode_lefttop_x ;
	l_gcode_lefttop_y = l_gcode_rightbottom_y  + BUTTON_VERTICAL_SPACE ;	
	l_gcode_rightbottom_x = l_gcode_lefttop_x + BUTTON_WIDTH;
	l_gcode_rightbottom_y = l_gcode_lefttop_y + BUTTON_HEIGHT;

	CRect rect3050 = CRect(l_gcode_lefttop_x, l_gcode_lefttop_y, l_gcode_rightbottom_x, l_gcode_rightbottom_y);
	stGcodeDepth.Create(_T("Depth"), WS_CHILD|WS_VISIBLE, rect3050, this, 3050);
	stGcodeDepth.SetFont(&m_font, TRUE);

	r_gcode_lefttop_x = l_gcode_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_gcode_lefttop_y = l_gcode_lefttop_y ;
	r_gcode_rightbottom_x = r_gcode_lefttop_x + 50;
	r_gcode_rightbottom_y = r_gcode_lefttop_y + BUTTON_HEIGHT;

	CRect rect3051 = CRect(r_gcode_lefttop_x, r_gcode_lefttop_y, r_gcode_rightbottom_x, r_gcode_rightbottom_y);
	edtGcodeDepth.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_NUMBER, rect3051, this, 3051);
	edtGcodeDepth.SetFont(&m_font, TRUE);

	//--------------------------------------------------------
	// ������� Count
	//--------------------------------------------------------
	l_gcode_lefttop_x = l_gcode_lefttop_x ;
	l_gcode_lefttop_y = l_gcode_rightbottom_y  + BUTTON_VERTICAL_SPACE ;	
	l_gcode_rightbottom_x = l_gcode_lefttop_x + BUTTON_WIDTH;
	l_gcode_rightbottom_y = l_gcode_lefttop_y + BUTTON_HEIGHT;

	CRect rect3060 = CRect(l_gcode_lefttop_x, l_gcode_lefttop_y, l_gcode_rightbottom_x, l_gcode_rightbottom_y);
	stGcodeDepthCount.Create(_T("Depth Count"), WS_CHILD|WS_VISIBLE, rect3060, this, 3060);
	stGcodeDepthCount.SetFont(&m_font, TRUE);

	r_gcode_lefttop_x = l_gcode_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_gcode_lefttop_y = l_gcode_lefttop_y ;
	r_gcode_rightbottom_x = r_gcode_lefttop_x + 50;
	r_gcode_rightbottom_y = r_gcode_lefttop_y + BUTTON_HEIGHT;

	CRect rect3061 = CRect(r_gcode_lefttop_x, r_gcode_lefttop_y, r_gcode_rightbottom_x, r_gcode_rightbottom_y);
	edtGcodeDepthCount.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_NUMBER, rect3061, this, 3061);
	edtGcodeDepthCount.SetFont(&m_font, TRUE);

	//--------------------------------------------------------
	// Tool No
	//--------------------------------------------------------
	l_gcode_lefttop_x = l_gcode_lefttop_x ;
	l_gcode_lefttop_y = l_gcode_rightbottom_y  + BUTTON_VERTICAL_SPACE ;	
	l_gcode_rightbottom_x = l_gcode_lefttop_x + BUTTON_WIDTH;
	l_gcode_rightbottom_y = l_gcode_lefttop_y + BUTTON_HEIGHT;

	CRect rect3070 = CRect(l_gcode_lefttop_x, l_gcode_lefttop_y, l_gcode_rightbottom_x, l_gcode_rightbottom_y);
	stGcodeToolNo.Create(_T("Tool Size"), WS_CHILD|WS_VISIBLE, rect3070, this, 3070);
	stGcodeToolNo.SetFont(&m_font, TRUE);

	r_gcode_lefttop_x = l_gcode_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_gcode_lefttop_y = l_gcode_lefttop_y ;
	r_gcode_rightbottom_x = r_gcode_lefttop_x + 50;
	r_gcode_rightbottom_y = r_gcode_lefttop_y + BUTTON_HEIGHT;

	CRect rect3071 = CRect(r_gcode_lefttop_x, r_gcode_lefttop_y, r_gcode_rightbottom_x, r_gcode_rightbottom_y);
	edtGcodeToolNo.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_NUMBER, rect3071, this, 3071);
	edtGcodeToolNo.SetFont(&m_font, TRUE);

	//--------------------------------------------------------
	// Idle Time
	//--------------------------------------------------------
	l_gcode_lefttop_x = l_gcode_lefttop_x ;
	l_gcode_lefttop_y = l_gcode_rightbottom_y  + BUTTON_VERTICAL_SPACE ;	
	l_gcode_rightbottom_x = l_gcode_lefttop_x + BUTTON_WIDTH;
	l_gcode_rightbottom_y = l_gcode_lefttop_y + BUTTON_HEIGHT;

	CRect rect3080 = CRect(l_gcode_lefttop_x, l_gcode_lefttop_y, l_gcode_rightbottom_x, l_gcode_rightbottom_y);
	stGcodeIdleTime.Create(_T("Idle Time"), WS_CHILD|WS_VISIBLE, rect3080, this, 3080);
	stGcodeIdleTime.SetFont(&m_font, TRUE);

	r_gcode_lefttop_x = l_gcode_rightbottom_x + BUTTON_HORIZON_SPACE;
	r_gcode_lefttop_y = l_gcode_lefttop_y ;
	r_gcode_rightbottom_x = r_gcode_lefttop_x + 50;
	r_gcode_rightbottom_y = r_gcode_lefttop_y + BUTTON_HEIGHT;

	CRect rect3081 = CRect(r_gcode_lefttop_x, r_gcode_lefttop_y, r_gcode_rightbottom_x, r_gcode_rightbottom_y);
	edtGcodeIdleTime.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_NUMBER, rect3081, this, 3081);
	edtGcodeIdleTime.SetFont(&m_font, TRUE);


	// Default �� Setting
	m_intModule = 10;
	m_intPitchNo = 16;	
	m_intBinaryUnity = 100;	
	m_intBinaryThreadLow = 50;	
	m_intBinaryThreadHigh = 200;
	m_intRotateDegree = 0;

	// Rect
	m_RectTopX = 0;
	m_RectTopY = 0;
	m_RectBottomX = 0;
	m_RectBottomY = 0;

    // Circle
	m_CircleX = 0;
	m_CircleY = 0;
	m_CircleR = 0;

	// G-Code
	m_GcodeStartX = 0;
	m_GcodeStartY = 0;

	m_GcodeHorizonPart = 0;
	m_GcodeVerticalPart = 0;
	m_GcodeDrawlineThick = 1;
	m_GcodeScale = 100;
	m_GcodeDepth = 0.3;
	m_GcodeDepthCount = 1;
	m_GcodeToolNo = 1;
	m_GcodeIdleTime = 100;

	UpdateData(FALSE); 

	return 0;
}


BOOL CKsooPixelDrawView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	//-------------------------------
	// Ȯ���ư ���� ���
	//-------------------------------
	if( wParam == 2010 )	{
		cmdZoomIn();

	//-------------------------------
	// ��ҹ�ư ���� ���
	//-------------------------------
	} else if( wParam == 2020 )	{
		cmdZoomOut();

	//-------------------------------
	// ������ư ���� ���
	//-------------------------------
	} else if( wParam == 2021 )	{
		cmdBinaryReverse("RV");

	//-------------------------------
	// ���Ϲ�ư ���� ���
	//-------------------------------
	} else if( wParam == 2022 )	{
		cmdBinaryReverse("MTB");

	//-------------------------------
	// �¿��ư ���� ���
	//-------------------------------
	} else if( wParam == 2023 )	{
		cmdBinaryReverse("MLR");

	//-------------------------------
	// ȸ����ư ���� ���
	//-------------------------------
	} else if( wParam == 2024 )	{
		cmdBinaryReverse("ROT");

	//-------------------------------
	// ��庯ȯ ��ư ���� ���
	//-------------------------------
	} else if( wParam == 2030 )	{
		cmdModeChange();
		
    } else if( wParam == 2040 )	{
	    cmdFileOpen();

    } else if( wParam == 2050 )	{
	    cmdFileSave();

	} else if( wParam == 2060 )	{
	    cmdDrawGear();

	} else if( wParam == 2070 )	{
	    cmdImageBinary();

	} else if( wParam == 2080 )	{
	    cmdImageBinaryThread();

	} else if( wParam == 2090 )	{
	    cmdImageOpen();

	} else if( wParam == 2110 )	{
	    cmdTextFontSelect();

	} else if( wParam == 2120 )	{
	    cmdTextImageGen();

	//-------------------------------
	// �簢�� ��ư ���� ���
	//-------------------------------
	} else if( wParam == 2130 )	{
		UpdateData(TRUE);
	    CShapeDraw drawShape(this);
		drawShape.RectangleDraw(m_RectTopX,m_RectTopY,m_RectBottomX,m_RectBottomY);

	//-------------------------------
	// LINE ��ư ���� ���
	//-------------------------------
	} else if( wParam == 2137 )	{
		UpdateData(TRUE);
	    CShapeDraw drawShape(this);
		drawShape.LineDraw(m_RectTopX,m_RectTopY,m_RectBottomX,m_RectBottomY);

	//-------------------------------
	// LINE ��ư ���� ���
	//-------------------------------
	} else if( wParam == 2138 )	{
		UpdateData(TRUE);
	    CShapeDraw drawShape(this);
		drawShape.RoundRectDraw(m_RectTopX,m_RectTopY,m_RectBottomX,m_RectBottomY);

	//-------------------------------
	// �� ��ư ���� ���
	//-------------------------------
	} else if( wParam == 2140 )	{

		UpdateData(TRUE);
	    CShapeDraw drawShape(this);
		drawShape.CircleDraw(m_CircleX, m_CircleY, m_CircleR);

    } else if( wParam == 2999 )	{
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
	//-------------------------------
	// Path File ��ư ���� ���
	//-------------------------------
	} else if( wParam == 3008 )	{

		CPathGenerate pathGen(this);
		pathGen.PathFileSave();

	//-------------------------------
	// G Code File ��ư ���� ���
	//-------------------------------
	} else if( wParam == 3009 )	{

		CPathGenerate pathGen(this);
		pathGen.GcodeFileSave();

	//-------------------------------
	// Horizon ��ư ���� ���
	//-------------------------------
	} else if( wParam == 3010 )	{

		UpdateData(TRUE);

		CPathGenerate pathGen(this);

		// Horizon Process ó��
		pathGen.MainHorizon();

	//-------------------------------
	// Vertical ��ư ���� ���
	//-------------------------------
	} else if( wParam == 3020 )	{

		UpdateData(TRUE);

		CPathGenerate pathGen(this);

		// Vertical Process ó��
		pathGen.MainVertical();

	//-------------------------------
	// Out Line��ư ���� ���
	//-------------------------------
	} else if( wParam == 3040 )	{
		
		UpdateData(TRUE);

		CPathGenerate pathGen(this);

		// �ܰ��� ���� Process ó��
		pathGen.MainOutLine();

	//-------------------------------
	// Trace Line��ư ���� ���
	//-------------------------------
	} else if( wParam == 3041 )	{
		
		UpdateData(TRUE);

		CPathGenerate pathGen(this);

		// Line ���� Process ó��
		pathGen.MainTraceLine();

	}

	return CView::OnCommand(wParam, lParam);
}


//--------------------------------
// �۾����Ͽ���
//--------------------------------
void CKsooPixelDrawView::cmdFileOpen(void)
{
	char szFilter[] = "STI File(*.sti)|*.sti|";

	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if(IDOK == fileDlg.DoModal())
	{
		CPixelFileOpen open(fileDlg.GetPathName(), this);
	}
}


//--------------------------------
// �۾���������
//--------------------------------
void CKsooPixelDrawView::cmdFileSave(void)
{
	Singleton *sing = (Singleton *)Singleton::getInstance();

	char szFilter[] = "STI File(*.sti)|";

	CFileDialog fileDlg(FALSE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	
	if(IDOK == fileDlg.DoModal())
	{
		CPixelFileSave pixelFileSave(fileDlg.GetPathName());
	}
}


//--------------------------------
// �۾������ȯ(�׸���/�̵�)
//--------------------------------
void CKsooPixelDrawView::cmdModeChange(void)
{
	Singleton *sing = (Singleton *)Singleton::getInstance();
	CString str;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if(!sing->g_bDrawMode){
		if(IDYES == AfxMessageBox("�׸��� ���� ��ȯ�Ͻðڽ��ϱ�?", MB_YESNO | MB_ICONQUESTION))
		{
			sing->g_bDrawMode = true;
			str.Format(" �׸��� ���");
			pMainFrame->m_wndStatusBar.SetPaneText(3, str);
		}
		else
		{
			sing->g_bDrawMode = false;
			str.Format(" �̵� ���");
			pMainFrame->m_wndStatusBar.SetPaneText(3, str);
		}
	}
	else if(sing->g_bDrawMode)
	{
		if(IDYES == AfxMessageBox("�̵� ���� ��ȯ�Ͻðڽ��ϱ�?", MB_YESNO | MB_ICONQUESTION))
		{
			sing->g_bDrawMode = false;
			str.Format(" �̵� ���");
			pMainFrame->m_wndStatusBar.SetPaneText(3, str);
		}
		else
		{
			sing->g_bDrawMode = true;
			str.Format(" �׸��� ���");
			pMainFrame->m_wndStatusBar.SetPaneText(3, str);
		}
	}
}

//-------------------------------------
//  �̹��� Ȯ��
//-------------------------------------
void CKsooPixelDrawView::cmdZoomIn(void)
{
	int tmp = 0;
	Singleton *sing = (Singleton *)Singleton::getInstance();
	for(int i=0; i<8; i++)
	{
		if(ZOOMSIZE[i] == sing->g_cellSize)
		{
			tmp = i;
		}
	}

	tmp++;

	if(tmp < 0) tmp = 0;
	if(tmp > 7) tmp = 7;

	m_wndPixel.m_wndView->m_DrawGrid.CreateGridPage(m_wndPixel.m_wndView, 
		sing->g_AmountWidth, sing->g_AmountHeight, ZOOMSIZE[tmp]);

	if(sing->g_aIndex != NULL){
		m_wndPixel.m_wndView->m_DrawCell.SetDrawItem(sing->g_AmountWidth, sing->g_AmountHeight, ZOOMSIZE[tmp]);
	}
		
	m_pDrawMeasure->m_iUnitSize = ZOOMSIZE[tmp];
	sing->g_cellSize = ZOOMSIZE[tmp];
	m_wndPixel.m_wndView->Invalidate();
	Invalidate();
}

//-------------------------------------
//  �̹��� ���
//-------------------------------------
void CKsooPixelDrawView::cmdZoomOut(void)
{
	int tmp = 0;
	Singleton *sing = (Singleton *)Singleton::getInstance();
	for(int i=0; i<8; i++)
	{
		if(ZOOMSIZE[i] == sing->g_cellSize)
		{
			tmp = i;
		}
	}

	tmp--;

	if(tmp < 0) tmp = 0;
	if(tmp > 7) tmp = 7;

	m_wndPixel.m_wndView->m_DrawGrid.CreateGridPage(m_wndPixel.m_wndView, 
		sing->g_AmountWidth, sing->g_AmountHeight, ZOOMSIZE[tmp]);
	
	if(sing->g_aIndex != NULL){
		m_wndPixel.m_wndView->m_DrawCell.SetDrawItem(sing->g_AmountWidth, sing->g_AmountHeight, ZOOMSIZE[tmp]);
	}

	m_pDrawMeasure->m_iUnitSize = ZOOMSIZE[tmp];
	sing->g_cellSize = ZOOMSIZE[tmp];
	m_wndPixel.m_wndView->Invalidate();
	Invalidate();
}

//-------------------------------------
//  ����/����/�¿� ��ư
//-------------------------------------
void CKsooPixelDrawView::cmdBinaryReverse(CString p_work_code)
{
	UpdateData(TRUE);

	int v_rotate_degree = m_intRotateDegree;
	
	if (p_work_code == "ROT" && ( 0 > v_rotate_degree || v_rotate_degree > 360 ))
	{
		AfxMessageBox("0~360�������� �մϴ�.");
		return;
	}

	CImageBinary open(this,p_work_code, v_rotate_degree);
	
}

//-------------------------------------
//  ��� ������
//-------------------------------------
void CKsooPixelDrawView::cmdDrawGear(void)
{
	UpdateData(TRUE);

	double v_module = m_intModule;
	double v_pitch_no = m_intPitchNo;
	
	CGearDraw gearDraw(this,v_module,v_pitch_no);
	
}

//-------------------------------------
//  ��������(Unit)
//-------------------------------------
void CKsooPixelDrawView::cmdImageBinary(void)
{
	UpdateData(TRUE);

	int v_binary_unity = m_intBinaryUnity;
	
	if ( 0 > v_binary_unity || v_binary_unity > 255 )
	{
		AfxMessageBox("0~255�������� �մϴ�.");
		return;
	}

	CImageBinary open(this,v_binary_unity);
	
}

//-------------------------------------
//  ��������(Thread)
//-------------------------------------
void CKsooPixelDrawView::cmdImageBinaryThread(void)
{
	UpdateData(TRUE);

	int v_binary_thread_low = m_intBinaryThreadLow;
	int v_binary_thread_high = m_intBinaryThreadHigh;
	
	if ( 0 > v_binary_thread_low || v_binary_thread_low > 255 )
	{
		AfxMessageBox("0~255�������� �մϴ�.");
		return;
	}

	if ( 0 > v_binary_thread_high || v_binary_thread_high > 255 )
	{
		AfxMessageBox("0~255�������� �մϴ�.");
		return;
	}

	if ( v_binary_thread_low > v_binary_thread_high )
	{
		AfxMessageBox("High���� Ŀ�� �մϴ�.");
		return;
	}


	CImageBinary open(this,v_binary_thread_low , v_binary_thread_high);
	
}

//-------------------------------------
//  �̹��� ���� ����
//-------------------------------------
void CKsooPixelDrawView::cmdImageOpen(void)
{
	char szFilter[] = "JPG File(*.JPG)|*.JPG|BMP File(*.BMP)|*.BMP|JPEG File(*.JPEG)|*.JPEG|GIF File(*.GIF)|*.GIF|PNG File(*.PNG)|*.PNG|";

	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if(IDOK == fileDlg.DoModal())
	{
		CImageFileOpen open(this, fileDlg.GetPathName());
	}
	
}

//-------------------------------------
//  �ؽ�Ʈ Font ����
//-------------------------------------
void CKsooPixelDrawView::cmdTextFontSelect(void)
{
	UpdateData(TRUE);

    CFontDialog dlg;

	if(m_log.lfFaceName[0] != 0)
	{
		dlg.m_cf.Flags |= CF_EFFECTS | CF_INITTOLOGFONTSTRUCT;
		dlg.m_cf.lpLogFont = &m_log;
	}

	if(dlg.DoModal() != IDOK)
		return;

	dlg.GetCurrentFont(&m_log);

	lfFaceName = m_log.lfFaceName;

	m_strFontName = lfFaceName;

	UpdateData(FALSE);

}

//-------------------------------------
//  �ؽ�Ʈ �̹��� ��ȯ
//-------------------------------------
void CKsooPixelDrawView::cmdTextImageGen(void)
{
	UpdateData(TRUE);

	if ( m_strFontName.IsEmpty() )
	{
		AfxMessageBox("��Ʈ�� �����ϼ���");
		return;
	}

	if ( m_strTextString.IsEmpty() )
	{
		AfxMessageBox("������ �����ϼ���");
		return;
	}

    CTextImage open(this, m_strTextString );
	
}

