#pragma once
#include "utility.h"

class CMyListCtrl1 : public CListCtrl, public CUICfg
{
	//方法
	DECLARE_MESSAGE_MAP()
public:
	CMyListCtrl1();

protected:
private:
	//属性
public:
protected:
	CImageList				m_imgList;
	CImageList				m_imgListSmall;
	CImageList				m_imgListState;

private:
	virtual bool regex_callback(const boost::smatch& what);//ui正则回调
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
public:
	afx_msg void OnLvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void MeasureItem(/*int nIDCtl, */LPMEASUREITEMSTRUCT lpMeasureItemStruct);
};