#pragma once
#include "utility.h"

enum MYSTATIC_TYPE {
	MYSTATIC_1,
	MYSTATIC_2,
	MYSTATIC_TYPE_NUM
};

class CMyStatic1 : public CStatic, public CUICfg
{
	//����
public:
	CMyStatic1(MYSTATIC_TYPE t = MYSTATIC_1);
	inline void SetType(MYSTATIC_TYPE t) { m_type = t; }
	//bool Init();
	
	//virtual CMyStatic1& operator & (const std::string& s);

protected:
	//CMyBitmapButton		m_test1;//�رհ�ť

private:


	//����
public:

protected:
	CFont				m_font;//����
	COLORREF			m_colorCtrlBG;//�ؼ�������ɫ				
	COLORREF			m_colorText;//������ɫ
	COLORREF			m_colorHightLight;//�ı�������ɫ
	UINT m_type = MYSTATIC_1;
	CImageList m_il;
private:
	virtual bool regex_callback(const boost::smatch& what);//ui����ص�
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