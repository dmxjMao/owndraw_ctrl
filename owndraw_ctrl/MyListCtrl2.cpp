// MyListCtrl2.cpp : 实现文件
//

#include "stdafx.h"
#include "owndraw_ctrl.h"
#include "MyListCtrl2.h"
#include "utility.h"


namespace {
	using std::string;
	using std::vector;
	using std::shared_ptr;
	using std::make_shared;

	struct PARAMSORT //排序元素
	{
		PARAMSORT(const shared_ptr<CListCtrl_DataModel>& datamodel, int columnData, bool ascending)
			:m_pDataModel(datamodel)
			, m_ColumnData(columnData)
			, m_Ascending(ascending)
		{}

		const shared_ptr<CListCtrl_DataModel>& m_pDataModel;
		int  m_ColumnData;
		bool m_Ascending;
	};

	// Comparison extracts values from the DataModel
	int CALLBACK SortFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
	{
		PARAMSORT& ps = *(PARAMSORT*)lParamSort;

		//lParam 行索引 ，这里按文本序
		const CString& left = ps.m_pDataModel->GetCellText((size_t)lParam1, ps.m_ColumnData);
		const CString& right = ps.m_pDataModel->GetCellText((size_t)lParam2, ps.m_ColumnData);

		if (ps.m_Ascending)
			return left < right;
		else
			return right < left;
	}

	struct SortFunc2
	{
		int m_ColumnData;
		bool m_Ascending;

		SortFunc2(int columnData, bool ascending)
			:m_ColumnData(columnData)
			, m_Ascending(ascending)
		{}

		bool operator()(const CListCtrl_DataRecord& left, const CListCtrl_DataRecord& right)
		{
			if (m_Ascending)
				return left.GetCellText(m_ColumnData, false) < right.GetCellText(m_ColumnData, false);
			else
				return right.GetCellText(m_ColumnData, false) < left.GetCellText(m_ColumnData, false);
		}
	};

}

// CMyListCtrl2

IMPLEMENT_DYNAMIC(CMyListCtrl2, CListCtrl)

CMyListCtrl2::CMyListCtrl2()
{
	m_pDataModel = make_shared<CListCtrl_DataModel>();
}

CMyListCtrl2::~CMyListCtrl2()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl2, CListCtrl)
	ON_NOTIFY_REFLECT_EX(LVN_COLUMNCLICK, OnHeaderClick)
	ON_NOTIFY_REFLECT_EX(LVN_GETDISPINFO, OnGetDispInfo)
END_MESSAGE_MAP()



// CMyListCtrl2 消息处理程序




void CMyListCtrl2::PreSubclassWindow()
{
	CListCtrl::PreSubclassWindow();

	//一定要拖动控件在DDX，否则这些样式都不起作用，LVS_OWNDATA更是要在属性单中指定
	ModifyStyle(0, LVS_REPORT);
	SetExtendedStyle(GetExtendedStyle() | LVS_EX_DOUBLEBUFFER |
		LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_COLUMNSNAPPOINTS);

	EnableWindowTheme(GetSafeHwnd(), L"ListView", L"Explorer", 0);
}



BOOL CMyListCtrl2::OnHeaderClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLISTVIEW* pLV = reinterpret_cast<NMLISTVIEW*>(pNMHDR);

	SetFocus();	// Ensure other controls gets kill-focus

	int colIndex = pLV->iSubItem;

	if (m_nSortCol == colIndex)
	{
		m_bAscending = !m_bAscending;
	}
	else
	{
		m_nSortCol = colIndex;
		m_bAscending = true;
	}

	if (SortColumn(m_nSortCol, m_bAscending))
		SetSortArrow(m_nSortCol, m_bAscending);

	return FALSE;	// Let parent-dialog get chance
}



void CMyListCtrl2::SetSortArrow(int colIndex, bool ascending)
{

	for (int i = 0; i < GetHeaderCtrl()->GetItemCount(); ++i)
	{
		HDITEM hditem = { 0 };
		hditem.mask = HDI_FORMAT;
		VERIFY(GetHeaderCtrl()->GetItem(i, &hditem));
		hditem.fmt &= ~(HDF_SORTDOWN | HDF_SORTUP);
		if (i == colIndex)
		{
			hditem.fmt |= ascending ? HDF_SORTDOWN : HDF_SORTUP;
		}
		VERIFY(CListCtrl::GetHeaderCtrl()->SetItem(i, &hditem));
	}

}

// The column version of GetItemData(), one can specify an unique
// identifier when using InsertColumn()
int CMyListCtrl2::GetColumnData(int col) const
{
	LVCOLUMN lvc = { 0 };
	lvc.mask = LVCF_SUBITEM;
	VERIFY(GetColumn(col, &lvc));
	return lvc.iSubItem;
}

bool CMyListCtrl2::SortColumn(int columnIndex, bool ascending)
{
	//if (GetItemCount() != m_pDataModel->GetRowIds())
	//	return false;

	//columnData可以是附加参数
	//int columnData = GetColumnData(columnIndex);
	//PARAMSORT paramsort(m_pDataModel, columnData, ascending);
	//SortItems(SortFunc, (DWORD_PTR)&paramsort);


	//使用LVS_OWNDATA，针对大数据，m_pDataModel是缓存
	int columnData = GetColumnData(columnIndex);
	std::stable_sort(m_pDataModel->GetRecords().begin(), 
		m_pDataModel->GetRecords().end(), SortFunc2(columnData, ascending));
	SetItemCount((int)m_pDataModel->GetRowIds());	// Refresh List-Control


	return true;

}



void CMyListCtrl2::LoadData()
{
	//if (GetHeaderCtrl()->GetItemCount() == 0)
	//{
	//	// Create Columns
	//	LVCOLUMN lvCol;
	//	lvCol.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_MINWIDTH;
	//	for (int col = 0; col < m_pDataModel->GetColCount(); ++col)
	//	{
	//		CString& title = const_cast<CString&>(m_pDataModel->GetColTitle(col));
	//		lvCol.pszText = title.GetBuffer();
	//		lvCol.cchTextMax = title.GetLength();
	//		lvCol.iSubItem = col;
	//		lvCol.cxMin = 2 * GetStringWidth(title);
	//		//VERIFY(InsertColumn(col, title, LVCFMT_LEFT, 100) != -1);
	//		InsertColumn(col, &lvCol);
	//	}
	//}
	//else
	//{
	//	// Empty list-control and force refresh
	//	DeleteAllItems();
	//	//ResetSortOrder();
	//	Invalidate();
	//	UpdateWindow();
	//}

	//// Insert data with callback
	//SetRedraw(FALSE);	// Disable redraw as InsertItem becomes so much faster
	//int nItem = 0;
	//for (size_t rowId = 0; rowId < m_pDataModel->GetRowIds(); ++rowId)
	//{
	//	nItem = InsertItem(++nItem, _T(""));	// Fastest to insert at the end
	//	VERIFY(nItem != -1);
	//	VERIFY(SetItemData(nItem, rowId));
	//	for (int col = 0; col < m_pDataModel->GetColCount(); ++col)
	//	{
	//		VERIFY(SetItemText(nItem, col, LPSTR_TEXTCALLBACK));
	//	}
	//}

	////自动列宽
	//AdjustColumnWidth();

	//SetRedraw(TRUE);
	//Invalidate();
	//UpdateWindow();

	if (GetHeaderCtrl()->GetItemCount() == 0)
	{
		// LVS_OWNERDATA is set using the Resource Editor

		// Create Columns
		for (int col = 0; col < m_pDataModel->GetColCount(); ++col)
		{
			const CString& title = m_pDataModel->GetColTitle(col);
			VERIFY(InsertColumn(col, title, LVCFMT_LEFT, 100, col) != -1);
		}
	}

	//ResetSortOrder();

	//m_DataModel = dataModel;	// Update our local "cache"

	// Tell list-control how much data we have, LVS_OWNDATA需要
	SetItemCount((int)m_pDataModel->GetRowIds());
}



BOOL CMyListCtrl2::OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVDISPINFO* pNMW = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	int nItem = pNMW->item.iItem;
	int nSubItem = pNMW->item.iSubItem;

	if (nItem< 0 || nItem >= GetItemCount())
		return FALSE;	// requesting invalid item

	if (nSubItem < 0 || nSubItem >= GetHeaderCtrl()->GetItemCount())
		return FALSE;	// requesting invalid column

	//int col = GetColumnData(nSubItem);  //为什么都返回0？
	//size_t rowId = (size_t)GetItemData(nItem);

	if (pNMW->item.mask & LVIF_TEXT)
	{
		// Request text
		CString& result = const_cast<CString&>(m_pDataModel->GetCellText(nItem, nSubItem));
		_tcsncpy_s(pNMW->item.pszText, pNMW->item.cchTextMax, result, pNMW->item.cchTextMax);
	}

	return FALSE;	// Let parent-dialog get chance
}


void CMyListCtrl2::AdjustColumnWidth()
{
	SetRedraw(FALSE);
	int nColumnCount = GetHeaderCtrl()->GetItemCount();

	for (int i = 0; i < nColumnCount; i++)
	{
		SetColumnWidth(i, LVSCW_AUTOSIZE);
		int nColumnWidth = GetColumnWidth(i);
		SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
		int nHeaderWidth = GetColumnWidth(i);

		SetColumnWidth(i, max(nColumnWidth, nHeaderWidth));
	}
	SetRedraw(TRUE);
}