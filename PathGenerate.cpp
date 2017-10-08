#include "StdAfx.h"
#include "PathGenerate.h"
#include "Singleton.h"

CPathGenerate::CPathGenerate(CKsooPixelDrawView *tView)
{
	pView = tView;
	sing = (Singleton *)Singleton::getInstance();
}

CPathGenerate::~CPathGenerate(void)
{
}

// --------------------------------------------------------------------------
// Routine Name : CheckGcodeSet
// Description  : Check G-Code Setting Value
// History      : 2016-07-17 KSOOCHO  Create
// --------------------------------------------------------------------------
bool CPathGenerate::CheckGcodeSet(CString p_work_type)
{

	float v_gcode_scale = pView->m_GcodeScale;
	float v_gcode_depth = pView->m_GcodeDepth;
	
	// Common Check
	if (v_gcode_scale > 100 || v_gcode_scale <= 0 )
	{
		AfxMessageBox(" Scale Rate(%)는 1 ~ 100 범위여야 합니다.");
		return false;
	}

	if (v_gcode_depth > 3.0 || v_gcode_depth <= 0 )
	{
		AfxMessageBox(" Depth Size(mm)는 0 ~ 3.0 범위여야 합니다.");
		return false;
	}

	// Special Check

	return true;
}

// --------------------------------------------------------------------------
// Routine Name : GetPixel
// Description  : 
// History      : 2016-07-17 KSOOCHO  Create
// --------------------------------------------------------------------------
int CPathGenerate::GetPixel(int x_pos, int y_pos)
{

	byte v_color_r, v_color_g, v_color_b;
	int  pixel;

    v_color_r = sing->g_oriColor[y_pos][x_pos].r;
	v_color_g = sing->g_oriColor[y_pos][x_pos].g;
	v_color_b = sing->g_oriColor[y_pos][x_pos].b;

	// BLACK이면 1
	if ( v_color_r == 0 && v_color_g == 0 &&  v_color_b == 0 ){
		pixel = 1;
	} else if ( v_color_r == 255 && v_color_g == 0 &&  v_color_b == 0 ){
		pixel = 2;
	} else if ( v_color_r == 0 && v_color_g == 255 &&  v_color_b == 0 ){
		pixel = 3;
	} else if ( v_color_r == 0 && v_color_g == 0 &&  v_color_b == 255 ){
		pixel = 4;
	} else {
		pixel = 0;
	}

	return pixel;
}

// --------------------------------------------------------------------------
// Routine Name : PathTrace
// Description  : Path 추출
// History      : 2016-07-17 KSOOCHO  Create
// --------------------------------------------------------------------------
void CPathGenerate::PathTrace(int p_x_pos, int p_y_pos, int p_up_down)
{
	CString str, str_x, str_y, str_z;
	int    val_x, val_y, val_z;

	val_x = (p_x_pos - start_x);
	val_y = (p_y_pos - start_y);
	val_z = p_up_down;
	
	str_x.Format("%d",val_x);
    str_y.Format("%d",val_y);
    str_z.Format("%d",val_z);
	str.Format("%s %s %s", str_x, str_y, str_z);
	
	path_count++;

	// Marking Trace
	sing->g_oriColor[p_y_pos][p_x_pos].r = 255;
	sing->g_oriColor[p_y_pos][p_x_pos].g = 0;
	sing->g_oriColor[p_y_pos][p_x_pos].b = 0;

	// Path Trace
	pView->m_List->AddString(str);

	//Delay
	//Sleep(10);
	//pView->m_wndPixel.SendMessage(WM_SETREDRAW,1,0);
	//pView->m_wndPixel.Invalidate();
	//pView->m_wndPreview.Invalidate();

	pView->Invalidate();	
}

// --------------------------------------------------------------------------
// Routine Name : GcodeWrite
// Description  : G Code 추출
// History      : 2016-07-17 KSOOCHO  Create
// --------------------------------------------------------------------------
void CPathGenerate::GcodeWrite(int p_x_pos, int p_y_pos, int p_up_down)
{
	float   val_x, val_y, val_z;
	float   val_scale, val_depth;
	CString str,str_x,str_y,str_z;

	float v_gcode_scale = pView->m_GcodeScale;
	float v_gcode_depth = pView->m_GcodeDepth;

	val_scale = v_gcode_scale/100; // Setup Value 적용
	val_depth = v_gcode_depth; // Setup Value 적용

	// ---------------------------------------
	// 이동모드
	// ---------------------------------------
	if ( p_up_down == 0 ) {

		val_x = (p_x_pos - start_x) * val_scale;
		val_y = (p_y_pos - start_y) * val_scale;
		val_z = 2.0;

		str_x.Format("%s%.4f","X",val_x);
		str_y.Format("%s%.4f","Y",val_y);
		str_z.Format("%s%.4f","Z",val_z);

		// CNC End Point
		str.Format("%s %s %s", "G01", str_x, str_y);
		pView->m_GList->AddString(str);

		str.Format("%s %s", "G00", str_z );
        pView->m_GList->AddString(str);

	// ---------------------------------------
    // 절삭모드
	// ---------------------------------------
	} else {

		val_x = (p_x_pos - start_x) * val_scale;
		val_y = (p_y_pos - start_y) * val_scale;
		val_z = (-1) * (0.1 + val_depth);

		str_x.Format("%s%.4f","X",val_x);
        str_y.Format("%s%.4f","Y",val_y);
        str_z.Format("%s%.4f","Z",val_z);

        // CNC Start Point
        str.Format("%s %s %s", "G00", str_x, str_y);
        pView->m_GList->AddString(str);
                           
        str.Format("%s %s", "G01", str_z );
        pView->m_GList->AddString(str);
	}
}

// --------------------------------------------------------------------------
// Routine Name : GcodeStart
// Description  : G Code Header
// History      : 2016-07-17 KSOOCHO  Create
// --------------------------------------------------------------------------
void CPathGenerate::GcodeStart()
{
	CString str;

	str.Format("%s","G21");
    pView->m_GList->AddString(str);
    str.Format("%s","G00 G17");
    pView->m_GList->AddString(str);
    str.Format("%s","G00 G90 X0.0 Y0.0 M3");
    pView->m_GList->AddString(str);
    str.Format("%s","G00 Z5.0");
    pView->m_GList->AddString(str);
    str.Format("%s","G01 Z2.0 F500.0");
    pView->m_GList->AddString(str);
}

// --------------------------------------------------------------------------
// Routine Name : GcodeEnd
// Description  : G Code Footer
// History      : 2016-07-17 KSOOCHO Create
// --------------------------------------------------------------------------
void CPathGenerate::GcodeEnd()
{
	CString str;

	str.Format("%s","G00 Z5.0");
    pView->m_GList->AddString(str);
    str.Format("%s","G00 X0.0 Y0.0");
    pView->m_GList->AddString(str);
}

// --------------------------------------------------------------------------
// Routine Name : GcodeCheckArea
// Description  : 
// History      : 2016-07-17 KSOOCHO Create
// --------------------------------------------------------------------------
void CPathGenerate::GcodeCheckArea()
{
	float v_scale;
	CString str, str_x, str_y;

	v_scale = 1; // 향후 Setup Value 적용

    str_x.Format("%s%.4f","X",((float)(first_x - start_x)/v_scale));
    str_y.Format("%s%.4f","Y",((float)(first_y - start_y)/v_scale));
    str.Format("%s %s %s", "G00", str_x, str_y);
    pView->m_GList->AddString(str);

    str_x.Format("%s%.4f","X",((float)(last_x - start_x)/v_scale));
    str_y.Format("%s%.4f","Y",((float)(first_y - start_y)/v_scale));
    str.Format("%s %s %s", "G00", str_x, str_y);
    pView->m_GList->AddString(str);

    str_x.Format("%s%.4f","X",((float)(last_x - start_x) /v_scale));
    str_y.Format("%s%.4f","Y",((float)(last_y - start_y)/v_scale));
    str.Format("%s %s %s", "G00", str_x, str_y);
    pView->m_GList->AddString(str);

    str_x.Format("%s%.4f","X",((float)(first_x - start_x)/v_scale));
    str_y.Format("%s%.4f","Y",((float)(last_y - start_y)/v_scale));
    str.Format("%s %s %s", "G00", str_x, str_y);
    pView->m_GList->AddString(str);

    str_x.Format("%s%.4f","X",((float)(first_x - start_x)/v_scale));
    str_y.Format("%s%.4f","Y",((float)(first_y - start_y)/v_scale));
    str.Format("%s %s %s", "G00", str_x, str_y);
    pView->m_GList->AddString(str);

    // Center Point
    str_x.Format("%s%.4f","X",((float)(center_x - start_x)/v_scale));
    str_y.Format("%s%.4f","Y",((float)(center_y - start_y)/v_scale));
    str.Format("%s %s %s", "G00", str_x, str_y);
    pView->m_GList->AddString(str);
}

// --------------------------------------------------------------------------
// Routine Name : PathFileSave
// Description  : Path File 저장
// History      : 2016-07-17 KSOOCHO Create
// --------------------------------------------------------------------------
void CPathGenerate::PathFileSave(void)
{
	int pathCount = pView->m_List->GetCount();
    CString fileName;
    CString strItem;

    //canSave
    if(pathCount == 0){
		AfxMessageBox(" Path Log is empty.");
        return;
	}

    //File Save
    CFileDialog dlgFileOpen(FALSE,
                            "ks",
                            NULL,
                            OFN_FILEMUSTEXIST,
                            "Path(*.ks)|*.ks||",
                            NULL);

    if(dlgFileOpen.DoModal()==IDOK)
    {
        if(dlgFileOpen.GetFileExt()=="ks")
        {
            fileName = dlgFileOpen.GetPathName();
            CStdioFile f(fileName, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive);
            for(int i = 0; i < pathCount; i++)
            {
                pView->m_List->GetText(i,strItem);
                f.WriteString(_T(strItem+"\r"));
            }

            f.Close();

            AfxMessageBox("Path File Save - Success!!");   
        }
    }  // dlgFileOpen 
}

// --------------------------------------------------------------------------
// Routine Name : GcodeFileSave
// Description  : G Code File 저장
// History      : 2016-07-17 KSOOCHO Create
// --------------------------------------------------------------------------
void CPathGenerate::GcodeFileSave()
{
    int gcodeCount = pView->m_GList->GetCount();
    CString fileName;
    CString strItem;

    //canSave
    if(gcodeCount == 0){
		AfxMessageBox(" G-Code Log is empty.");
        return;
	}

    //File Save
    CFileDialog dlgFileOpen(FALSE,
                            "nc",
                            NULL,
                            OFN_FILEMUSTEXIST,
                            "G Code(*.nc)|*.nc||",
                            NULL);

    if(dlgFileOpen.DoModal()==IDOK)
    {
        if(dlgFileOpen.GetFileExt()=="nc")
        {
            fileName = dlgFileOpen.GetPathName();
            CStdioFile f(fileName, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive);
            for(int i = 0; i < gcodeCount; i++)
            {
                pView->m_GList->GetText(i,strItem);
                f.WriteString(_T(strItem+"\r"));
            }

            f.Close();

            AfxMessageBox("G Code File Save - Success!!");   
        }
    }  // dlgFileOpen 
}

// --------------------------------------------------------------------------
// Routine Name : CheckArea
// Description  : 작업영역에 대한 정보 Setting
//                시작Point, 완료Point, 중간Point
// History      : 2016-07-17 KSOOCHO Create
// --------------------------------------------------------------------------
void CPathGenerate::CheckArea(void)
{
	int   pixel;

	int  v_width  = sing->g_AmountWidth;
	int  v_height = sing->g_AmountHeight;

	sti_width = v_width;
	sti_height = v_height;

	first_x = v_width;
    first_y = v_height;
    last_x = 0;
    last_y = 0;

	for(int y = 0; y < v_height; y++)
    {
        for(int x = 0; x < v_width; x++)
        {
			pixel = GetPixel(x,y);

			if ( pixel != 0)
            {
                first_x = (first_x > x ? x: first_x);
                first_y = (first_y > y ? y: first_y);
                last_x  = (last_x < x ? x: last_x);
                last_y  = (last_y < y ? y: last_y);
            }

		}  // v_width

	} // v_height

	center_x = first_x+(int)((last_x-first_x)/2);
    center_y = first_y+(int)((last_y-first_y)/2);

	// Start Point 적용
	int v_start_x = 30; // pView->m_GcodeStartX;
	int v_start_y = 30; // pView->m_GcodeStartY;

	if ( first_x > v_start_x ) {
	    start_x = first_x - v_start_x;
	} else {
		start_x = 0;
	}

	if ( first_y > v_start_y ) {
	    start_y = first_y - v_start_y;
	} else {
		start_y = 0;
	}
}

// --------------------------------------------------------------------------
// Routine Name : MainHorizon
// Description  : 
// History      : 2016-07-17 KSOOCHO  Create
// --------------------------------------------------------------------------
void CPathGenerate::MainHorizon()
{

	// List Box Clear
	pView->m_List->ResetContent();
	pView->m_GList->ResetContent();

	// Check Setting Value
	if ( CheckGcodeSet("HOR") == false ) {
	    return;
	}

	// Check Workspace
	CheckArea();

	// G Code Start
	GcodeStart();

	// G Code Workspace
	GcodeCheckArea();
	
	// G Code 생성
	PathHorizon();

	// G Code 종료
	GcodeEnd();

}

// --------------------------------------------------------------------------
// Routine Name : GcodeWrite
// Description  : G Code 추출
// History      : 2016-07-17 KSOOCHO  Create
// --------------------------------------------------------------------------
void CPathGenerate::PathHorizon()
{
	int  step_cnt = 0, cnt = 0;
	int  pixel,temp_pixel;

	int  v_height = sing->g_AmountHeight;
	int  v_width  = sing->g_AmountWidth;

	// Path Count 초기화
	path_count = 0;
	step_cnt = 0;

	for(int y = 0; y < v_height; y++)
	{
		step_cnt++;
		temp_pixel = 0;

		// 홀수열인 경우
		if (step_cnt%2==1) {

			for(int x=0; x<v_width; x++)
			{
				pixel = GetPixel(x,y);

				if (pixel != temp_pixel) { // Pixel이 달라지는 경우

					if (pixel == 0) {
						// trace log ( up - end point로 활용한다)
						//PathTrace(x, y, 0);
						// G Code - x, y, z (up) 
						GcodeWrite(x, y, 0);
					} else {
						// trace log ( down )
						PathTrace(x, y, 1);
						// G Code - x, y, z (down)
						GcodeWrite(x, y, 1);
					}

				} else {  // Pixel이 같은 경우

					if (pixel==1) {
					    // trace log ( down )
						PathTrace(x, y, 1);
					}

				}

				temp_pixel = pixel;

			}
        // 짝수열인 경우
		} else {

			for(int x = v_width; x > 0; x--)
			{
				pixel = GetPixel(x,y);

				if (pixel != temp_pixel) {   // Pixel이 달라지는 경우

					cnt = cnt + 1;

					if (pixel == 0) {
						// G Code - x, y, z (up) 
						GcodeWrite(x, y, 0);
					} else {
						// trace log
						PathTrace(x, y, 1);
						// G Code - x, y, z (down)
						GcodeWrite(x, y, 1);
					}

				} else {   // Pixel이 같은 경우

					if (pixel == 1) {
					    // trace log
						PathTrace(x, y, 0);
					}

				}

				temp_pixel = pixel;

			} // v_width loop

		} // 홀수열,짝수열

	} // v_height loop 

}

// --------------------------------------------------------------------------
// Routine Name : MainVertical
// Description  : 
// History      : 2016-07-17 KSOOCHO  Create
// --------------------------------------------------------------------------
void CPathGenerate::MainVertical(void)
{
	// List Box Clear
	pView->m_List->ResetContent();
	pView->m_GList->ResetContent();

	// Check Setting Value
	if ( CheckGcodeSet("VER") == false ) {
	    return;
	}

	// Check Workspace
	CheckArea();

	// G Code Start
	GcodeStart();

	// G Code Workspace
	GcodeCheckArea();
	
	// G Code 생성
	PathVertical();

	// G Code 종료
	GcodeEnd();

}

// --------------------------------------------------------------------------
// Routine Name : PathVertical
// Description  : 
// History      : 2016-07-17 KSOOCHO  Create
// --------------------------------------------------------------------------
void CPathGenerate::PathVertical(void)
{
	int  step_cnt = 0, cnt = 0;
	int  pixel,temp_pixel;

	int  v_height = sing->g_AmountHeight;
	int  v_width  = sing->g_AmountWidth;

	// Path Count 초기화
	path_count = 0;
	step_cnt = 0;

	for(int x = 0; x < v_width; x++)
	{
		step_cnt++;
		temp_pixel = 0;

		// 홀수열인 경우
		if (step_cnt%2==1) {

			for(int y = 0; y < v_height; y++)
			{
				pixel = GetPixel(x,y);

				if (pixel != temp_pixel) { // Pixel이 달라지는 경우

					if (pixel == 0) {
						// trace log ( up - end point로 활용한다)
						//PathTrace(x, y, 0);
						// G Code - x, y, z (up) 
						GcodeWrite(x, y, 0);
					} else {
						// trace log ( down )
						PathTrace(x, y, 1);
						// G Code - x, y, z (down)
						GcodeWrite(x, y, 1);
					}

				} else {  // Pixel이 같은 경우

					if (pixel==1) {
					    // trace log ( down )
						PathTrace(x, y, 1);
					}

				}

				temp_pixel = pixel;

			}
        // 짝수열인 경우
		} else {

			for(int y = (v_height - 1); y >= 0; y--)
			{
				pixel = GetPixel(x,y);

				if (pixel != temp_pixel) {   // Pixel이 달라지는 경우

					cnt = cnt + 1;

					if (pixel == 0) {
						// G Code - x, y, z (up) 
						GcodeWrite(x, y, 0);
					} else {
						// trace log
						PathTrace(x, y, 1);
						// G Code - x, y, z (down)
						GcodeWrite(x, y, 1);
					}

				} else {   // Pixel이 같은 경우

					if (pixel == 1) {
					    // trace log
						PathTrace(x, y, 0);
					}

				}

				temp_pixel = pixel;

			} // v_height loop

		} // 홀수열,짝수열

	} // v_width loop 

}

// --------------------------------------------------------------------------
// Routine Name : MainOutLine
// Description  : 외곽선 추출 Main
// History      : 2016-07-17 KSOOCHO Create
// --------------------------------------------------------------------------
void CPathGenerate::MainOutLine(void)
{
	// List Box Clear
	pView->m_List->ResetContent();
	pView->m_GList->ResetContent();

	// Check Setting Value
	if ( CheckGcodeSet("OUT") == false ) {
	    return;
	}

	// Check Workspace
	CheckArea();

	// G Code Start
	GcodeStart();

	// G Code Workspace
	GcodeCheckArea();
	
	// G Code 생성- OutLine
	PathOutLine();

	// G Code 종료
	GcodeEnd();

}

// --------------------------------------------------------------------------
// Routine Name : PathOutLine
// Description  : 외곽선 추출 Process
// History      : 2016-07-17 KSOOCHO Create
// --------------------------------------------------------------------------
void CPathGenerate::PathOutLine(void)
{
	int   next_x;
	int   cur_pixel, next_pixel;

	int  v_height = sing->g_AmountHeight;
	int  v_width  = sing->g_AmountWidth;

	for(int y = 0; y < v_height; y++)
    {
        for(int x = 0; x < (v_width - 1); x++)
        {
			// WHITE-BLACK POINT를 찾아 Start Point로 한다

			// Current Point
            cur_pixel = GetPixel(x,y);

			// Next Point
			next_x = x + 1;
            next_pixel = GetPixel(next_x,y);

			// Start Point - Outline 
			if ( cur_pixel == 0 && next_pixel == 1 ) {			
				RightOnBlock(x, y, LEFT);			
			}

		}  // v_width
	} // v_height

}

// --------------------------------------------------------------------------
// Routine Name : RightOnBlock
// Description  : 
// History      : 2016-07-17 KSOOCHO Create
// --------------------------------------------------------------------------
void CPathGenerate::RightOnBlock(int x, int y, int dir)
{
	int start_point_x = x;
    int start_point_y = y;

	 int point_count = 1;

	 while (StillInMiro(x, y, start_point_x, start_point_y, point_count)) {  // 아직도 미로 안이면. 
	 
		 TurnRight(dir); // 오른쪽으로 틀기 

		 while (BlockAhead(x, y, dir)) { // 앞에 벽이 있으면 계속 
		     TurnLeft(dir);     // 왼쪽으로 튼다.  
		 }

		// 이동
        GoAhead(x, y, dir);

		point_count++;

        // trace log ( down )
		PathTrace(x, y, 1);
		// G Code - x, y, z (down)
		GcodeWrite(x, y, 1);

	 } // StillInMiro

    // trace log ( up )
	PathTrace(x, y, 0);
	// G Code - x, y, z (up)
	GcodeWrite(x, y, 0);

}

// --------------------------------------------------------------------------
// Routine Name : StillInMiro
// Description  : 
// History      : 2016-07-17 KSOOCHO Create
// --------------------------------------------------------------------------
bool CPathGenerate::StillInMiro(int x, int y, int start_point_x, int start_point_y, int point_count)
{
	int v_width  = sti_width; 
    int v_height = sti_height; 

    if (x > 0 && x < v_width - 1 && y > 0 && y < v_height - 1) // Map내부
    {
        if ( point_count > 1 && x == start_point_x && y == start_point_y ) // 원점으로 돌아오면
        {
            return false;
        } else {
            return true;
        }
    } else {
        return false;
    }
}

// --------------------------------------------------------------------------
// Routine Name : TurnLeft
// Description  : 
// History      : 2016-07-17 KSOOCHO Create
// --------------------------------------------------------------------------
void CPathGenerate::TurnLeft(int &dir)
{
	dir >>= 1;
    dir = (dir == 0 ? LEFT : dir);
}

// --------------------------------------------------------------------------
// Routine Name : TurnRight
// Description  : 
// History      : 2016-07-17 KSOOCHO Create
// --------------------------------------------------------------------------
void CPathGenerate::TurnRight(int &dir)
{
	dir <<= 1;
    dir = (dir > LEFT ? UP : dir);
}

// --------------------------------------------------------------------------
// Routine Name : BlockAhead
// Description  : 
// History      : 2016-07-17 KSOOCHO Create
// --------------------------------------------------------------------------
bool CPathGenerate::BlockAhead(int x, int y, int dir)
{
	int pixel;

	// 좌표를 한칸 이동하여 벽인지 아닌지를 체크한다.
    x = (dir == LEFT ? --x : dir == RIGHT ? ++x : x);
    y = (dir == UP ? --y : dir == DOWN ? ++y : y);

	pixel = GetPixel(x, y);

	return ( pixel == 1 ) ;
}

// --------------------------------------------------------------------------
// Routine Name : GoAhead
// Description  : 
// History      : 2016-07-17 KSOOCHO Create
// --------------------------------------------------------------------------
void CPathGenerate::GoAhead(int &x, int &y, int dir)
{
	// 좌표 이동
    x = (dir == LEFT ? --x : dir == RIGHT ? ++x : x);
    y = (dir == UP ? --y : dir == DOWN ? ++y : y);
}


// --------------------------------------------------------------------------
// Routine Name : MainTraceLine
// Description  : 
// History      : 2016-07-17 KSOOCHO Create
// --------------------------------------------------------------------------
void CPathGenerate::MainTraceLine(void)
{
	// List Box Clear
	pView->m_List->ResetContent();
	pView->m_GList->ResetContent();

	// Check Setting Value
	if ( CheckGcodeSet("TRC") == false ) {
	    return;
	}

	// Check Workspace
	CheckArea();

	// G Code Start
	GcodeStart();

	// G Code Workspace
	GcodeCheckArea();
	
	// G Code 생성- Trace Line
	PathTraceLine();

	// G Code 종료
	GcodeEnd();

}

// --------------------------------------------------------------------------
// Routine Name : PathTraceLine
// Description  : 
// History      : 2016-07-17 KSOOCHO Create
// --------------------------------------------------------------------------
void CPathGenerate::PathTraceLine(void)
{

	int   cur_pixel;

	int  v_height = sing->g_AmountHeight;
	int  v_width  = sing->g_AmountWidth;

	for(int y = 0; y < v_height; y++)
    {
        for(int x = 0; x < (v_width - 1); x++)
        {
			// Current Point
            cur_pixel = GetPixel(x,y);

			if (cur_pixel==1)
            {
                TraceLine(x, y, RIGHT);
            }

		}  // v_width

	} // v_height

}


// --------------------------------------------------------------------------
// Routine Name : TraceLine
// Description  : 
// History      : 2016-07-17 KSOOCHO Create
// --------------------------------------------------------------------------
void CPathGenerate::TraceLine(int x, int y, int dir)
{

	// trace log ( down )
	PathTrace(x, y, 1);
	// G Code - x, y, z (down)
	GcodeWrite(x, y, 1);
	
	int point_count = 1;

    while (StillInLine(x, y, dir, point_count))
    {
       point_count++;

	    // trace log ( down )
		PathTrace(x, y, 1);
		// G Code - x, y, z (down)
		GcodeWrite(x, y, 1);
    }

	 // trace log ( up )
	PathTrace(x, y, 0);
	// G Code - x, y, z (up)
	GcodeWrite(x, y, 0);

}

// --------------------------------------------------------------------------
// Routine Name : GoLine
// Description  : 
// History      : 2016-07-17 KSOOCHO Create
// --------------------------------------------------------------------------
void CPathGenerate::GoLine(CString ewsn, int &x, int &y, int &dir)
{
	if (ewsn=="E") {
        x--;
        dir=LEFT;
    }

    if (ewsn=="W") {
        x++;
        dir=RIGHT;
    }

    if (ewsn=="S")    {
        y++;
        dir = DOWN;
    }   
   
    if (ewsn=="N") {
        y--;
        dir = UP;
    }
       
    if (ewsn=="NE") {
        x--;
        y--;
        dir=LEFT;
    }
   
    if (ewsn=="NW") {
        x++;
        y--;
        dir=RIGHT;
    }       

    if (ewsn=="SE") {
        x--;
        y++;
        dir=LEFT;
    }

    if (ewsn=="SW") {
        x++;
        y++;
        dir=RIGHT;
    } 
}

// --------------------------------------------------------------------------
// Routine Name : StillInLine
// Description  : 
// History      : 2016-07-17 KSOOCHO Create
// --------------------------------------------------------------------------
bool CPathGenerate::StillInLine(int &x, int &y, int &dir, int point_count)
{
	int v_width      = sti_width; 
    int v_height     = sti_height; 

    if (x > 0 && x < v_width - 1 && y > 0 && y < v_height - 1) // Map내부
    {
        int pixel_E =  (dir == RIGHT ? 0 : ((int)GetPixel(x-1, y)==1   ? 1 : 0));
        int pixel_W =  (dir == LEFT ?  0 : ((int)GetPixel(x+1, y)==1   ? 1 : 0));
        int pixel_N =  (dir == DOWN ?  0 : ((int)GetPixel(x,   y-1)==1 ? 1 : 0));
        int pixel_S =  (dir == UP ?    0 : ((int)GetPixel(x,   y+1)==1 ? 1 : 0));
        int pixel_NE = (dir == RIGHT ? 0 : ((int)GetPixel(x-1, y-1)==1 ? 1 : 0));
        int pixel_NW = (dir == DOWN ?  0 : ((int)GetPixel(x+1, y-1)==1 ? 1 : 0));
        int pixel_SW = (dir == LEFT ?  0 : ((int)GetPixel(x+1, y+1)==1 ? 1 : 0));
        int pixel_SE = (dir == UP ?    0 : ((int)GetPixel(x-1, y+1)==1 ? 1 : 0));

        if ((point_count>1)&&(pixel_E+pixel_W+pixel_N+pixel_S+pixel_NE+pixel_NW+pixel_SW+pixel_SE==0))
        {
            return false;
        } else {
            if (dir==RIGHT)    {
                if (pixel_N==1)    {
                    GoLine("N", x, y, dir);
                } else if (pixel_W==1) {
                    GoLine("W", x, y, dir);
                } else if (pixel_S==1) {
                    GoLine("S", x, y, dir);
                } else if (pixel_NW==1) {
                    GoLine("NW", x, y, dir);
                } else if (pixel_SW==1) {
                    GoLine("SW", x, y, dir);
                } else if (pixel_SE==1) {
                    GoLine("SE", x, y, dir);
                } else if (pixel_NE==1) {
                    GoLine("NE", x, y, dir);
                } else if (pixel_E==1) {
                    GoLine("E", x, y, dir);
                }

            } else if (dir==UP) {
                if (pixel_E==1)    {
                    GoLine("E", x, y, dir);
                } else if (pixel_N==1) {
                    GoLine("N", x, y, dir);
                } else if (pixel_W==1) {
                    GoLine("W", x, y, dir);
                } else if (pixel_NE==1) {
                    GoLine("NE", x, y, dir);
                } else if (pixel_NW==1) {
                    GoLine("NW", x, y, dir);
                } else if (pixel_SW==1) {
                    GoLine("SW", x, y, dir);
                } else if (pixel_SE==1) {
                    GoLine("SE", x, y, dir);
                } else if (pixel_S==1) {
                    GoLine("S", x, y, dir);
                }
            } else if (dir==DOWN) {
                if (pixel_W==1)    {
                    GoLine("W", x, y, dir);
                } else if (pixel_S==1) {
                    GoLine("S", x, y, dir);
                } else if (pixel_E==1) {
                    GoLine("E", x, y, dir);
                } else if (pixel_SW==1) {
                    GoLine("SW", x, y, dir);
                } else if (pixel_SE==1) {
                    GoLine("SE", x, y, dir);
                } else if (pixel_NE==1) {
                    GoLine("NE", x, y, dir);
                } else if (pixel_NW==1) {
                    GoLine("NW", x, y, dir);
                } else if (pixel_N==1) {
                    GoLine("N", x, y, dir);
                }
            } else if (dir==LEFT) {
                if (pixel_E==1)    {
                    GoLine("E", x, y, dir);
                } else if (pixel_S==1) {
                    GoLine("S", x, y, dir);
                } else if (pixel_N==1) {
                    GoLine("N", x, y, dir);
                } else if (pixel_SE==1) {
                    GoLine("SE", x, y, dir);
                } else if (pixel_NE==1) {
                    GoLine("NE", x, y, dir);
                } else if (pixel_NW==1) {
                    GoLine("NW", x, y, dir);
                } else if (pixel_SW==1) {
                    GoLine("SW", x, y, dir);
                } else if (pixel_W==1) {
                    GoLine("W", x, y, dir);
                }       
            }

             return true;
        }
    } else {
        return false;
    }


}


