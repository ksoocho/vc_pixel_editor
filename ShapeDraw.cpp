#include "StdAfx.h"
#include "ShapeDraw.h"

CShapeDraw::CShapeDraw(CKsooPixelDrawView *tView)
{
	pView = tView;
	sing = (Singleton *)Singleton::getInstance();
}

CShapeDraw::~CShapeDraw(void)
{
}

// --------------------------------------------------------------------------
// Routine Name : RectangleDraw
// Description  : �簢�� �׸���
// History      : 2016-07-22 KSOOCHO  Create
// --------------------------------------------------------------------------
void CShapeDraw::RectangleDraw(int p_top_x, int p_top_y, int p_bottom_x, int p_bottom_y)
{
	// Validation

	if ( p_top_x <= 0 || p_top_y <= 0 || p_bottom_x <= 0 || p_bottom_y <= 0 ){	  
		AfxMessageBox(" Position Value�� ������� �մϴ�.");
		return;	
	}

	if ( p_top_x >= p_bottom_x  || p_top_y >= p_bottom_y ){	  
		AfxMessageBox(" Top Value�� Bottom Value���� �۾ƾ� �մϴ�.");
		return;	
	}

    sing->g_AmountWidth = p_bottom_x + 30;
	sing->g_AmountHeight = p_bottom_y + 30;

	sing->refresh();
	sing->copyOriColor();

	// Rectangle Draw 
    for(int y=0; y<sing->g_AmountHeight; y++)
	{
		for(int x=0; x<sing->g_AmountWidth; x++)
		{            
			sing->g_oriColor[y][x].r = 255;
			sing->g_oriColor[y][x].g = 255;
			sing->g_oriColor[y][x].b = 255;
		}
	}

	// Rectangle ����
	for ( int inx = p_top_x; inx <= p_bottom_x; inx++ ) {
		sing->g_oriColor[p_top_y][inx].r = 0;
		sing->g_oriColor[p_top_y][inx].g = 0;
		sing->g_oriColor[p_top_y][inx].b = 0;
	}

	// Rectangle ������
	for ( int iny = p_top_y; iny <= p_bottom_y; iny++ ) {
		sing->g_oriColor[iny][p_bottom_x].r = 0;
		sing->g_oriColor[iny][p_bottom_x].g = 0;
		sing->g_oriColor[iny][p_bottom_x].b = 0;
	}

	// Rectangle �Ʒ���
	for ( int inx = p_bottom_x; inx >= p_top_x; inx-- ) {
		sing->g_oriColor[p_bottom_y][inx].r = 0;
		sing->g_oriColor[p_bottom_y][inx].g = 0;
		sing->g_oriColor[p_bottom_y][inx].b = 0;
	}

	// Rectangle �޺�
	for ( int iny = p_bottom_y; iny >= p_top_y; iny-- ) {
		sing->g_oriColor[iny][p_top_x].r = 0;
		sing->g_oriColor[iny][p_top_x].g = 0;
		sing->g_oriColor[iny][p_top_x].b = 0;
	}

	int v_tool_size = 6;
	int v_tool_semi_size = (int)(v_tool_size*0.5);
	// --------------------------
	// Inner Line
	// --------------------------

	// Inner Rectangle ����
	for ( int inx = p_top_x+v_tool_semi_size; inx <= p_bottom_x-v_tool_semi_size; inx++ ) {
		sing->g_oriColor[p_top_y+v_tool_semi_size][inx].r = 255;
		sing->g_oriColor[p_top_y+v_tool_semi_size][inx].g = 0;
		sing->g_oriColor[p_top_y+v_tool_semi_size][inx].b = 0;
	}

	// Inner Rectangle ������
	for ( int iny = p_top_y+v_tool_semi_size; iny <= p_bottom_y-v_tool_semi_size; iny++ ) {
		sing->g_oriColor[iny][p_bottom_x-v_tool_semi_size].r = 255;
		sing->g_oriColor[iny][p_bottom_x-v_tool_semi_size].g = 0;
		sing->g_oriColor[iny][p_bottom_x-v_tool_semi_size].b = 0;
	}

	// Inner Rectangle �Ʒ���
	for ( int inx = p_bottom_x-v_tool_semi_size; inx >= p_top_x+v_tool_semi_size; inx-- ) {
		sing->g_oriColor[p_bottom_y-v_tool_semi_size][inx].r = 255;
		sing->g_oriColor[p_bottom_y-v_tool_semi_size][inx].g = 0;
		sing->g_oriColor[p_bottom_y-v_tool_semi_size][inx].b = 0;
	}

	// Inner Rectangle �޺�
	for ( int iny = p_bottom_y-v_tool_semi_size; iny >= p_top_y+v_tool_semi_size; iny-- ) {
		sing->g_oriColor[iny][p_top_x+v_tool_semi_size].r = 255;
		sing->g_oriColor[iny][p_top_x+v_tool_semi_size].g = 0;
		sing->g_oriColor[iny][p_top_x+v_tool_semi_size].b = 0;
	}

	// --------------------------
	// Outer Line
	// --------------------------

	// Outer Rectangle ����
	for ( int inx = p_top_x-v_tool_semi_size; inx <= p_bottom_x+v_tool_semi_size; inx++ ) {
		sing->g_oriColor[p_top_y-v_tool_semi_size][inx].r = 0;
		sing->g_oriColor[p_top_y-v_tool_semi_size][inx].g = 0;
		sing->g_oriColor[p_top_y-v_tool_semi_size][inx].b = 255;
	}

	// Outer Rectangle ������
	for ( int iny = p_top_y-v_tool_semi_size; iny <= p_bottom_y+v_tool_semi_size; iny++ ) {
		sing->g_oriColor[iny][p_bottom_x+v_tool_semi_size].r = 0;
		sing->g_oriColor[iny][p_bottom_x+v_tool_semi_size].g = 0;
		sing->g_oriColor[iny][p_bottom_x+v_tool_semi_size].b = 255;
	}

	// Outer Rectangle �Ʒ���
	for ( int inx = p_bottom_x+v_tool_semi_size; inx >= p_top_x-v_tool_semi_size; inx-- ) {
		sing->g_oriColor[p_bottom_y+v_tool_semi_size][inx].r = 0;
		sing->g_oriColor[p_bottom_y+v_tool_semi_size][inx].g = 0;
		sing->g_oriColor[p_bottom_y+v_tool_semi_size][inx].b = 255;
	}

	// Outer Rectangle �޺�
	for ( int iny = p_bottom_y+v_tool_semi_size; iny >= p_top_y-v_tool_semi_size; iny-- ) {
		sing->g_oriColor[iny][p_top_x-v_tool_semi_size].r = 0;
		sing->g_oriColor[iny][p_top_x-v_tool_semi_size].g = 0;
		sing->g_oriColor[iny][p_top_x-v_tool_semi_size].b = 255;
	}

	// ȭ�� Display
	sing->g_oldAmountWidth = sing->g_AmountWidth;
	sing->g_oldAmountHeight = sing->g_AmountHeight;

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

	sing->g_bStart = false;

}

// --------------------------------------------------------------------------
// Routine Name : CircleDraw
// Description  : �� �׸���
// History      : 2016-07-22 KSOOCHO  Create
// --------------------------------------------------------------------------
void CShapeDraw::CircleDraw(int p_center_x, int p_center_y, int p_radius)
{

	// Validation

	if ( p_center_x <= 0 || p_center_y <= 0 || p_radius <= 0 ){	  
		AfxMessageBox(" Position Value�� ������� �մϴ�.");
		return;	
	}

	if ( p_center_x - p_radius <= 0 || p_center_y - p_radius <= 0 ){	  
		AfxMessageBox(" ������ ����");
		return;	
	}

    sing->g_AmountWidth  = p_center_x + p_radius + 30;
	sing->g_AmountHeight = p_center_y + p_radius + 30;

	sing->refresh();
	sing->copyOriColor();

	// Background Color 
    for(int y=0; y<sing->g_AmountHeight; y++)
	{
		for(int x=0; x<sing->g_AmountWidth; x++)
		{            
			sing->g_oriColor[y][x].r = 255;
			sing->g_oriColor[y][x].g = 255;
			sing->g_oriColor[y][x].b = 255;
		}
	}

	// Circle Draw 
	int v_pos_x, v_pos_y;
	
	for(int angle=0;angle<=360;angle++)
    {

        v_pos_x = (int)(cos(angle* 3.141592/180)*p_radius)+p_center_x;
        v_pos_y= (int)(sin(angle* 3.141592/180)*p_radius)+p_center_y;


			sing->g_oriColor[v_pos_y][v_pos_x].r = 0;
			sing->g_oriColor[v_pos_y][v_pos_x].g = 0;
			sing->g_oriColor[v_pos_y][v_pos_x].b = 0;
    }


	int v_tool_size = 6;
	int v_tool_semi_size = (int)(v_tool_size*0.5);

	// Inner Circle Draw
	for(int angle=0;angle<=360;angle++)
    {

        v_pos_x = (int)(cos(angle* 3.141592/180)*(p_radius-v_tool_semi_size))+p_center_x;
        v_pos_y= (int)(sin(angle* 3.141592/180)*(p_radius-v_tool_semi_size))+p_center_y;

			sing->g_oriColor[v_pos_y][v_pos_x].r = 255;
			sing->g_oriColor[v_pos_y][v_pos_x].g = 0;
			sing->g_oriColor[v_pos_y][v_pos_x].b = 0;
    }

	// Outer Circle Draw
	for(int angle=0;angle<=360;angle++)
    {

        v_pos_x = (int)(cos(angle* 3.141592/180)*(p_radius+v_tool_semi_size))+p_center_x;
        v_pos_y= (int)(sin(angle* 3.141592/180)*(p_radius+v_tool_semi_size))+p_center_y;

			sing->g_oriColor[v_pos_y][v_pos_x].r = 0;
			sing->g_oriColor[v_pos_y][v_pos_x].g = 0;
			sing->g_oriColor[v_pos_y][v_pos_x].b = 255;
    }

	// ȭ��ó��
	sing->g_oldAmountWidth = sing->g_AmountWidth;
	sing->g_oldAmountHeight = sing->g_AmountHeight;

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

	sing->g_bStart = false;

}


void CShapeDraw::LineDraw(int p_top_x, int p_top_y, int p_bottom_x, int p_bottom_y)
{
	// Validation

	if ( p_top_x <= 0 || p_top_y <= 0 || p_bottom_x <= 0 || p_bottom_y <= 0 ){	  
		AfxMessageBox(" Position Value�� ������� �մϴ�.");
		return;	
	}

	// Work Space
    sing->g_AmountWidth  = (p_top_x > p_bottom_x ? p_top_x: p_bottom_x) + 30;
	sing->g_AmountHeight = (p_top_y > p_bottom_y ? p_top_y: p_bottom_y) + 30;

	sing->refresh();
	sing->copyOriColor();

	// Background 
    for(int y=0; y<sing->g_AmountHeight; y++)
	{
		for(int x=0; x<sing->g_AmountWidth; x++)
		{            
			sing->g_oriColor[y][x].r = 255;
			sing->g_oriColor[y][x].g = 255;
			sing->g_oriColor[y][x].b = 255;
		}
	}

	// Line Draw
	int v_temp_top_x, v_temp_top_y;
	int v_temp_bottom_x, v_temp_bottom_y;

	if ( p_top_x == p_bottom_x){

		if (p_top_y > p_bottom_y) {
		   v_temp_top_y = p_bottom_y;
		   v_temp_bottom_y = p_top_y;
		} else {
		   v_temp_top_y = p_top_y;
		   v_temp_bottom_y = p_bottom_y;
		}

	    for ( int iny = v_temp_top_y; iny <= v_temp_bottom_y; iny++ ) {
			sing->g_oriColor[iny][p_top_x].r = 0;
			sing->g_oriColor[iny][p_top_x].g = 0;
			sing->g_oriColor[iny][p_top_x].b = 0;
		}
	
	} else if ( p_top_y == p_bottom_y){

		if (p_top_x > p_bottom_x) {
		   v_temp_top_x = p_bottom_x;
		   v_temp_bottom_x = p_top_x;
		} else {
		   v_temp_top_x = p_top_x;
		   v_temp_bottom_x = p_bottom_x;
		}

	    for ( int inx = v_temp_top_x; inx <= v_temp_bottom_x; inx++ ) {
			sing->g_oriColor[p_top_y][inx].r = 0;
			sing->g_oriColor[p_top_y][inx].g = 0;
			sing->g_oriColor[p_top_y][inx].b = 0;
		}

	} else {


        if (p_top_x > p_bottom_x) {
		   v_temp_top_x = p_bottom_x;
		   v_temp_top_y = p_bottom_y;
		   v_temp_bottom_x = p_top_x;
		   v_temp_bottom_y = p_top_y;
		} else {
		   v_temp_top_x = p_top_x;
		   v_temp_top_y = p_top_y;
		   v_temp_bottom_x = p_bottom_x;
		   v_temp_bottom_y = p_bottom_y;
		}

		int iny;
		float v_slope =  ((float)v_temp_bottom_y - (float)v_temp_top_y)/((float)v_temp_bottom_x - (float)v_temp_top_x);

        for ( int inx = v_temp_top_x; inx <= v_temp_bottom_x; inx++ ) {

			iny = (int) (v_slope * ( inx - v_temp_top_x)) + v_temp_top_y;

			sing->g_oriColor[iny][inx].r = 0;
			sing->g_oriColor[iny][inx].g = 0;
			sing->g_oriColor[iny][inx].b = 0;
		}
	
	}
	
	
	// ȭ�� Display
	sing->g_oldAmountWidth = sing->g_AmountWidth;
	sing->g_oldAmountHeight = sing->g_AmountHeight;

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

	sing->g_bStart = false;
}


void CShapeDraw::RoundRectDraw(int p_top_x, int p_top_y, int p_bottom_x, int p_bottom_y)
{

	int v_pos_x, v_pos_y;
	int v_center_x, v_center_y;
	float v_radius = ((float)p_bottom_y - (float)p_top_y) /2 ;

	// Validation
	if ( p_top_x <= 0 || p_top_y <= 0 || p_bottom_x <= 0 || p_bottom_y <= 0 ){	  
		AfxMessageBox(" Position Value�� ������� �մϴ�.");
		return;	
	}

	if ( p_top_x >= p_bottom_x  || p_top_y >= p_bottom_y ){	  
		AfxMessageBox(" Top Value�� Bottom Value���� �۾ƾ� �մϴ�.");
		return;	
	}

	if ( p_top_x < (int)v_radius + 1  ){	  
		AfxMessageBox(" Top X Value�� ���������� Ŀ�� �մϴ�.");
		return;	
	}

    sing->g_AmountWidth = p_bottom_x + 30;
	sing->g_AmountHeight = p_bottom_y + 30;

	sing->refresh();
	sing->copyOriColor();

	// Background 
    for(int y=0; y<sing->g_AmountHeight; y++)
	{
		for(int x=0; x<sing->g_AmountWidth; x++)
		{            
			sing->g_oriColor[y][x].r = 255;
			sing->g_oriColor[y][x].g = 255;
			sing->g_oriColor[y][x].b = 255;
		}
	}

	// Center ����
	for ( int inx = p_top_x; inx <= p_bottom_x; inx++ ) {
		sing->g_oriColor[p_top_y][inx].r = 0;
		sing->g_oriColor[p_top_y][inx].g = 0;
		sing->g_oriColor[p_top_y][inx].b = 0;
	}


	// Center ������ 	
	v_center_x = p_bottom_x;
	v_center_y = p_top_y + (int) v_radius;

	for(int angle=271;angle<=360;angle++)
    {
        v_pos_x = (int)(cos(angle* 3.141592/180)*v_radius)+v_center_x;
        v_pos_y= (int)(sin(angle* 3.141592/180)*v_radius)+v_center_y;

		sing->g_oriColor[v_pos_y][v_pos_x].r = 0;
		sing->g_oriColor[v_pos_y][v_pos_x].g = 0;
		sing->g_oriColor[v_pos_y][v_pos_x].b = 0;
    }

	for(int angle=0;angle<=90;angle++)
    {
        v_pos_x = (int)(cos(angle* 3.141592/180)*v_radius)+v_center_x;
        v_pos_y= (int)(sin(angle* 3.141592/180)*v_radius)+v_center_y;

		sing->g_oriColor[v_pos_y][v_pos_x].r = 0;
		sing->g_oriColor[v_pos_y][v_pos_x].g = 0;
		sing->g_oriColor[v_pos_y][v_pos_x].b = 0;
    }


	// Center �Ʒ���
	for ( int inx = p_bottom_x; inx >= p_top_x; inx-- ) {
		sing->g_oriColor[p_bottom_y][inx].r = 0;
		sing->g_oriColor[p_bottom_y][inx].g = 0;
		sing->g_oriColor[p_bottom_y][inx].b = 0;
	}

	// Center �޺�
	v_center_x = p_top_x;
	v_center_y = p_top_y + (int) v_radius;

	for(int angle=91;angle<=270;angle++)
    {

        v_pos_x = (int)(cos(angle* 3.141592/180)*v_radius)+v_center_x;
        v_pos_y= (int)(sin(angle* 3.141592/180)*v_radius)+v_center_y;

		sing->g_oriColor[v_pos_y][v_pos_x].r = 0;
		sing->g_oriColor[v_pos_y][v_pos_x].g = 0;
		sing->g_oriColor[v_pos_y][v_pos_x].b = 0;
    }

	int v_tool_size = 6;
	int v_tool_semi_size = (int)(v_tool_size*0.5);

	// ---------------------
	// Inner Line
	// ---------------------

    // Inner ����
	for ( int inx = p_top_x; inx <= p_bottom_x; inx++ ) {
		sing->g_oriColor[p_top_y+v_tool_semi_size][inx].r = 255;
		sing->g_oriColor[p_top_y+v_tool_semi_size][inx].g = 0;
		sing->g_oriColor[p_top_y+v_tool_semi_size][inx].b = 0;
	}

    // Inner ������ 	
	v_center_x = p_bottom_x;
	v_center_y = p_top_y + (int) v_radius;

	for(int angle=271;angle<=360;angle++)
    {
        v_pos_x = (int)(cos(angle* 3.141592/180)*(v_radius-v_tool_semi_size))+v_center_x;
        v_pos_y= (int)(sin(angle* 3.141592/180)*(v_radius-v_tool_semi_size))+v_center_y;

		sing->g_oriColor[v_pos_y][v_pos_x].r = 255;
		sing->g_oriColor[v_pos_y][v_pos_x].g = 0;
		sing->g_oriColor[v_pos_y][v_pos_x].b = 0;
    }

	for(int angle=0;angle<=90;angle++)
    {
        v_pos_x = (int)(cos(angle* 3.141592/180)*(v_radius-v_tool_semi_size))+v_center_x;
        v_pos_y= (int)(sin(angle* 3.141592/180)*(v_radius-v_tool_semi_size))+v_center_y;

		sing->g_oriColor[v_pos_y][v_pos_x].r = 255;
		sing->g_oriColor[v_pos_y][v_pos_x].g = 0;
		sing->g_oriColor[v_pos_y][v_pos_x].b = 0;
    }

    // inner �Ʒ���
	for ( int inx = p_bottom_x; inx >= p_top_x; inx-- ) {
		sing->g_oriColor[p_bottom_y-v_tool_semi_size][inx].r = 255;
		sing->g_oriColor[p_bottom_y-v_tool_semi_size][inx].g = 0;
		sing->g_oriColor[p_bottom_y-v_tool_semi_size][inx].b = 0;
	}

    // inner �޺�
	v_center_x = p_top_x;
	v_center_y = p_top_y + (int) v_radius;

	for(int angle=91;angle<=270;angle++)
    {

        v_pos_x = (int)(cos(angle* 3.141592/180)*(v_radius-v_tool_semi_size))+v_center_x;
        v_pos_y= (int)(sin(angle* 3.141592/180)*(v_radius-v_tool_semi_size))+v_center_y;

		sing->g_oriColor[v_pos_y][v_pos_x].r = 255;
		sing->g_oriColor[v_pos_y][v_pos_x].g = 0;
		sing->g_oriColor[v_pos_y][v_pos_x].b = 0;
    }

	// ---------------------
	// Outer Line
	// ---------------------
	 // Outer ����
	for ( int inx = p_top_x; inx <= p_bottom_x; inx++ ) {
		sing->g_oriColor[p_top_y-v_tool_semi_size][inx].r = 0;
		sing->g_oriColor[p_top_y-v_tool_semi_size][inx].g = 0;
		sing->g_oriColor[p_top_y-v_tool_semi_size][inx].b = 255;
	}

    // Outer ������ 	
	v_center_x = p_bottom_x;
	v_center_y = p_top_y + (int) v_radius;

	for(int angle=271;angle<=360;angle++)
    {
        v_pos_x = (int)(cos(angle* 3.141592/180)*(v_radius+v_tool_semi_size))+v_center_x;
        v_pos_y= (int)(sin(angle* 3.141592/180)*(v_radius+v_tool_semi_size))+v_center_y;

		sing->g_oriColor[v_pos_y][v_pos_x].r = 0;
		sing->g_oriColor[v_pos_y][v_pos_x].g = 0;
		sing->g_oriColor[v_pos_y][v_pos_x].b = 255;
    }

	for(int angle=0;angle<=90;angle++)
    {
        v_pos_x = (int)(cos(angle* 3.141592/180)*(v_radius+v_tool_semi_size))+v_center_x;
        v_pos_y= (int)(sin(angle* 3.141592/180)*(v_radius+v_tool_semi_size))+v_center_y;

		sing->g_oriColor[v_pos_y][v_pos_x].r = 0;
		sing->g_oriColor[v_pos_y][v_pos_x].g = 0;
		sing->g_oriColor[v_pos_y][v_pos_x].b = 255;
    }

	// Outer �Ʒ���
	for ( int inx = p_bottom_x; inx >= p_top_x; inx-- ) {
		sing->g_oriColor[p_bottom_y+v_tool_semi_size][inx].r = 0;
		sing->g_oriColor[p_bottom_y+v_tool_semi_size][inx].g = 0;
		sing->g_oriColor[p_bottom_y+v_tool_semi_size][inx].b = 255;
	}

    // Outer �޺�
	v_center_x = p_top_x;
	v_center_y = p_top_y + (int) v_radius;

	for(int angle=91;angle<=270;angle++)
    {

        v_pos_x = (int)(cos(angle* 3.141592/180)*(v_radius+v_tool_semi_size))+v_center_x;
        v_pos_y= (int)(sin(angle* 3.141592/180)*(v_radius+v_tool_semi_size))+v_center_y;

		sing->g_oriColor[v_pos_y][v_pos_x].r = 0;
		sing->g_oriColor[v_pos_y][v_pos_x].g = 0;
		sing->g_oriColor[v_pos_y][v_pos_x].b = 255;
    }

	// ȭ�� Display
	sing->g_oldAmountWidth = sing->g_AmountWidth;
	sing->g_oldAmountHeight = sing->g_AmountHeight;

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

	sing->g_bStart = false;
}
