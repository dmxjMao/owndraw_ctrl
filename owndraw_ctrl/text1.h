#pragma once
#include <string>
#include <memory>

class CMyStatic1 : public CStatic
{
	//方法
public:
	CMyStatic1();
	bool Init();
	
	CMyStatic1& operator & (const std::string& s);


	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
protected:

private:


	//属性
public:

protected:
	CFont				m_font;//字体
	COLORREF			m_colorBG;//控件背景颜色				
	COLORREF			m_colorText;//文字颜色

private:
	std::shared_ptr<std::string>			m_uicfg;//ui配置
};