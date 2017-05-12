#pragma once


/*�ؼ�����*/


//���ÿؼ�λ��
//����λ�ã�x,y,cx,cy; b:�Ƿ�ʹ��Ĭ�ϴ�С; b&&!cxʹ��Ĭ�ϴ�С��ʼ��
//UINT flag = (b && !cx) ? (SWP_NOZORDER | SWP_NOSIZE) : SWP_NOZORDER;
#define SET_CTL_LOC_ABSOLUTE(id,x,y,cx,cy) \
{\
	CWnd* pWnd = GetDlgItem(id);\
	if(pWnd){\
		pWnd->SetWindowPos(0, x, y, cx, cy, SWP_NOZORDER);\
	}\
}

//���λ�ã�idrel��Կؼ���offx,offyƫ��; b:�Ƿ�ʹ��Ĭ�ϴ�С
#define SET_CTL_LOC_RELATIVE(id,idrel,offx,offy,cx,cy) \
{\
	CWnd* pWnd = GetDlgItem(id);\
	if(pWnd){\
		RECT rc;\
		GetDlgItem(idrel)->GetWindowRect(&rc);\
		ScreenToClient(&rc);\
		pWnd->SetWindowPos(0, rc.left + offx, rc.top + offy, cx, cy, SWP_NOZORDER);\
	}\
}
