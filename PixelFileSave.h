#pragma once

class CPixelFileSave
{
public:
	CPixelFileSave(void);
	CPixelFileSave::CPixelFileSave(CString str);
	~CPixelFileSave(void);

private:
	char tmp[2];
	char* CPixelFileSave::Trans(short v);
};

