#pragma once
#include "KsooPixelDrawView.h"
#include "Singleton.h"

class CShapeDraw
{
public:
	CShapeDraw(CKsooPixelDrawView *tView);
	~CShapeDraw(void);

private:
	CKsooPixelDrawView *pView;
	Singleton *sing;

public:
	void RectangleDraw(int p_top_x, int p_top_y, int p_bottom_x, int p_bottom_y);
	void CircleDraw(int p_center_x, int p_center_y, int p_radius);
	void LineDraw(int p_top_x, int p_top_y, int p_bottom_x, int p_bottom_y);
	void RoundRectDraw(int p_top_x, int p_top_y, int p_bottom_x, int p_bottom_y);
};

