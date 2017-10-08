#pragma once

#include <gdiplus.h>
#pragma comment(lib,"gdiplus")
using namespace Gdiplus;
#include "Singleton.h"

class CDrawCell
{
public:
	CDrawCell(void);
	~CDrawCell(void);
	bool Draw(CDC* pDC);
	void SetDrawItem(int AmtX, int AmtY, int cs); //CX CY CS Set
	void DrawCell(Graphics *g); //Cell 그리기

public:
	int m_iFirstX; //현재 화면에만 그려주기 위한 멤버변수
	int m_iLastX;
	int m_iFirstY;
	int m_iLastY;
	bool m_bCell; //색실 글자 뷰 플러그
	bool m_bCharacter;
	
private:
	int m_iCellSize; //Cell의 Width
	int m_iAmountX; //X 크기
	int m_iAmountY; //Y 크기

};
