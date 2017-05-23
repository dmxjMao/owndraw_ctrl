#pragma once
#include "utility.h"

class CMyListCtrl1 : public CListCtrl, public CUICfg
{
	//����
	DECLARE_MESSAGE_MAP()
public:
	CMyListCtrl1();
	bool Init();

protected:
private:
	//����
public:
protected:
	CImageList				m_imgList;
	CImageList				m_imgListSmall;
	CImageList				m_imgListState;

private:
	virtual bool regex_callback(const boost::smatch& what);//ui����ص�
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();

	LRESULT	CreateSingleGroup(int nIndex, int nGroupId, CString strHeader);
public:
	afx_msg void OnLvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void MeasureItem(/*int nIDCtl, */LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnHdnTrack(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnEndtrack(NMHDR *pNMHDR, LRESULT *pResult);
};