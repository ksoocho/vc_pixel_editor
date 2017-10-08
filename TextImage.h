#pragma once
#include "KsooPixelDrawView.h"


class CTextImage
{
public:
	CTextImage(void);
	CTextImage::CTextImage(CKsooPixelDrawView *pView, CString p_text_string);
	~CTextImage(void);	
};

