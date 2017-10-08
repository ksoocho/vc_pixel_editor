/***************************************************************************
	클래스 명 : Singleton
	내용      : 색실의 정보를 가지고 있는 유일한 class 
	만든 이	  : 김병철(ddeng722@nate.com)
	수정 일자 : 2005년 8월 17일
***************************************************************************/

#pragma once

#include <iostream>

using namespace std;
#define MARK_AMOUNT	85 //마크 갯수
#define TOTAL_KINDOFLINE	100

/***************************************************************************
	구조체 명 : SKindOfLine
	내용      : 현재 사용되는 색실의 정보를 저장하는 Struct 
***************************************************************************/

struct SKindOfLine
{
	char str; //스트링
	bool flag; //사용 여부
	short line; //색실 번호
	CString name; //색실 명
	byte r, g, b; //색실 rgb 24bit기준
};

struct SColor
{
	byte r, g, b;
};

class Singleton
{

private:
    static bool instanceFlag;
    static Singleton *single;

public:
	bool g_bEdge;             //에지 추출 여부
	short g_userid;           //UserID
	bool g_bDragFlag;
	SColor **g_oriColor;      //오리지날 칼라
	SColor **g_tempColor;     //Temp 칼라
	int g_AmountWidth;        //가로 길이
	int g_AmountHeight;       //세로 길이
	int g_oldAmountWidth;     //old 가로길이
	int g_oldAmountHeight;    //old 세로길이
	int g_cellSize;           //셀 Size
	bool g_bDrawMode;         //그리기 모드
	bool g_bStart;            //처음
	int **g_aIndex;           //선택된 index


	 //Image Processing
	int g_binary_unity;  
	int g_binary_dual_low;  
	int g_binary_dual_high; 

	COLORREF g_select_color;
	LOGFONT	 g_font;
	COLORREF g_font_color;

    static Singleton* getInstance(); //Get Singleton 

    Singleton();

	~Singleton()
    {
		instanceFlag = false;
		if(g_oriColor != NULL){
			for(int j=0;j<g_AmountHeight;j++)
			{
				delete [] g_oriColor[j];
			}
			delete g_oriColor;
		}
    }

    void method();

	void refresh(void);

	void copyOriColor(void);
};