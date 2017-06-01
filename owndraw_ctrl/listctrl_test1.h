#pragma once
#include "utility.h"
#include <vector>


struct CLinkItem;


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
	virtual bool regex_callback(const boost::smatch& what);//ui����ص�
	virtual void PreSubclassWindow();

	LRESULT	CreateGroup(int nIndex, int nGroupId, CString strHeader);





public:
	enum SORTTYPE {//����������
		STRING,//�ַ���
		INTEGER,//����
		PERCENTAGE//�ٷֱ�
	};


protected:
	CImageList				m_imgList;
	CImageList				m_imgListSmall;
	CImageList				m_imgListState;
	std::map<CString, std::shared_ptr<CLinkItem>> m_linkMap;

private:
	int m_SortCol = -1;//��ǰѡ�����
	int m_preSortCol = -1;//֮ǰѡ�����
	bool m_Ascending = true;//����

	std::vector<CString>	m_vecColsName //����
		= { _T("����"),_T("����"), _T("�Ա�"), _T("����"), _T("��������"),_T("����") };
	std::vector<SORTTYPE>	m_vecSortType//����������
		= { STRING, INTEGER, STRING, STRING, PERCENTAGE };
	std::vector<CString>	m_vecGroupName
		= { _T("����"),_T("����"), _T("����"), _T("����") };

	LRESULT	CreateSingleGroup(/*int nIndex, int nGroupId, CString strHeader*/);
public:
	//afx_msg void OnLvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void MeasureItem(/*int nIDCtl, */LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//afx_msg void OnHdnTrack(NMHDR *pNMHDR, LRESULT *pResult);
	virtual INT_PTR OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
	void CellHitTest(const CPoint& pt, int& nRow, int& nCol) const;
	afx_msg BOOL OnToolNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomDraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);

	//afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
};



struct CLinkProperties
{
//public:
//	CLinkProperties();
//	virtual ~CLinkProperties();
//
//	void SetLinkProperties(COLORREF clrLink = DEFAULT_UNVISITED_COLOR,
//		COLORREF clrVisited = DEFAULT_VISITED_COLOR,
//		HCURSOR hCursorHotSpot = DEFAULT_HOTSPOT_CURSOR,
//		BOOL bUnderlinedLink = DEFAULT_UNDERLINED);
//
//	BOOL		GetUnderlinedLink() { return m_bUnderlinedLink; }
//	COLORREF	GetLinkColor() { return m_clrLink; }
//	COLORREF	GetVisitedLinkColor() { return m_clrVisited; }
//	HCURSOR		GetCursor() { return m_hCursorHotSpot; }

	//BOOL		m_bUnderlinedLink = TRUE;
	COLORREF	m_clrLink = RGB(0, 0, 255);
	COLORREF    m_clrVisited = RGB(128, 0, 128);
	HCURSOR		m_hCursorHotSpot = AfxGetApp()->LoadStandardCursor(IDC_HAND);
	CFont		m_fontLink;

	CLinkProperties() {
		LOGFONT lf;
		memset(&lf, 0, sizeof(LOGFONT));
		lf.lfHeight = -11;//Ĭ�ϴ�С
		lf.lfWeight = 400;
		_stprintf_s(lf.lfFaceName, _T("%s"), _T("MS Sans Serif"));
		lf.lfUnderline = TRUE;
		m_fontLink.CreateFontIndirect(&lf);
	}
};



struct CLinkItem : public CObject
{
	CLinkItem(CString& url, BOOL bVisited = FALSE)
		: m_strUrl(url), m_bVisited(bVisited) {}
//public:
//	CLinkItem();
//	virtual ~CLinkItem();
//
//public:
	//BOOL GetVisited() { return m_bVisited; }
	//void SetVisited(BOOL bVisited) { m_bVisited = bVisited; }

	//CString GetUrl() { return m_strUrl; }
	//void SetUrl(CString strUrl) { m_strUrl = strUrl; }

	//void SetLinkProperties(CLinkProperties* pLinkProp) { m_pLinkProp = pLinkProp; }

	//BOOL GetUnderlinedLink();

	//HCURSOR GetCursor();

	//COLORREF GetLinkColor();

//protected:
	
	CString m_strUrl;
	BOOL m_bVisited;
	CLinkProperties m_pLinkProp;
};