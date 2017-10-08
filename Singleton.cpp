#include "StdAfx.h"
#include "Singleton.h"

bool Singleton::instanceFlag = false;
Singleton* Singleton::single = NULL;

Singleton* Singleton::getInstance()
{
    if(! instanceFlag)
    {
        single = new Singleton();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}
Singleton::Singleton()
{
	//그리기 모드
	g_bDrawMode = false;
	g_bEdge = false;
	g_bStart = true;

	//수동 초기화
	g_bDragFlag = false;

	g_oriColor = NULL;
	g_tempColor = NULL;

	g_AmountWidth = 100;
	g_AmountHeight = 100;

	g_oldAmountWidth = 100;
	g_oldAmountHeight = 100;
	g_cellSize = 10; 

	//Image Processing 초기값
	g_binary_unity = 128;
	g_binary_dual_low = 50;
	g_binary_dual_high = 150;
	g_select_color = RGB(64, 128, 255);

	refresh();

	copyOriColor();
}

void Singleton::method()
{
    AfxMessageBox("싱글레톤");
}



void Singleton::refresh(void)
{
	if(g_oriColor != NULL){
		for(int j=0;j<g_oldAmountHeight;j++)
		{
			delete [] g_oriColor[j];
		}

		delete  g_oriColor;
		g_oriColor = NULL;
	}

	if(g_oriColor == NULL){
		g_oriColor = new SColor*[g_AmountHeight];
		for(int i=0; i<g_AmountHeight; i++)
		{
			g_oriColor[i] = new SColor[g_AmountWidth];
		}
	}
}

void Singleton::copyOriColor(void)
{
	if(g_tempColor != NULL){
		for(int j=0;j<g_oldAmountHeight;j++)
		{
			delete [] g_tempColor[j];
		}

		delete  g_tempColor;
		g_tempColor = NULL;
	}

	if(g_tempColor == NULL){
		g_tempColor = new SColor*[g_AmountHeight];
		for(int i=0; i<g_AmountHeight; i++)
		{
			g_tempColor[i] = new SColor[g_AmountWidth];
		}
	}

	// Copy original Color
	if(g_oriColor != NULL){

		for(int y=0; y<g_AmountHeight; y++)
		{
			for(int x=0; x<g_AmountWidth; x++)
			{
				g_tempColor[y][x].r = g_oriColor[y][x].r;
				g_tempColor[y][x].g = g_oriColor[y][x].g;
				g_tempColor[y][x].b = g_oriColor[y][x].b;
			}
		}
	}
}
