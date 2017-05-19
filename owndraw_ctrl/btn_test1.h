#pragma once
#include "utility.h"

class CMyBitmapButton : public CBitmapButton, public CUICfg
{
	//方法
public:
	CMyBitmapButton();
	bool Init();
	CSize GetBitmapSize();

protected:

private:

	//属性
public:

protected:
	//COLORREF			m_colorCtrlBG;//控件背景颜色				

private:
	virtual bool regex_callback(const boost::smatch& what);//ui正则回调
public:

	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnBnClicked();
};