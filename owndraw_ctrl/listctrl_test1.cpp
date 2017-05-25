#include "stdafx.h"
#include "resource.h"
#include "listctrl_test1.h"
//#include <array>
#include <vector>


BEGIN_MESSAGE_MAP(CMyListCtrl1, CListCtrl)
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, &CMyListCtrl1::OnLvnEndlabeledit)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, &CMyListCtrl1::OnLvnColumnclick)
END_MESSAGE_MAP()



namespace {
	//enum SORTTYPE {
	//	STRING,
	//	INTEGER,
	//	PERCENTAGE
	//};

	//struct PARAMSORT {//排序参数
	//	PARAMSORT(CListCtrl* pListCtrl, int nCol, bool bAscending, SORTTYPE t)
	//		:pl(pListCtrl)
	//		, col(nCol)
	//		, asc(bAscending)
	//		, type(t)
	//	{}

	//	CListCtrl* pl;
	//	int  col;
	//	bool asc;
	//	SORTTYPE type;
	//};

}

//排序函数
//LPARAM LVITEM ，Ex是item的索引  
int CALLBACK SortFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);


CMyListCtrl1::CMyListCtrl1()
{

}

bool CMyListCtrl1::Init()
{
	//组
	CreateGroup(0, 0, _T("甲组"));

	return true;
}



bool CMyListCtrl1::regex_callback(const boost::smatch& what)
{
	return true;
}



void CMyListCtrl1::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0, LVS_REPORT);
	//ModifyStyleEx(0, LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);
	SetExtendedStyle(GetExtendedStyle() | LVS_EX_FULLROWSELECT 
		| LVS_EX_DOUBLEBUFFER | LVS_EX_HEADERDRAGDROP
		| LVS_EX_COLUMNSNAPPOINTS/*最小宽度*/ | LVS_EX_CHECKBOXES
		);

	//bool b = IsCommonControlsEnabled();
	//应用主题
	EnableWindowTheme(GetSafeHwnd(), _T("ListView"), _T("Explorer"), NULL);

	m_imgList.Create(32, 32, ILC_COLOR24, 0, 10);
	CBitmap bmp;
	bmp.LoadBitmap(IDB_listctrl1);
	m_imgList.Add(&bmp, RGB(0, 0, 0));
	SetImageList(&m_imgList, LVSIL_NORMAL);

	//m_imgListGroup.Create(16, 16, ILC_COLOR24, 0, 10);
	//CBitmap bmpGroup;
	//bmpGroup.LoadBitmap(IDB_listctrl1_small);
	//m_imgListGroup.Add(&bmpGroup, RGB(0, 0, 0));
	//SetImageList(&m_imgListGroup, LVSIL_GROUPHEADER);

	__super::PreSubclassWindow();
}



void CMyListCtrl1::OnLvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: Add your control notification handler code here
	const LVITEM& item = pDispInfo->item;

	CT2A pszA(item.pszText);
	//5个汉字或10个字母或组合
	if(item.pszText && strlen(pszA) <= 10)
		SetItemText(pDispInfo->item.iItem, 0, pDispInfo->item.pszText);

	*pResult = 0;
}



LRESULT CMyListCtrl1::CreateGroup(int nIndex,
	int nGroupId, CString strHeader)
{
	SetRedraw(FALSE);

	//列
	CHeaderCtrl* pHeader = GetHeaderCtrl();
	LVCOLUMN lvCol;
	lvCol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM | LVCF_MINWIDTH;
	//lvCol.fmt = LVCFMT_LEFT;

	int colWidthSum = 0, colWidth = 0;
	//int len = sizeof(g_strCols) / sizeof(g_strCols[0]);
	int len = m_vecColsName.size();
	for (int i = 0; i < len; ++i) {
		CString& str = m_vecColsName[i];

		lvCol.pszText = str.GetBuffer();
		lvCol.cchTextMax = str.GetLength();
		lvCol.iSubItem = i;
		colWidth = 2 * GetStringWidth(str);
		lvCol.cx = lvCol.cxMin = colWidth;
		colWidthSum += colWidth;

		InsertColumn(i, &lvCol);	
	}
	//设置最后一列宽度
	//RECT rc;
	//GetClientRect(&rc);
	//SetColumnWidth(len - 1, rc.right - colWidthSum + colWidth);
	//禁止列拖动
	//GetHeaderCtrl()->EnableWindow(FALSE);
	//设置第一列排序小箭头升序
	//HDITEM hditem = { 0 };
	//hditem.mask = HDI_FORMAT;
	//pHeader->GetItem(0, &hditem);
	//hditem.fmt |= HDF_SORTUP;
	//pHeader->SetItem(0, &hditem);


	//item
	//_T("姓名"),_T("年龄"), _T("性别"), _T("爱好"), _T("工作进度")
	std::vector<std::vector<CString>> vec = {
		{ _T("a"),_T("43"), _T("男"), _T("篮球"), _T("90%") },
		{ _T("b"),_T("12"), _T("男"), _T("足球"), _T("10%") },
		{ _T("c"),_T("3"), _T("女"), _T("篮球"), _T("2%") },
		{ _T("d"),_T("4"), _T("女"), _T("篮球"), _T("30%") },
		{ _T("e"),_T("56"), _T("男"), _T("篮球"), _T("90%") },
		{ _T("f"),_T("12"), _T("女"), _T("羽毛球"), _T("20%") },
		{ _T("g"),_T("32"), _T("女"), _T("保龄球"), _T("90%") },
		{ _T("h"),_T("22"), _T("男"), _T("高尔夫球"), _T("90%") },
		{ _T("i"),_T("25"), _T("男"), _T("篮球"), _T("90%") },
		{ _T("j"),_T("26"), _T("男"), _T("篮球"), _T("90%") },
		{ _T("a"),_T("43"), _T("男"), _T("篮球"), _T("90%") },
		{ _T("b"),_T("12"), _T("男"), _T("足球"), _T("10%") },
		{ _T("c"),_T("3"), _T("女"), _T("篮球"), _T("2%") },
		{ _T("d"),_T("4"), _T("女"), _T("篮球"), _T("30%") },
		{ _T("e"),_T("56"), _T("男"), _T("篮球"), _T("90%") },
		{ _T("f"),_T("12"), _T("女"), _T("羽毛球"), _T("20%") },
		{ _T("g"),_T("32"), _T("女"), _T("保龄球"), _T("90%") },
		{ _T("h"),_T("22"), _T("男"), _T("高尔夫球"), _T("90%") },
		{ _T("i"),_T("25"), _T("男"), _T("篮球"), _T("90%") },
		{ _T("j"),_T("26"), _T("男"), _T("篮球"), _T("90%") }
	};
	const int nItemCnt = vec.size();
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;

	for (int i = 0; i < nItemCnt; ++i) {
		CString& str0 = vec[i][0];
		InsertItem(i, str0);
		//lvItem.iGroup = i % (nItemCnt/4);//均分
		//lvItem.iItem = i;
		//lvItem.pszText = str0.GetBuffer();
		//InsertItem(&lvItem);

		for (int j = 1; j < len; ++j) {
			CString& str = vec[i][j];
			SetItemText(i, j, str);
		}
	}

	//组
	EnableGroupView(TRUE);

	LVGROUP lg = { 0 };
	lg.cbSize = sizeof(lg);
	lg.mask = LVGF_GROUPID | LVGF_HEADER | LVGF_STATE
		| LVGF_TASK /*| LVGF_DESCRIPTIONTOP | LVGF_DESCRIPTIONBOTTOM*/ ;
	lg.state = LVGS_COLLAPSIBLE;

	CString strFooter, strSubTitle, strTask;//只能一行
	//CString strDesc = _T("description top");//只能一行
	//CString strDescB = _T("description bottom");//只能一行
	for (int i = 0; i < (int)m_vecGroupName.size(); ++i) {
		lg.iGroupId = i;
		CString& gname = m_vecGroupName[i];
		lg.pszHeader = gname.GetBuffer();
		lg.cchHeader = gname.GetLength();
		
		//strFooter.Format(_T("Group Footer:%s"), gname);
		//lg.pszFooter = strFooter.GetBuffer();
		//lg.cchFooter = strFooter.GetLength();

		//strSubTitle.Format(_T("SubTitle:%s"), gname);
		//lg.pszSubtitle = strSubTitle.GetBuffer();
		//lg.cchSubtitle = strSubTitle.GetLength();

		strTask.Format(_T("Task :%s"), gname);
		lg.pszTask = strTask.GetBuffer();
		lg.cchTask = strTask.GetLength();
		//lg.pszDescriptionTop = strDesc.GetBuffer();
		//lg.cchDescriptionTop = strDesc.GetLength();
		//lg.pszDescriptionBottom = strDescB.GetBuffer();
		//lg.cchDescriptionBottom= strDescB.GetLength();
		//lg.uAlign = LVGA_FOOTER_CENTER;
		//lg.iTitleImage = 1;  和文本不能重叠

		nGroupId = InsertGroup(i, &lg);//内部维护<索引,gid>
		if (-1 == nGroupId)
			return nGroupId;

		//绑定组：创建group就要绑定
		memset(&lvItem, 0, sizeof(LVITEM));
		lvItem.mask = LVIF_GROUPID;
		int cnt = nItemCnt / 4;//每组绑定多少个
		for (int nRow = nGroupId*cnt; nRow < (nGroupId+1)*cnt; ++nRow)
		{
			lvItem.iItem = nRow;
			lvItem.iGroupId = nGroupId;
			SetItem(&lvItem);
		}
	}



	SetRedraw();

	return nGroupId;
}







void CMyListCtrl1::OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	int nCol = pNMLV->iSubItem;
	if (m_SortCol == nCol){
		m_Ascending = !m_Ascending;
	}
	else{
		m_preSortCol = m_SortCol;
		m_SortCol = nCol;
		m_Ascending = true;
	}

	//设置排序小箭头，去掉之前，加上现在
	CHeaderCtrl* pHeader = GetHeaderCtrl();
	HDITEM hditem = { 0 };
	hditem.mask = HDI_FORMAT;
	if (pHeader->GetItem(m_preSortCol, &hditem)) {
		hditem.fmt &= ~(HDF_SORTDOWN | HDF_SORTUP);
		pHeader->SetItem(m_preSortCol, &hditem);
	}
	if (pHeader->GetItem(m_SortCol, &hditem)) {
		hditem.fmt &= ~(HDF_SORTDOWN | HDF_SORTUP);
		hditem.fmt |= m_Ascending ? HDF_SORTUP : HDF_SORTDOWN;
		pHeader->SetItem(m_SortCol, &hditem);
	}

	//PARAMSORT paramsort(this, nCol, m_Ascending, g_sortType[nCol]);
	//ListView_SortItemsEx(GetSafeHwnd(), SortFunc, &paramsort);
	SortItemsEx(SortFunc, (DWORD_PTR)this);

	*pResult = 0;
}


int CALLBACK SortFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	//PARAMSORT& ps = *(PARAMSORT*)lParamSort;
	CMyListCtrl1& pl = *((CMyListCtrl1*)lParamSort);

	const CString& left = pl.GetItemText(lParam1, pl.m_SortCol);
	const CString& right = pl.GetItemText(lParam2, pl.m_SortCol);

	int a, b;
	switch (pl.m_vecSortType[pl.m_SortCol])
	{
	case CMyListCtrl1::STRING:
		return pl.m_Ascending ? _tcscmp(left, right) : _tcscmp(right, left);
	case CMyListCtrl1::INTEGER:
	case CMyListCtrl1::PERCENTAGE:
		a = _ttoi(left); b = _ttoi(right);
		return pl.m_Ascending ? a > b : b > a;
	}

	return 1;
}