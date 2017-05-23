#pragma once


/*控件布局*/

enum class RELATIVE_LOC { LEFT_TOP, RIGHT_TOP, LEFT_BOTTOM, RIGHT_BOTTOM };//相对位置

//设置控件位置
//绝对位置：x,y,cx,cy;
#define SetCtrlLocAbsolute(id,x,y,cx,cy) \
{\
	CWnd* pWnd = GetDlgItem(id);\
	if(pWnd){\
		pWnd->SetWindowPos(0, x, y, cx, cy, SWP_NOZORDER | SWP_NOREDRAW);\
	}\
}

//相对控件：idrel相对控件，offx,offy偏移; 
#define SetCtrlLocRelativeCtrl(id,idrel,dir,offx,offy) \
{\
	CWnd* pWnd = GetDlgItem(idrel); \
	if (pWnd) {\
		CRect rcCtrlrel;\
		pWnd->GetWindowRect(&rcCtrlrel);\
		CWnd* pWnd2 = GetDlgItem(id);\
		if (pWnd2) {\
			CRect rcCtrl;\
			pWnd2->GetClientRect(&rcCtrl);\
			int x, y;\
			switch (dir)\
			{\
			case RELATIVE_LOC::LEFT_TOP:\
				x = rcCtrlrel.left - offx - rcCtrl.Width();\
				y = rcCtrlrel.top;\
				break;\
			case RELATIVE_LOC::RIGHT_TOP:\
				x = rcCtrlrel.right + offx;\
				y = rcCtrlrel.top - offy;\
				break;\
			case RELATIVE_LOC::RIGHT_BOTTOM:\
				x = rcCtrlrel.right + offx;\
				y = rcCtrlrel.bottom + offy;\
				break;\
			case RELATIVE_LOC::LEFT_BOTTOM:\
				x = rcCtrlrel.left - offx - rcCtrl.Width();\
				y = rcCtrlrel.bottom + offy;\
				break;\
			}\
			pWnd2->SetWindowPos(0, x, y, rcCtrl.Width(), rcCtrl.Height(), SWP_NOZORDER | SWP_NOREDRAW);\
		}\
	}\
}

//相对对话框：id控件ID，dir：相对，offx偏移量(>0)
#define SetCtrlLocRelativeDlg(id,dir,offx,offy) \
{\
	CWnd* pWnd = GetDlgItem(id);\
	if (pWnd) {\
		CRect rcCtl;\
		pWnd->GetClientRect(&rcCtl);\
		CRect rcDlg;\
		GetClientRect(&rcDlg); \
		int x, y;\
		switch (dir) {\
		case RELATIVE_LOC::LEFT_TOP:\
			x = rcDlg.left + offx;\
			y = offy;\
			break;\
		case RELATIVE_LOC::RIGHT_TOP:\
			x = rcDlg.right - offx - rcCtl.Width();\
			y = offy;\
			break;\
		case RELATIVE_LOC::RIGHT_BOTTOM:\
			x = rcDlg.right - offx - rcCtl.Width();\
			y = rcDlg.bottom - offy - rcCtl.Height();\
			break;\
		case RELATIVE_LOC::LEFT_BOTTOM:\
			x = rcDlg.left + offx;\
			y = rcDlg.bottom - offy - rcCtl.Height();\
			break;\
		}\
		pWnd->SetWindowPos(0, x, y, rcCtl.Width(), rcCtl.Height(), SWP_NOZORDER | SWP_NOREDRAW); \
	}\
}


