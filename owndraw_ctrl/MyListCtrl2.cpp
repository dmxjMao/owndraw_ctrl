// MyListCtrl2.cpp : 实现文件
//

#include "stdafx.h"
#include "owndraw_ctrl.h"
#include "MyListCtrl2.h"
#include "utility.h"

using std::string;
using std::vector;

namespace {
	struct PARAMSORT //排序元素
	{
		PARAMSORT(const CListCtrl_DataModel& datamodel, int columnData, bool ascending)
			:m_DataModel(datamodel)
			, m_ColumnData(columnData)
			, m_Ascending(ascending)
		{}

		const CListCtrl_DataModel& m_DataModel;
		int  m_ColumnData;
		bool m_Ascending;
	};

	// Comparison extracts values from the DataModel
	int CALLBACK SortFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
	{
		PARAMSORT& ps = *(PARAMSORT*)lParamSort;

		const string& left = ps.m_DataModel.GetCellText((size_t)lParam1, ps.m_ColumnData);
		const string& right = ps.m_DataModel.GetCellText((size_t)lParam2, ps.m_ColumnData);

		if (ps.m_Ascending)
			return strcmp(left.c_str(), right.c_str());
		else
			return strcmp(right.c_str(), left.c_str());
	}
}

// CMyListCtrl2

IMPLEMENT_DYNAMIC(CMyListCtrl2, CListCtrl)

//CMyListCtrl2::CMyListCtrl2()
//{
//
//}

CMyListCtrl2::~CMyListCtrl2()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl2, CListCtrl)
	ON_NOTIFY_REFLECT_EX(LVN_COLUMNCLICK, OnHeaderClick)
END_MESSAGE_MAP()



// CMyListCtrl2 消息处理程序




void CMyListCtrl2::PreSubclassWindow()
{
	CListCtrl::PreSubclassWindow();

	//SetExtendedStyle(GetExtendedStyle() | LVS_EX_DOUBLEBUFFER |
	//	LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);
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
	if (GetItemCount() != m_DataModel.GetRowIds())
		return false;

	int columnData = GetColumnData(columnIndex);
	PARAMSORT paramsort(m_DataModel, columnData, ascending);
	SortItems(SortFunc, (DWORD_PTR)&paramsort);
	return true;

}



void CMyListCtrl2::LoadData()
{
	if (GetHeaderCtrl()->GetItemCount() == 0)
	{
		// Create Columns
		for (int col = 0; col < m_DataModel.GetColCount(); ++col)
		{
			const string& title = m_DataModel.GetColTitle(col);
			VERIFY(InsertColumn(col, CString(title.c_str()), LVCFMT_LEFT, 100) != -1);
		}
	}
	else
	{
		// Empty list-control and force refresh
		DeleteAllItems();
		//ResetSortOrder();
		Invalidate();
		UpdateWindow();
	}

	// Insert data with callback
	SetRedraw(FALSE);	// Disable redraw as InsertItem becomes so much faster
	int nItem = 0;
	for (size_t rowId = 0; rowId < m_DataModel.GetRowIds(); ++rowId)
	{
		nItem = InsertItem(++nItem, _T(""));	// Fastest to insert at the end
		VERIFY(nItem != -1);
		VERIFY(SetItemData(nItem, rowId));
		for (int col = 0; col < m_DataModel.GetColCount(); ++col)
		{
			VERIFY(SetItemText(nItem, col, LPSTR_TEXTCALLBACK));
		}
	}
	SetRedraw(TRUE);
	Invalidate();
	UpdateWindow();
}