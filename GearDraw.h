#pragma once
#include "KsooPixelDrawView.h"

class CGearDraw
{
public:
	CGearDraw(void);
	CGearDraw::CGearDraw(CKsooPixelDrawView *pView,double p_module, double p_pitch_number);
	~CGearDraw(void);

public:
	void CGearDraw::drawGear(double p_module, double p_pitch_number);
};

