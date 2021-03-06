#pragma once


// CMyListCtrl2
class CListCtrl_DataModel;

class CMyListCtrl2 : public CListCtrl
{
	DECLARE_DYNAMIC(CMyListCtrl2)

public:
	CMyListCtrl2();
	virtual ~CMyListCtrl2();
	void SetSortArrow(int col, bool ascending);//设置箭头
	inline bool IsAscending() const { return m_bAscending; }
	int GetColumnData(int col) const;//排序的自定义数据
	bool SortColumn(int columnIndex, bool ascending);//排序
	void LoadData();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
	afx_msg BOOL OnHeaderClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);

	void AdjustColumnWidth();

private:
	bool m_bAscending = false; //是否升序
	int m_nSortCol = -1;//排序的列
	//bool m_bStableSort = true;//稳定排序
	std::shared_ptr<CListCtrl_DataModel> m_pDataModel;//数据
};


