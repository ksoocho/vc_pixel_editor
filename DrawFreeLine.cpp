#include "StdAfx.h"
#include "DrawFreeLine.h"
#include "Singleton.h"
#include <gdiplus.h>
using namespace Gdiplus;

CDrawFreeLine::CDrawFreeLine(void)
{
}

CDrawFreeLine::~CDrawFreeLine(void)
{
}

//�޼��� �ڵ鸵

void CDrawFreeLine::MouseMove(DWORD nFlag, CPoint point)
{
	/*
	Singleton *sing = (Singleton *)Singleton::getInstance();
	int tmpX, tmpY;
	tmpX = (int)(point.x/sing->g_cellSize);
	tmpY = (int)(point.y/sing->g_cellSize);
	*/
//	Graphics g(dc);
//	Pen pen(Color(0, 0, 0), 2);
//	g.DrawLine(pen, 0, 0, 100, 100);
	switch(nFlag)
	{
		case MK_LBUTTON:
		
		break;
	}

	//TRACE("X��ǥ : %d, Y��ǥ : %d\n", tmpX, tmpY);
}