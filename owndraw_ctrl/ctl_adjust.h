#pragma once


/*�ؼ�����*/

//λ�øı䣬��С����
//#define AUTO_SET_CONTROL_POS(CtrlId)\


//���ÿؼ�λ��
//����λ�ã�x,y,cx,cy; b:�Ƿ�ʹ��Ĭ�ϴ�С
#define SET_CTL_LOC_ABSOLUTE(id,b,x,y,cx,cy) \
{\
	CWnd* pWnd = GetDlgItem(id);\
	if(b && !cx){\
		pWnd->SetWindowPos(0, x, y, cx, cy, SWP_NOZORDER | SWP_NOSIZE);\
	}\
	else{\
		pWnd->MoveWindow(x, y, cx, cy); \
	}\
}

//void SetCtrlLocAbsolute(int ctrlid, bool default, int x, int y, int cx = 0, int cy = 0);

//���λ�ã�idrel��Կؼ���offx,offyƫ��; b:�Ƿ�ʹ��Ĭ�ϴ�С
#define SET_CTL_POS_RELATIVE(id,idrel,b,offx,offy,cx,cy) \
{\
	RECT rc;\
	GetDlgItem(idrel)->GetWindowRect(&rc);\
	ScreenToClient(&rc);\
	if(b){\
		RECT rc2;\
		GetDlgItem(id)->GetWindowClient(&rc2);\
		SET_CTL_LOC_ABSOLUTE(id,rc.left+offx,rc.top+offy,rc2.cx,rc2.cy);\
	}\
	else{\
		SET_CTL_LOC_ABSOLUTE(id,rc.left+offx,rc.top+offy,cx,cy);\
	}\
}
