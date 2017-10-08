#pragma once
#include "KsooPixelDrawView.h"

class CImageBinary
{
public:
	CImageBinary(void);
	CImageBinary(CKsooPixelDrawView *pView, int p_binary_unity);
	CImageBinary(CKsooPixelDrawView *pView, int p_binary_thread_low, int p_binary_thread_high);
	CImageBinary::CImageBinary(CKsooPixelDrawView *pView, CString p_work_code, int p_degree);
	~CImageBinary(void);
};

