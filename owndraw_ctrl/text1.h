#pragma once
#include <string>
#include <memory>

class CMyStatic1 : public CStatic
{
	//����
public:
	CMyStatic1();
	bool Init();
	
	CMyStatic1& operator & (const std::string& s);


	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
protected:

private:


	//����
public:

protected:
	CFont				m_font;//����
	COLORREF			m_colorBG;//�ؼ�������ɫ				
	COLORREF			m_colorText;//������ɫ

private:
	std::shared_ptr<std::string>			m_uicfg;//ui����
};