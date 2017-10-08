#pragma once

#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib, "gdiplus.lib")

class CDrawMeasure
{
public:
	CDrawMeasure(void);
	~CDrawMeasure(void);

public:
	bool Draw(CDC* pDC, int scrX, int scrY);
	void MeasureDraw(Graphics* g, int scrX, int scrY); //Drawing �κ�

private:
	Gdiplus::Font *m_Font;
	SolidBrush *m_Brush;
	Pen m_penDrawLine;      //Grid Line �׸��� Pen
	Pen m_penDrawPointLine; //Grid Line Point�ִ� Pen
	
	int m_iLineAmountX; //X Amount
	int m_iLineAmountY; //Y Amount

	int m_iStartPointX;
	int m_iStartPointY;

public:
	int m_iUnitSize; //�� �� ����
};

