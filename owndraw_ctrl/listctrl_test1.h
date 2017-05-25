#pragma once
#include "utility.h"
#include <vector>

class CMyListCtrl1 : public CListCtrl, public CUICfg
{
	DECLARE_MESSAGE_MAP()
	friend int CALLBACK SortFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

public:
	CMyListCtrl1();
	bool Init();

	afx_msg void OnLvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult);

protected:
private:
	virtual bool regex_callback(const boost::smatch& what);//ui正则回调
	virtual void PreSubclassWindow();

	LRESULT	CreateGroup(int nIndex, int nGroupId, CString strHeader);





public:
	enum SORTTYPE {//列排序类型
		STRING,//字符串
		INTEGER,//整数
		PERCENTAGE//百分比
	};


protected:
	CImageList				m_imgList;//32px图标
	CImageList				m_imgListSmall;//16px图标
	CImageList				m_imgListState;//state图标
	CImageList				m_imgListGroup;//group图标

private:
	int m_SortCol = -1;//当前选择的列
	int m_preSortCol = -1;//之前选择的列
	bool m_Ascending = true;//升序

	std::vector<CString>	m_vecColsName //列名
		= { _T("姓名"),_T("年龄"), _T("性别"), _T("爱好"), _T("工作进度") };
	std::vector<SORTTYPE>	m_vecSortType//列排序类型
		= { STRING, INTEGER, STRING, STRING, PERCENTAGE };
	std::vector<CString>	m_vecGroupName
		= { _T("甲组"),_T("乙组"), _T("丙组"), _T("丁组") };

};