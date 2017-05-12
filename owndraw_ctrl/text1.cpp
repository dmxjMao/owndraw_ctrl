#include "stdafx.h"
#include "text1.h"
#include "ctl_property.h"


CMyStatic1::CMyStatic1()
{

}

BEGIN_MESSAGE_MAP(CMyStatic1, CStatic)
ON_WM_PAINT()
END_MESSAGE_MAP()


bool CMyStatic1::Init()
{
	//初始化默认UI
	//字体
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 20;
	_stprintf_s(lf.lfFaceName, _T("%s"), _T("宋体"));
	m_font.CreateFontIndirect(&lf);
	SetFont(&m_font);//构造函数，还没有控件，调用失败
					
	m_colorBG = COLOR_LIGHT_BLUE;//控件背景色
	m_colorText = COLOR_WHITE;//文字颜色

	return true;
}




void CMyStatic1::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CStatic::OnPaint() for painting messages
	RECT rc;
	GetClientRect(&rc);
	dc.FillSolidRect(&rc, m_colorBG);

	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(m_font);
	//SetWindowText(_T("报警123"));
	dc.SetTextColor(m_colorText);
	dc.DrawText(_T("  三种系统默认的灰色"),&rc, DT_SINGLELINE|DT_VCENTER);

}



CMyStatic1& CMyStatic1::operator & (const std::string& s)
{
	if (!m_uicfg)
		m_uicfg = std::make_shared<std::string>();

	(*m_uicfg) += s + ',';

	return(*this);
}