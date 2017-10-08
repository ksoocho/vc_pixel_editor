#pragma once
#include "KsooPixelDrawView.h"

class CImageFileOpen
{
public:
	CImageFileOpen(void);
	CImageFileOpen::CImageFileOpen(CKsooPixelDrawView *pView, CString p_image_file_path);
	~CImageFileOpen(void);
};

