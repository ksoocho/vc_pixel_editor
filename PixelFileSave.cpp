#include "StdAfx.h"
#include "PixelFileSave.h"
#include "Singleton.h"


CPixelFileSave::CPixelFileSave(void)
{
}

CPixelFileSave::CPixelFileSave(CString str)
{
	Singleton *sing = (Singleton *)Singleton::getInstance();

	CString tmp;
	char flag = '&';
	FILE *ifp;

	str+=".STI";

	//ifp = fopen((LPCSTR)str, "wb");  //cks

    fopen_s(&ifp, (LPCSTR)str, "wb");


	fwrite(&flag, sizeof(char), 1, ifp);

	//Width 2Bytes
	fwrite(&sing->g_AmountWidth, sizeof(short), 1, ifp);

	//Height 2Bytes
	fwrite(&sing->g_AmountHeight, sizeof(short), 1, ifp);

	byte v_color_r, v_color_g, v_color_b;

	for(int y=0; y<sing->g_AmountHeight; y++)
	{
		for(int x=0; x<sing->g_AmountWidth; x++)
		{
            v_color_r = sing->g_oriColor[y][x].r;
            v_color_g = sing->g_oriColor[y][x].g;
            v_color_b = sing->g_oriColor[y][x].b;

			fwrite(&v_color_r, sizeof(v_color_r), 1, ifp);
			fwrite(&v_color_g, sizeof(v_color_g), 1, ifp);
			fwrite(&v_color_b, sizeof(v_color_b), 1, ifp);

		}
	}

	fclose(ifp);
}


CPixelFileSave::~CPixelFileSave(void)
{
}

char* CPixelFileSave::Trans(short v)
{
	
	
	tmp[0]= (byte)(( v >> 8 ) & 0xFF); 
	tmp[1]= (byte)( v & 0xFF ); 

	return tmp;

}

