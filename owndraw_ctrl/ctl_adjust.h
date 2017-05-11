#pragma once


/*控件布局*/


//设置控件位置
//绝对位置：x,y,cx,cy; b:是否使用默认大小; b&&!cx使用默认大小初始化
#define SET_CTL_LOC_ABSOLUTE(id,b,x,y,cx,cy) \
{\
	CWnd* pWnd = GetDlgItem(id);\
	if(pWnd){\
		if(b && !cx){\
			pWnd->SetWindowPos(0, x, y, cx, cy, SWP_NOZORDER | SWP_NOSIZE);\
		}\
		else{\
			pWnd->MoveWindow(x, y, cx, cy); \
		}\
	}\
}

//相对位置：idrel相对控件，offx,offy偏移; b:是否使用默认大小
#define SET_CTL_LOC_RELATIVE(id,idrel,b,offx,offy,cx,cy) \
{\
	CWnd* pWnd = GetDlgItem(id);\
	if(pWnd){\
		RECT rc;\
		GetDlgItem(idrel)->GetWindowRect(&rc);\
		ScreenToClient(&rc);\
		if (b && !cx) {\
			pWnd->SetWindowPos(0, rc.left + offx, rc.top + offy, cx, cy, SWP_NOZORDER | SWP_NOSIZE);\
		}\
		else{\
			pWnd->MoveWindow(rc.left + offx, rc.top + offy, cx, cy);\
		}\
	}\
}
