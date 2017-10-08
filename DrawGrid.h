/***************************************************************************
	Ŭ���� �� : CDrawGrid
	����      : Grid �׷���
	���� ��	  : �躴ö(ddeng722@nate.com)
	���� ���� : 2005�� 8�� 15��
***************************************************************************/
#pragma once

#include "BasicSet.h"

#include <gdiplus.h>
using namespace Gdiplus;

class CWorkView;
class CDrawGrid
{
//������ �� �Ҹ���
public:
	CDrawGrid(void);
	~CDrawGrid(void);

//��� ����
protected:
	int m_cx; //��ü Cx
	int m_cy; //��ü Cy
	int m_iCellSize; //Cell�� Width
	
	int m_iAmountX; //X ũ��
	int m_iAmountY; //Y ũ��
	
	Color	m_colorBG;		//����
	Pen     m_penDrawLine; //Grid Line �׸��� Pen
	Pen		m_penDrawPointLine; //Grid ����Ʈ Line �׸��� Pen
	Graphics* m_lpGridGrp; //Grid �׸� Graphic

	COLORREF m_line_Color;

public:
	int GetCellSize(){return m_iCellSize;} //Cell Size
	int GetAmountX(){return m_iAmountX;}   
	int GetAmountY(){return m_iAmountY;}
	Color GetColorBG(){return m_colorBG;}
	void SetCellSize(int x);
	void setAmountXY(int x, int y);
	bool Draw(CDC* pDC);
	void CreateGridPage(CWorkView *pView, int xAmt, int yAmt, int cs); //GridPage ����
	bool SetGridDrawLine(Graphics* g); //Drawing �κ�
};
