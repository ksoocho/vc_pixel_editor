#include "StdAfx.h"
#include "GearDraw.h"
#include "math.h"
#include "Singleton.h"

#define PI	3.14159

double rotationX ( double p_rot_ang, double p_x, double p_y);
double rotationY ( double p_rot_ang, double p_x, double p_y);

CGearDraw::CGearDraw(void)
{
}

CGearDraw::CGearDraw(CKsooPixelDrawView *pView,double p_module, double p_pitch_number)
{
	double v_module = p_module;
	double v_pitch_number = p_pitch_number;

	Singleton *sing = (Singleton *)Singleton::getInstance();

	drawGear(v_module,v_pitch_number);

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
	
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	CString strStatus1, strStatus2;
	strStatus1.Format(" X 크기 : %d", sing->g_AmountWidth);
	strStatus2.Format(" Y 크기 : %d", sing->g_AmountHeight);
	pMainFrame->m_wndStatusBar.SetPaneText(1, strStatus1);
	pMainFrame->m_wndStatusBar.SetPaneText(2, strStatus2);
	pMainFrame->m_wndStatusBar.SetPaneText(3, " 이동 모드");
}

CGearDraw::~CGearDraw(void)
{
	
}


void CGearDraw::drawGear(double p_module, double p_pitch_number)
{
	double v_diameter_prime = p_module * p_pitch_number;
	double v_diameter_ext = v_diameter_prime + 2 * p_module;
	double v_diameter_base = v_diameter_prime * cos(p_pitch_number * PI / 180 );
	double v_diameter_root = v_diameter_prime - 2.5 * p_module;

	double v_circular_pitch = p_module * PI;

	double v_radius_prime = v_diameter_prime / 2 ;
	double v_radius_root = v_diameter_root / 2 ;
	double v_radius_base = v_diameter_base / 2 ;
	double v_radius_ext  = v_diameter_ext / 2;

	int **aPos;
	int nRow, nCol;

	nRow = (int)v_diameter_ext + 1;
	nCol = (int)v_diameter_ext + 1;

	aPos = (int **)malloc(nRow * sizeof(int *));

	for (int i = 0; i < nRow; ++i )
	{
		aPos[i] = (int *)malloc(nCol * sizeof(int));
		for ( int j = 0; j < nCol; ++j ) aPos[i][j] = 0; 
	}

	double v_gamma = PI * p_module / (2 * v_radius_prime);
	double v_are = (sqrt((pow(v_radius_ext,2) - pow(v_radius_base,2)) / pow(v_radius_base,2)) 
		           - atan(sqrt((pow(v_radius_ext,2) - pow(v_radius_base,2)) / pow(v_radius_base,2)))
				   );
	double v_tre = sqrt((pow(v_radius_ext,2) - pow(v_radius_base,2)) / pow(v_radius_base,2));
	double v_arp = (sqrt((pow(v_radius_prime,2) - pow(v_radius_base,2)) / pow(v_radius_base,2)) 
		            - atan(sqrt((pow(v_radius_prime,2) - pow(v_radius_base,2)) / pow(v_radius_base,2)))
					);
	double v_epsilon = v_are - v_arp;
	double v_se = (v_gamma - 2 * v_epsilon);
	double v_sigma = v_se + 2 * v_are;
	double v_tau = 360 / p_pitch_number;

	//-----------------------------------------
	//  Main Routine
	//-----------------------------------------

	bool v_continue = true;
	bool v_follow;
	double x, y, x1, y1, r, v_step, v_teta, v_val01, v_val02;
	double v_taurot = 0;

	do{
		v_teta = 0;

		//--------------------------
		// Section A
		//--------------------------
		v_step = 0.1;
		x = v_radius_root;
		y = 0;
		v_follow = true;

		do
		{
			v_val01 = rotationX(v_taurot, x, y );
			v_val02 = rotationY(v_taurot, x, y );

			aPos[(int)v_val01 + (int) v_radius_ext][(int)v_val02 + (int)v_radius_ext] = 1;

			x = x + v_step;

			if( x > v_radius_base ) v_follow = false;

		} while ( v_follow ) ;

		//--------------------------
		// Section B
		//--------------------------
		v_step = 0.1;
		v_follow = true;

        do
		{
			x = (v_radius_base * cos ( v_teta * PI / 180 ))
				 + (v_radius_base * v_teta * PI / 180 * sin(v_teta * PI /180));
			y = (v_radius_base * sin ( v_teta * PI / 180 ))
				 - (v_radius_base * v_teta * PI / 180 * cos(v_teta * PI /180));

			v_val01 = rotationX(v_taurot, x, y );
			v_val02 = rotationY(v_taurot, x, y );

			aPos[(int)v_val01 + (int) v_radius_ext][(int)v_val02 + (int)v_radius_ext] = 1;

			v_teta = v_teta + v_step;

			if( atan(y / x) > v_are ) v_follow = false;

		} while ( v_follow ) ;

		//--------------------------
		// Section C
		//--------------------------
		v_step = 0.1;
		v_follow = true;

		v_teta = v_are * 180 / PI;

		do
		{
			x = v_radius_ext * cos(v_teta * PI / 180);
			y = v_radius_ext * sin(v_teta * PI / 180);

			v_val01 = rotationX(v_taurot, x, y );
			v_val02 = rotationY(v_taurot, x, y );

			aPos[(int)v_val01 + (int) v_radius_ext][(int)v_val02 + (int)v_radius_ext] = 1;

			v_teta = v_teta + v_step;

			if( v_teta > (v_are + v_se) * 180 / PI ) v_follow = false;

		} while ( v_follow ) ;

		//--------------------------
		// Section D
		//--------------------------
        v_step = 0.1;
		v_follow = true;

		v_teta = v_tre * 180 / PI;

		do
		{
			x1 = ( v_radius_base * cos(v_teta * PI / 180))
				  + ( v_radius_base * v_teta * PI / 180 * sin ( v_teta * PI / 180));
			y1 = -((v_radius_base * sin(v_teta * PI / 180)) 
				   - (v_radius_base * v_teta * PI / 180 * cos(v_teta * PI / 180 )));

			x = rotationX(v_sigma * 180 / PI, x1, y1);
			y = rotationY(v_sigma * 180 / PI, x1, y1);

			v_val01 = rotationX(v_taurot, x, y);
			v_val02 = rotationY(v_taurot, x, y);

			aPos[(int)v_val01 + (int) v_radius_ext][(int)v_val02 + (int)v_radius_ext] = 1;

			v_teta = v_teta - v_step;

			if( v_teta < 0 ) v_follow = false;

		} while (v_follow);

		//--------------------------
		// Section E
		//--------------------------
		v_step = 0.1;
		v_follow = true;

		do
		{
			v_val01 = rotationX(v_taurot, x, y);
			v_val02 = rotationY(v_taurot, x, y);

			aPos[(int)v_val01 + (int) v_radius_ext][(int)v_val02 + (int)v_radius_ext] = 1;

			x = x - v_step;
			y = x * tan(v_sigma);
			r = sqrt(pow(x,2) + pow(y,2));

			if(r < v_radius_root) v_follow = false;

		} while(v_follow);

		//--------------------------
		// Section F
		//--------------------------
		v_step = 0.1;
		v_follow = true;
		v_teta = v_sigma * 180 / PI;

		do
		{
			x = (v_radius_root) * cos(v_teta * PI / 180);
			y = (v_radius_root) * sin(v_teta * PI / 180 );

			v_val01 = rotationX(v_taurot, x, y);
			v_val02 = rotationY(v_taurot, x, y);

			aPos[(int)v_val01 + (int) v_radius_ext][(int)v_val02 + (int)v_radius_ext] = 1;

			v_teta = v_teta + v_step;
			r= sqrt(pow(x,2) + pow(y,2));

			if ( v_teta > v_tau ) v_follow = false;

		} while( v_follow ) ;

		//--------------------------
		// Section Final
		//--------------------------

		v_taurot = v_taurot + v_tau;

		if ( v_taurot > (v_tau * p_pitch_number)) v_continue = false;

	} while(v_continue);

	//-----------------------------------
	// Gear Display
	//-----------------------------------
	Singleton *sing = (Singleton *)Singleton::getInstance();

	sing->g_AmountWidth = nRow;
	sing->g_AmountHeight = nCol;

	sing->refresh();
	sing->copyOriColor();

	byte v_color_r, v_color_g, v_color_b;

	for(int y=0; y<sing->g_AmountHeight; y++)
	{
		for(int x=0; x<sing->g_AmountWidth; x++)
		{
			if (aPos[x][y] == 1 )
			{
				v_color_r = 0;
				v_color_g = 0;
				v_color_b = 0;
			} else {
				v_color_r = 255;
				v_color_g = 255;
				v_color_b = 255;
			}
            
			sing->g_oriColor[y][x].r = v_color_r;
			sing->g_oriColor[y][x].g = v_color_g;
			sing->g_oriColor[y][x].b = v_color_b;
		}
	}

	sing->g_oldAmountWidth = sing->g_AmountWidth;
	sing->g_oldAmountHeight = sing->g_AmountHeight;


}

double rotationX ( double p_rot_ang, double p_x, double p_y)
{
	double v_return_value;

	v_return_value = (p_x * cos(p_rot_ang * PI / 180))
		             - (p_y * sin(p_rot_ang * PI / 180 ));
	return v_return_value;

}

double rotationY ( double p_rot_ang, double p_x, double p_y)
{
	double v_return_value;

	v_return_value =  (p_x * sin(p_rot_ang * PI / 180))
		             + (p_y * cos(p_rot_ang * PI / 180 ));

	return v_return_value; 
}
