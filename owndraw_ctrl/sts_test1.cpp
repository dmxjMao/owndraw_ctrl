#include "stdafx.h"
#include "resource.h"
#include "sts_test1.h"
#include "ctl_adjust.h"
#include "ctl_property.h"


bool				g_bMouseTrack = true;//�����ͣ����
COLORREF			g_color;//��ɫ����

CMyStatic1::CMyStatic1()
{
	try {
		//ui��������
		m_uiregex.assign(
			"textpoint\\s*[-:,./]\\s*([0-9]+)|"//�����С
			"textcolor\\s*[-:,./]\\s*(RGB[^@]+)|"//������ɫ	
			"ctrlbgcolor\\s*[-:,./]\\s*(RGB[^@]+)"//�ؼ�����ɫ
			, boost::regex_constants::icase);
	}
	catch (boost::regex_error e) {

	}
	
}

BEGIN_MESSAGE_MAP(CMyStatic1, CStatic)
ON_WM_PAINT()
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEHOVER()
ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()


bool CMyStatic1::Init()
{
	//��ʼ��Ĭ��UI
	//����
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 20;
	_stprintf_s(lf.lfFaceName, _T("%s"), _T("����"));
	m_font.CreateFontIndirect(&lf);
	SetFont(&m_font);//���캯������û�пؼ�������ʧ��
					
	m_colorCtrlBG = COLOR_LIGHT_BLUE;//�ؼ�����ɫ
	m_colorText = COLOR_WHITE;//������ɫ
	m_colorHightLight = COLOR_RED;//�����ı���ɫ


	//��ʽ
	//ModifyStyle(0, WS_POPUP);
	return true;
}




void CMyStatic1::OnPaint()
{
	
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CStatic::OnPaint() for painting messages
	RECT rc;
	GetClientRect(&rc);
	dc.FillSolidRect(&rc, m_colorCtrlBG);

	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(m_font);
	//SetWindowText(_T("����123"));
	dc.SetTextColor(m_colorText);
	dc.DrawText(_T(" ���Ǹ�����"),&rc, DT_SINGLELINE|DT_VCENTER);

	//if (!m_test1.GetSafeHwnd()) {
	//	m_test1.Create(_T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
	//		CRect(0, 0, 0, 0), this, ID_MYCTRL_TEST1);
	//	
	//	m_test1.LoadBitmaps(IDB_TEST1U);
	//	m_test1.SizeToContent();

	//	CSize bmSize = m_test1.GetBitmapSize();
	//	SetCtrlLocAbsolute(ID_MYCTRL_TEST1, DLG_SIZE_CX - 2 - bmSize.cx, 2, bmSize.cx, bmSize.cy);
	//	//m_test1.SetWindowPos(&wndTop, DLG_SIZE_CX - 2 - bmSize.cx, 2, bmSize.cx, bmSize.cy, SWP_NOREDRAW);
	//	m_test1.ShowWindow(SW_NORMAL);
	//}
}


bool CMyStatic1::regex_callback(const boost::smatch& what)
{
	//what[1] �����С
	//what[2] ������ɫ
	const int uicfgCnt = 3;//ui��������
	//std::bitset<uicfgCnt> bts;
	
	int i = 0;//ƥ�������
	for (i = 1; i < uicfgCnt; ++i) {
		if (what[i].matched)
			break;
	}

	switch (i) {
	case 1:
	{
		LOGFONT ft;
		m_font.GetLogFont(&ft);
		ft.lfHeight = stoi(what[i].str());
		m_font.DeleteObject();
		m_font.CreateFontIndirect(&ft);
		break;
	}
	case 2:
	{
		m_colorText = GetRGBfromString(what[i].str());
		break;
	}
	case 3:
		m_colorCtrlBG = GetRGBfromString(what[i].str());
		break;
	}

	return true;
}

void CMyStatic1::OnMouseMove(UINT nFlags, CPoint point)
{
	static CPoint PrePoint = CPoint(0, 0);
	if (MK_LBUTTON == nFlags)
	{
		if (point != PrePoint)
		{
			CPoint ptTemp = point - PrePoint;
			CRect rcWindow;
			GetParent()->GetWindowRect(&rcWindow);
			rcWindow.OffsetRect(ptTemp.x, ptTemp.y);
			GetParent()->MoveWindow(&rcWindow);
			return;
		}
	}
	PrePoint = point;
	////�����ͣ
	//if (g_bMouseTrack)
	//{
	//	g_bMouseTrack = false;
	//	TRACKMOUSEEVENT tme;
	//	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	//	tme.dwFlags = TME_HOVER | TME_LEAVE;
	//	//tme.dwHoverTime = HOVER_DEFAULT;  
	//	tme.dwHoverTime = 50;
	//	tme.hwndTrack = GetSafeHwnd();
	//	TrackMouseEvent(&tme);
	//}
	//__super::OnMouseMove(nFlags, point);
}


void CMyStatic1::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));//ʹ���ڿ��϶�
	SetCapture();

	__super::OnLButtonDown(nFlags, point);
}


void CMyStatic1::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture();

	//__super::OnLButtonUp(nFlags, point);
}


//void CMyStatic1::OnMouseHover(UINT nFlags, CPoint point)
//{
//	g_color = m_colorText;//����ԭ�����ı���ɫ
//	m_colorText = COLOR_RED;
//	Invalidate();
//}
//
//
//void CMyStatic1::OnMouseLeave()
//{
//	g_bMouseTrack = true;
//	m_colorText = g_color;
//	Invalidate();
//}


void CMyStatic1::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	//m_test1.AutoLoad(ID_TEST1, this);
	//SetCtrlLocRelativeDlg(ID_TEST1, RELATIVE_LOC::RIGHT_TOP, 1, 1);

	__super::PreSubclassWindow();
}
