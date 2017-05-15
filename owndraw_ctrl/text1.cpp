#include "stdafx.h"
#include "text1.h"
#include "ctl_property.h"


//ui��������
boost::regex g_regexUI(
	"textpoint\\s*[-:,./]\\s*([0-9]+)|"//�����С
	"textcolor\\s*[-:,./]\\s*(RGB[^@]+)|"//������ɫ	
	"ctrlbgcolor\\s*[-:,./]\\s*(RGB[^@]+)"//�ؼ�����ɫ
	, boost::regex_constants::icase
);

bool				g_bMouseTrack = true;//�����ͣ����
COLORREF			g_color;//��ɫ����

CMyStatic1::CMyStatic1()
{

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

}



CMyStatic1& CMyStatic1::operator & (const std::string& s)
{

	if (!m_uicfg)
		m_uicfg = std::make_shared<std::string>();
	//�����ظ�����
	size_t pos = s.find_first_of("-:,./");
	std::string strCfgname = s.substr(0,pos);
	pos = m_uicfg->find(strCfgname);
	if(std::string::npos == pos)
		(*m_uicfg) += s + '@';
	else {
		size_t posEnd = m_uicfg->find_first_of('@', pos);
		m_uicfg->replace(pos, posEnd - pos, s);
	}
	
	boost::sregex_iterator it(m_uicfg->begin(), m_uicfg->end(), g_regexUI), itend;
	//��ÿһ��ƥ��������Ȼ�����ظ����ã����Ƕ���ui�������ִ�����Ӱ��Ч��
	//std::for_each(it, itend, &CMyStatic1::regex_callback);
	for (; it != itend; ++it) {
		regex_callback(*it);
	}

	return(*this);
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
		ft.lfHeight = stoi(what[1].str());
		m_font.DeleteObject();
		m_font.CreateFontIndirect(&ft);
		break;
	}
	case 2:
	{
		m_colorText = GetRGBfromString(what[2].str());
		break;
	}
	case 3:
		m_colorCtrlBG = GetRGBfromString(what[3].str());
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
	//�����ͣ
	if (g_bMouseTrack)
	{
		g_bMouseTrack = false;
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_HOVER | TME_LEAVE;
		//tme.dwHoverTime = HOVER_DEFAULT;  
		tme.dwHoverTime = 50;
		tme.hwndTrack = GetSafeHwnd();
		TrackMouseEvent(&tme);
	}
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


void CMyStatic1::OnMouseHover(UINT nFlags, CPoint point)
{
	g_color = m_colorText;//����ԭ�����ı���ɫ
	m_colorText = COLOR_RED;
	Invalidate();
}


void CMyStatic1::OnMouseLeave()
{
	g_bMouseTrack = true;
	m_colorText = g_color;
	Invalidate();
}
