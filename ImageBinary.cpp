#include "StdAfx.h"
#include "ImageBinary.h"


CImageBinary::CImageBinary(void)
{

}

CImageBinary::CImageBinary(CKsooPixelDrawView *pView, int p_binary_unity)
{
	Singleton *sing = (Singleton *)Singleton::getInstance();

	byte v_color_r, v_color_g, v_color_b, GRAY;

	for(int y=0; y<sing->g_AmountHeight; y++)
	{
		for(int x=0; x<sing->g_AmountWidth; x++)
		{
			
			GRAY = (BYTE)(0.299*sing->g_tempColor[y][x].r + 0.587*sing->g_tempColor[y][x].g + 0.114*sing->g_tempColor[y][x].b );
				
			if(GRAY > p_binary_unity ) 
			{
				v_color_r = 255;
				v_color_g = 255;
				v_color_b = 255;
			} else { 
				v_color_r = 0;
				v_color_g = 0;
				v_color_b = 0;
			}

			sing->g_oriColor[y][x].r = v_color_r;
			sing->g_oriColor[y][x].g = v_color_g;
			sing->g_oriColor[y][x].b = v_color_b;

		}
	}

    pView->m_wndPixel.m_wndView->m_DrawGrid.CreateGridPage
		                                    (pView->m_wndPixel.m_wndView, 
		                                     sing->g_AmountWidth, 
											 sing->g_AmountHeight, 
											 sing->g_cellSize
											);

	if(sing->g_oriColor != NULL){
		pView->m_wndPixel.m_wndView->m_DrawCell.SetDrawItem
			                                     (sing->g_AmountWidth, 
												  sing->g_AmountHeight, 
												  sing->g_cellSize
												 );
	}

	pView->m_pDrawMeasure->m_iUnitSize = sing->g_cellSize;
	pView->m_wndPixel.m_wndView->Invalidate();
	pView->Invalidate();
}

CImageBinary::CImageBinary(CKsooPixelDrawView *pView, int p_binary_thread_low, int p_binary_thread_high)
{
	Singleton *sing = (Singleton *)Singleton::getInstance();

	byte v_color_r, v_color_g, v_color_b, GRAY;

	for(int y=0; y<sing->g_AmountHeight; y++)
	{
		for(int x=0; x<sing->g_AmountWidth; x++)
		{
			
			GRAY = (BYTE)(0.299*sing->g_tempColor[y][x].r + 0.587*sing->g_tempColor[y][x].g + 0.114*sing->g_tempColor[y][x].b );
				
			if(GRAY > p_binary_thread_low && GRAY < p_binary_thread_high ) 
			{
				v_color_r = 255;
				v_color_g = 255;
				v_color_b = 255;
			} else { 
				v_color_r = 0;
				v_color_g = 0;
				v_color_b = 0;
			}

			sing->g_oriColor[y][x].r = v_color_r;
			sing->g_oriColor[y][x].g = v_color_g;
			sing->g_oriColor[y][x].b = v_color_b;

		}
	}

    pView->m_wndPixel.m_wndView->m_DrawGrid.CreateGridPage
		                                    (pView->m_wndPixel.m_wndView, 
		                                     sing->g_AmountWidth, 
											 sing->g_AmountHeight, 
											 sing->g_cellSize
											);

	if(sing->g_oriColor != NULL){
		pView->m_wndPixel.m_wndView->m_DrawCell.SetDrawItem
			                                     (sing->g_AmountWidth, 
												  sing->g_AmountHeight, 
												  sing->g_cellSize
												 );
	}

	pView->m_pDrawMeasure->m_iUnitSize = sing->g_cellSize;
	pView->m_wndPixel.m_wndView->Invalidate();
	pView->Invalidate();
}

CImageBinary::CImageBinary(CKsooPixelDrawView *pView, CString p_work_code, int p_degree)
{

	Singleton *sing = (Singleton *)Singleton::getInstance();

	// 작업 Data 초기화
	int l_map_width     = sing->g_AmountWidth;  
    int l_map_height    = sing->g_AmountHeight;  
	
	//-------------------------------------
	// 초기화
	//-------------------------------------
	//원본 Data 초기화
	int** m_nMap = new int*[l_map_height];

    for(int arri = 0; arri < l_map_height; arri++)
      m_nMap[arri] = new int[l_map_width];

	//작업Data 초기화
	int** m_nTempMap = new int*[l_map_height];

    for(int arri = 0; arri < l_map_height; arri++)
      m_nTempMap[arri] = new int[l_map_width];

	//-------------------------------------
	// 작업영역담기
	//-------------------------------------
	for(int y=0; y<l_map_height; y++)
	{
		for(int x=0; x<l_map_width; x++)
		{
			if ( sing->g_oriColor[y][x].r == 0 &&
				 sing->g_oriColor[y][x].g == 0 &&
				 sing->g_oriColor[y][x].b == 0 )
			{
				m_nMap[y][x] = 1;
			} else {
				m_nMap[y][x] = 0;
			}
		}
	}

	//-------------------------------------
	//이미지 반전
	//-------------------------------------
	if (p_work_code == "RV") 
	{

		for(int y=0; y<l_map_height; y++)
		{
			for(int x=0; x<l_map_width; x++)
			{
				m_nTempMap[y][x] = (m_nMap[y][x] == 1 ? 0 : 1 );
			}
		}

	}

	//-------------------------------------
	//이미지 상하 미러링
	//-------------------------------------
	if (p_work_code == "MTB") 
	{

		for(int y=0; y<l_map_height; y++)
		{
			for(int x=0; x<l_map_width; x++)
			{
				m_nTempMap[y][x]=m_nMap[(l_map_height - 1) - y][x];
			}
		}
	}

	//-------------------------------------
	//이미지 좌우 미러링
	//-------------------------------------
	if (p_work_code == "MLR") 
	{

		for(int y=0; y<l_map_height; y++)
		{
			for(int x=0; x<l_map_width; x++)
			{
				m_nTempMap[y][x]=m_nMap[y][(l_map_width - 1) -x];
			}
		}
	}

	//-------------------------------------
	//이미지 회전
	//-------------------------------------
	if (p_work_code == "ROT") 
	{
		if ( l_map_height != l_map_width )
		{
			AfxMessageBox("가로 세로 같은 값이어야 합니다.");
			return;
		} 

		// Rotate Logic
		double radius, sin_value, cos_value;
		int centerX, centerY;
		double new_x, new_y;
		BYTE ret_var;
		double M_PI = 3.141592654;

		int degree = p_degree;

		//degree를 radius로 변환 
		radius = 270 - degree*(M_PI/180.0);
		sin_value = sin(radius);
		cos_value = cos(radius);

		//중심화소
		centerX = (int)l_map_height/2;
		centerY = (int)l_map_width/2;

		for(int y=0; y<l_map_height; y++)
		{
			for(int x=0; x<l_map_width; x++)
			{
				new_x = (y-centerX)*cos_value - (x-centerY)*sin_value + centerX;
				new_y = (y-centerX)*sin_value + (x-centerY)*cos_value + centerY;
			
				if (new_x<0 || new_x >= l_map_height)
				{
					ret_var = 0;
				}
				else if (new_y < 0 || new_y >= l_map_width)
				{
					ret_var = 0 ;
				}
				else
				{
					ret_var = m_nMap[(int)new_x][(int)new_y];
				}

				m_nTempMap[y][x]=ret_var;
			}
		}
	}

	// 작업결과 이미지 반영
    for(int y=0; y<l_map_height; y++)
	{
		for(int x=0; x<l_map_width; x++)
		{
			if ( m_nTempMap[y][x] == 0 )  
			{	
				sing->g_oriColor[y][x].r = 255; 
				sing->g_oriColor[y][x].g = 255; 
				sing->g_oriColor[y][x].b = 255;
			} else {
				sing->g_oriColor[y][x].r = 0; 
				sing->g_oriColor[y][x].g = 0; 
				sing->g_oriColor[y][x].b = 0;
			}
		}
	}

	//DELETE Array
	for(int deli = 0; deli < l_map_height; deli++)
		delete m_nMap[deli];

    delete m_nMap; 

	for(int deli = 0; deli < l_map_height; deli++)
		delete m_nTempMap[deli];

    delete m_nTempMap; 

	pView->m_wndPixel.m_wndView->m_DrawGrid.CreateGridPage
		                                    (pView->m_wndPixel.m_wndView, 
		                                     sing->g_AmountWidth, 
											 sing->g_AmountHeight, 
											 sing->g_cellSize
											);

	if(sing->g_oriColor != NULL){
		pView->m_wndPixel.m_wndView->m_DrawCell.SetDrawItem
			                                     (sing->g_AmountWidth, 
												  sing->g_AmountHeight, 
												  sing->g_cellSize
												 );
	}

	pView->m_pDrawMeasure->m_iUnitSize = sing->g_cellSize;
	pView->m_wndPixel.m_wndView->Invalidate();
	pView->Invalidate();


}


CImageBinary::~CImageBinary(void)
{
}
