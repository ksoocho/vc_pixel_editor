/***************************************************************************
	Ŭ���� �� : Singleton
	����      : ������ ������ ������ �ִ� ������ class 
	���� ��	  : �躴ö(ddeng722@nate.com)
	���� ���� : 2005�� 8�� 17��
***************************************************************************/

#pragma once

#include <iostream>

using namespace std;
#define MARK_AMOUNT	85 //��ũ ����
#define TOTAL_KINDOFLINE	100

/***************************************************************************
	����ü �� : SKindOfLine
	����      : ���� ���Ǵ� ������ ������ �����ϴ� Struct 
***************************************************************************/

struct SKindOfLine
{
	char str; //��Ʈ��
	bool flag; //��� ����
	short line; //���� ��ȣ
	CString name; //���� ��
	byte r, g, b; //���� rgb 24bit����
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
	bool g_bEdge;             //���� ���� ����
	short g_userid;           //UserID
	bool g_bDragFlag;
	SColor **g_oriColor;      //�������� Į��
	SColor **g_tempColor;     //Temp Į��
	int g_AmountWidth;        //���� ����
	int g_AmountHeight;       //���� ����
	int g_oldAmountWidth;     //old ���α���
	int g_oldAmountHeight;    //old ���α���
	int g_cellSize;           //�� Size
	bool g_bDrawMode;         //�׸��� ���
	bool g_bStart;            //ó��
	int **g_aIndex;           //���õ� index


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