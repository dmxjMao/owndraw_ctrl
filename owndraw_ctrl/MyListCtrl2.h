#pragma once


// CMyListCtrl2
class CListCtrl_DataModel;

class CMyListCtrl2 : public CListCtrl
{
	DECLARE_DYNAMIC(CMyListCtrl2)

public:
	CMyListCtrl2();
	virtual ~CMyListCtrl2();
	void SetSortArrow(int col, bool ascending);//���ü�ͷ
	inline bool IsAscending() const { return m_bAscending; }
	int GetColumnData(int col) const;//������Զ�������
	bool SortColumn(int columnIndex, bool ascending);//����
	void LoadData();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
	afx_msg BOOL OnHeaderClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);

	void AdjustColumnWidth();

private:
	bool m_bAscending = false; //�Ƿ�����
	int m_nSortCol = -1;//�������
	//bool m_bStableSort = true;//�ȶ�����
	std::shared_ptr<CListCtrl_DataModel> m_pDataModel;//����
};


