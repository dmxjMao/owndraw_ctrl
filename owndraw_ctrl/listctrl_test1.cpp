#include "stdafx.h"
#include "resource.h"
#include "listctrl_test1.h"


BEGIN_MESSAGE_MAP(CMyListCtrl1, CListCtrl)
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, &CMyListCtrl1::OnLvnEndlabeledit)
	ON_WM_MEASUREITEM_REFLECT()
	
	//ON_NOTIFY(HDN_TRACKA, 0, &CMyListCtrl1::OnHdnTrack)
	ON_NOTIFY(HDN_TRACKW, 0, &CMyListCtrl1::OnHdnTrack)
	ON_NOTIFY(HDN_ENDTRACKA, 0, &CMyListCtrl1::OnHdnEndtrack)
	ON_NOTIFY(HDN_ENDTRACKW, 0, &CMyListCtrl1::OnHdnEndtrack)
END_MESSAGE_MAP()

CMyListCtrl1::CMyListCtrl1()
{

}

bool CMyListCtrl1::Init()
{
	//组
	CreateSingleGroup(0, 0, _T("甲组"));

	return true;
}



bool CMyListCtrl1::regex_callback(const boost::smatch& what)
{
	return true;
}

BOOL CMyListCtrl1::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class

	return __super::PreCreateWindow(cs);
}


void CMyListCtrl1::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(LVS_ALIGNLEFT, LVS_REPORT
		/*| LVS_OWNERDRAWFIXED*/);
	//SendMessage(WM_WINDOWPOSCHANGED, 0, 0);

	//SetBkColor(RGB(0, 255, 0));
	//CImageList* pImgList = GetImageList(LVSIL_NORMAL);
	m_imgList.Create(32, 32, ILC_COLOR24, 0, 5);
	CBitmap bmp;
	bmp.LoadBitmap(IDB_listctrl1);
	m_imgList.Add(&bmp, RGB(0, 0, 0));
	SetImageList(&m_imgList, LVSIL_NORMAL);

	//int cx, cy;
	//GetItemSpacing(FALSE, &cx, &cy);
	//CSize sz(32+10, cy-10);
	//SetIconSpacing(sz);

//	LVITEM item;
//	typedef struct tagLVITEMW
//	{
//		UINT mask;//LVIF_COLFMT(piColFmt,cColumns),LVIF_COLUMNS(cColumns),...
//		int iItem;//item索引
//		int iSubItem;//report
//		UINT state;//被覆盖，被拖动，被剪切等，特复杂
//		UINT stateMask;//哪些state可检索
//		LPWSTR pszText;
//		int cchTextMax;
//		int iImage;
//		LPARAM lParam;
//		int iIndent;//缩进以image宽为单位
//#if (NTDDI_VERSION >= NTDDI_WINXP)
//		int iGroupId;
//		UINT cColumns; // 数据列tile view columns
//		PUINT puColumns;
//#endif
//#if (NTDDI_VERSION >= NTDDI_VISTA)
//		int* piColFmt;
//		int iGroup; // readonly. only valid for owner data.
//#endif
//	} LVITEMW, *LPLVITEMW;

	//int nImgCnt = m_imgList.GetImageCount();
	//for (int i = 0; i < nImgCnt; ++i) {
	//	InsertItem(i, _T("animal"), i);
	//}


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







void CMyListCtrl1::MeasureItem(/*int nIDCtl, */LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: Add your message handler code here and/or call default
	/*当 combo box , list box, list-view,menu item 创建时，发送给owner window
	*/
	lpMeasureItemStruct->itemHeight = 70;

	//__super::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}


LRESULT CMyListCtrl1::CreateSingleGroup(int nIndex,
	int nGroupId, CString strHeader)
{
	//列
	CString strCols[] = { _T("姓名"),_T("年龄"), _T("性别"), _T("爱好"), _T("工作进度") };
	LVCOLUMN lvCol;
	lvCol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM | LVCF_FMT;
	lvCol.fmt = LVCFMT_LEFT;

	int colWidthSum = 0, colWidth = 0;
	int len = sizeof(strCols) / sizeof(strCols[0]);
	for (int i = 0; i < len; ++i) {
		CString& str = strCols[i];

		lvCol.pszText = str.GetBuffer();
		lvCol.cchTextMax = str.GetLength();
		lvCol.iSubItem = i;
		colWidth = 2 * GetStringWidth(str);
		lvCol.cx = colWidth;
		colWidthSum += colWidth;

		InsertColumn(i, &lvCol);	
	}
	//设置最后一列宽度
	//RECT rc;
	//GetClientRect(&rc);
	//SetColumnWidth(len - 1, rc.right - colWidthSum + colWidth);
	//禁止列拖动
	//GetHeaderCtrl()->EnableWindow(FALSE);

	/*EnableGroupView(TRUE);

	LVGROUP lg = { 0 };
	lg.cbSize = sizeof(lg);
	lg.mask = LVGF_GROUPID | LVGF_HEADER | LVGF_STATE | LVGF_ALIGN;
	lg.iGroupId = nGroupId;
	lg.pszHeader = strHeader.GetBuffer();
	lg.cchHeader = strHeader.GetLength();
	lg.state = LVGS_NORMAL;
	lg.uAlign = LVGA_HEADER_LEFT;
	
	nGroupId = InsertGroup(nIndex, &lg);
	if (-1 == nGroupId)
		return nGroupId;

	for (int nRow = 0; nRow < GetItemCount(); ++nRow)
	{
		LVITEM lvItem = { 0 };
		lvItem.mask = LVIF_GROUPID;
		lvItem.iItem = nRow;
		lvItem.iSubItem = 0;
		lvItem.iGroupId = nGroupId;
		SetItem(&lvItem);
	}*/

	return nGroupId;
}





void CMyListCtrl1::OnHdnTrack(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: Add your control notification handler code here
	//HDITEM* p = phdr->pitem; //它并没有全部信息！

	//UINT mask = p->mask;
	//mask = mask & HDI_TEXT; 为0！

	//HDITEM item;
	//item.mask = HDI_TEXT;
	//TCHAR buf[MAX_PATH] = { 0 };
	//item.pszText = buf;
	//item.cchTextMax = MAX_PATH;
	//GetHeaderCtrl()->GetItem(phdr->iItem, &item);
	//
	//int minColWidth = 2 * GetStringWidth(item.pszText);
	//int nowColWidth = GetColumnWidth(phdr->iItem);
	//if (nowColWidth < minColWidth)
	//	SetColumnWidth(phdr->iItem, minColWidth);

	*pResult = 0;
}





void CMyListCtrl1::OnHdnEndtrack(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: Add your control notification handler code here
	HDITEM item;
	item.mask = HDI_TEXT;
	TCHAR buf[MAX_PATH] = { 0 };
	item.pszText = buf;
	item.cchTextMax = MAX_PATH;
	GetHeaderCtrl()->GetItem(phdr->iItem, &item);

	int minColWidth = 2 * GetStringWidth(item.pszText);
	//int nowColWidth = GetColumnWidth(phdr->iItem);  //和minColWidth一样！
	if (item.cxy < minColWidth)
		SetColumnWidth(phdr->iItem, minColWidth);

	*pResult = 0;
}
