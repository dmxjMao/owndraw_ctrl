#pragma once


/*�ؼ�����*/


//���ÿؼ�λ��
//����λ�ã�x,y,cx,cy; b:�Ƿ�ʹ��Ĭ�ϴ�С; b&&!cxʹ��Ĭ�ϴ�С��ʼ��
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

//���λ�ã�idrel��Կؼ���offx,offyƫ��; b:�Ƿ�ʹ��Ĭ�ϴ�С
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
