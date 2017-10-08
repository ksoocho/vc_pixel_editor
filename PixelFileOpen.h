#pragma once
#include "KsooPixelDrawView.h"

class CPixelFileOpen
{
public:
	CPixelFileOpen(void);
	CPixelFileOpen::CPixelFileOpen(CString str, CKsooPixelDrawView *pView);
	~CPixelFileOpen(void);

private:
	short CPixelFileOpen::ReTrans(char* b);
};

