#pragma once
#include "utility.h"

class CMyBitmapButton : public CBitmapButton, public CUICfg
{
	//����
public:
	CMyBitmapButton();
	bool Init();
	CSize GetBitmapSize();

protected:

private:

	//����
public:

protected:
	//COLORREF			m_colorCtrlBG;//�ؼ�������ɫ				

private:
	virtual bool regex_callback(const boost::smatch& what);//ui����ص�
public:

	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnBnClicked();
};