/***************************************************************************
	클래스 명 : CDrawGrid
	내용      : Grid 그려줌
	만든 이	  : 김병철(ddeng722@nate.com)
	수정 일자 : 2005년 8월 15일
***************************************************************************/
#pragma once

#include "BasicSet.h"

#include <gdiplus.h>
using namespace Gdiplus;

class CWorkView;
class CDrawGrid
{
//생성자 및 소멸자
public:
	CDrawGrid(void);
	~CDrawGrid(void);

//멤버 변수
protected:
	int m_cx; //전체 Cx
	int m_cy; //전체 Cy
	int m_iCellSize; //Cell의 Width
	
	int m_iAmountX; //X 크기
	int m_iAmountY; //Y 크기
	
	Color	m_colorBG;		//배경색
	Pen     m_penDrawLine; //Grid Line 그리는 Pen
	Pen		m_penDrawPointLine; //Grid 포인트 Line 그리는 Pen
	Graphics* m_lpGridGrp; //Grid 그릴 Graphic

	COLORREF m_line_Color;

public:
	int GetCellSize(){return m_iCellSize;} //Cell Size
	int GetAmountX(){return m_iAmountX;}   
	int GetAmountY(){return m_iAmountY;}
	Color GetColorBG(){return m_colorBG;}
	void SetCellSize(int x);
	void setAmountXY(int x, int y);
	bool Draw(CDC* pDC);
	void CreateGridPage(CWorkView *pView, int xAmt, int yAmt, int cs); //GridPage 생성
	bool SetGridDrawLine(Graphics* g); //Drawing 부분
};
