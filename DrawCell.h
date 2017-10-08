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
	void DrawCell(Graphics *g); //Cell �׸���

public:
	int m_iFirstX; //���� ȭ�鿡�� �׷��ֱ� ���� �������
	int m_iLastX;
	int m_iFirstY;
	int m_iLastY;
	bool m_bCell; //���� ���� �� �÷���
	bool m_bCharacter;
	
private:
	int m_iCellSize; //Cell�� Width
	int m_iAmountX; //X ũ��
	int m_iAmountY; //Y ũ��

};
