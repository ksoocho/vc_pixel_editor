#pragma once
#include "KsooPixelDrawView.h"
#include "Singleton.h"

class CPathGenerate
{
public:
	CPathGenerate(CKsooPixelDrawView *tView);
	~CPathGenerate(void);

private:
	CKsooPixelDrawView *pView;
	Singleton *sing;
	int sti_width, sti_height;
	int start_x;
	int start_y;
	int first_x, first_y, last_x, last_y, center_x, center_y;
	enum {
        UP      = 1,
        RIGHT   = 2,
        DOWN    = 4,
        LEFT    = 8,
        NODIR   = 15
    };
	
public:
	void MainHorizon();
	void PathHorizon();
	void PathTrace(int p_x_pos, int p_y_pos, int p_up_down);
private:
	int path_count;
public:
	void GcodeWrite(int p_x_pos, int p_y_pos, int p_up_down);
	void GcodeStart();
	void GcodeEnd();
	void GcodeCheckArea();
	void GcodeFileSave();
	void CheckArea(void);
	void MainOutLine(void);
	void PathOutLine(void);
	bool StillInMiro(int x, int y, int start_point_x, int start_point_y, int point_count);
	void TurnLeft(int &dir);
	void TurnRight(int &dir);
	bool BlockAhead(int x, int y, int dir);
	int GetPixel(int x_pos, int y_pos);
	void GoAhead(int &x, int &y, int dir);
	void RightOnBlock(int x, int y, int dir);
	void MainVertical(void);
	void PathVertical(void);
	void MainTraceLine(void);
	void GoLine(CString ewsn, int &x, int &y, int &dir);
	bool StillInLine(int &x, int &y, int &dir, int point_count);
	void PathTraceLine(void);
	void TraceLine(int x, int y, int dir);
	bool CheckGcodeSet(CString p_work_type);
	void PathFileSave(void);
};

