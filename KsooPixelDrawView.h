
// KsooPixelDrawView.h : CKsooPixelDrawView Ŭ������ �������̽�
//

#pragma once

#include "WorkWnd.h"
#include "DrawMeasure.h"
#include "KsooPixelDrawDoc.h"    //cks
#include "PreviewWnd.h"
#include "StatusWnd.h"
#include "MainFrm.h"


class CKsooPixelDrawView : public CView
{
protected: // serialization������ ��������ϴ�.
	CKsooPixelDrawView();
	DECLARE_DYNCREATE(CKsooPixelDrawView)

// Ư���Դϴ�.
public:
	CKsooPixelDrawDoc* GetDocument() const;

// CKS ����
public:
	CWorkWnd m_wndPixel;              //Pixel Edit Window - View�� ����
	CDrawMeasure *m_pDrawMeasure;     //����
	int m_iScrollPosX, m_iScrollPosY; //���� ��ũ�� ��
    CListBox* m_List;
    CListBox* m_GList;

// �۾��Դϴ�.
public:
	CPreviewWnd m_wndPreview; //�̸����� View
	//CStatusWnd m_wndSatus; //��Ȳ ������
	CButton btnBinLarge;
	CButton btnBinSmall;
	CButton btnBinReverse;
	CButton btnBinMirrorTB;
	CButton btnBinMirrorLR;
	CButton btnBinRotate;
	CStatic stRotateVal;
	CEdit   edtRotateVal;
	CButton btnMode;
	CButton btnFileOpen;
	CButton btnFileSave;
	CButton btnGear;
	CStatic stGearModule;
	CEdit   edtGearModule;
	CStatic stPitchNo;
	CEdit   edtPitchNo;
	CButton btnBinary;
	CStatic stBinaryVal;
	CEdit   edtBinaryVal;
	CButton btnBinaryThread;
	CStatic stBinaryThread;
	CEdit   edtBinaryThreadLow;
	CEdit   edtBinaryThreadHigh;
	CButton btnImageOpen;
	CButton btnFontSelect;
	CStatic stFontName;
	CButton btnTextImage;
	CEdit   edtTextString;
	CButton btnExit;
	CButton btnRect;
	CButton btnLine;
	CButton btnRoundRect;
	CStatic stRectTop;
	CStatic stRectBottom;
	CEdit   edtRectTopX;
	CEdit   edtRectTopY;
	CEdit   edtRectBottomX;
	CEdit   edtRectBottomY;
	CButton btnCircle;
	CEdit   edtCircleX;
	CEdit   edtCircleY;
	CStatic stCircleR;
	CEdit   edtCircleR;

public:
	CButton btnPathFile;
	CButton btnGcodeFile;
	CStatic stGcodeStart;
	CEdit   edtGcodeStartX;
	CEdit   edtGcodeStartY;
	CButton btnGcodeHorizon;
	CButton btnGcodeVertical;
	CButton btnGcodeHorizonPart;
	CStatic stGcodeHorizonPart;
	CEdit   edtGcodeHorizonPart;
	CButton btnGcodeVerticalPart;
	CStatic stGcodeVerticalPart;
	CEdit   edtGcodeVerticalPart;
	CButton btnGcodeOutline;
	CButton btnGcodeDrawline;
	CStatic stGcodeDrawlineThick;
	CEdit   edtGcodeDrawlineThick;
	CStatic stGcodeScale;
	CEdit   edtGcodeScale;
	CStatic stGcodeDepth;
	CEdit   edtGcodeDepth;
	CStatic stGcodeDepthCount;
	CEdit   edtGcodeDepthCount;
	CStatic stGcodeToolNo;
	CEdit   edtGcodeToolNo;
	CStatic stGcodeIdleTime;
	CEdit   edtGcodeIdleTime;

public:
	CFont m_font;
	CFont m_fontText;
    LOGFONT m_log;
	CString lfFaceName;

public:
	int m_intModule;
	int m_intPitchNo;	
	int m_intBinaryUnity;	
	int m_intBinaryThreadLow;	
	int m_intBinaryThreadHigh;	
	int m_intRotateDegree;	
	CString m_strFontName;	
	CString m_strTextString;	
	int    m_RectTopX;
	int    m_RectTopY;
	int    m_RectBottomX;
	int    m_RectBottomY;
	int    m_CircleX;
	int    m_CircleY;
	int    m_CircleR;

public:
	int    m_GcodeStartX;
	int    m_GcodeStartY;
	int    m_GcodeHorizonPart;
	int    m_GcodeVerticalPart;
	int    m_GcodeDrawlineThick;
	double m_GcodeScale;
	double m_GcodeDepth;
	int    m_GcodeDepthCount;
	int    m_GcodeToolNo;
	int    m_GcodeIdleTime;

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:

// �����Դϴ�.
public:
	virtual ~CKsooPixelDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	void cmdFileOpen(void);
	void cmdFileSave(void);
	void cmdModeChange(void);
	void cmdZoomIn(void);
	void cmdZoomOut(void);
	void cmdDrawGear(void);
	void cmdImageBinary(void);
	void cmdImageBinaryThread(void);
	void cmdImageOpen(void);
	void cmdTextFontSelect(void);
	void cmdTextImageGen(void);
	void cmdBinaryReverse(CString p_work_code);
	virtual void DoDataExchange(CDataExchange* pDX);
};

#ifndef _DEBUG  // KsooPixelDrawView.cpp�� ����� ����
inline CKsooPixelDrawDoc* CKsooPixelDrawView::GetDocument() const
   { return reinterpret_cast<CKsooPixelDrawDoc*>(m_pDocument); }
#endif

