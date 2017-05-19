#pragma once
#include "utility.h"
#include "btn_test1.h"

class CMyStatic1 : public CStatic, public CUICfg
{
	//方法
public:
	CMyStatic1();
	bool Init();
	
	//virtual CMyStatic1& operator & (const std::string& s);

protected:
	//CMyBitmapButton		m_test1;//关闭按钮

private:


	//属性
public:

protected:
	CFont				m_font;//字体
	COLORREF			m_colorCtrlBG;//控件背景颜色				
	COLORREF			m_colorText;//文字颜色
	COLORREF			m_colorHightLight;//文本高亮颜色

private:
	virtual bool regex_callback(const boost::smatch& what);//ui正则回调
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	//afx_msg void OnMouseLeave();
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
};