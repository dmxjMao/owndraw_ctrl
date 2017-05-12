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
	//��ʼ��Ĭ��UI
	//����
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 20;
	_stprintf_s(lf.lfFaceName, _T("%s"), _T("����"));
	m_font.CreateFontIndirect(&lf);
	SetFont(&m_font);//���캯������û�пؼ�������ʧ��
					
	m_colorBG = COLOR_LIGHT_BLUE;//�ؼ�����ɫ
	m_colorText = COLOR_WHITE;//������ɫ

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
	//SetWindowText(_T("����123"));
	dc.SetTextColor(m_colorText);
	dc.DrawText(_T("  ����ϵͳĬ�ϵĻ�ɫ"),&rc, DT_SINGLELINE|DT_VCENTER);

}



CMyStatic1& CMyStatic1::operator & (const std::string& s)
{
	if (!m_uicfg)
		m_uicfg = std::make_shared<std::string>();

	(*m_uicfg) += s + ',';

	return(*this);
}