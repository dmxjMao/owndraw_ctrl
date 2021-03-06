#include "stdafx.h"
#include "resource.h"
#include "listctrl_test1.h"
//#include <array>
#include <vector>
#include <map>

namespace {
	std::map<CString, CString> g_mapTooltipStr = {
		{ _T("篮球"),_T("篮球运动是\r\n1891年由美国人詹姆斯奈史密斯发明的。") },
		{ _T("女"),_T("女氏，有两个来源") },
		{ _T("足球"),_T("足球，有“世界第一运动”的美誉，是全球体育界最具影响力的单项体育运动。") },
		{ _T("羽毛球"),_T("羽毛球是一项室内，室外都可以进行的体育运动。") },
		{ _T("保龄球"),_T("保龄球，又称地滚球，是在木板道上滚球击柱的一种室内运动。") },
		{ _T("男"),_T("毛奕男") },
		{ _T("h"),_T("这个家伙就是boss！") },
	};
}


BEGIN_MESSAGE_MAP(CMyListCtrl1, CListCtrl)
	//ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, &CMyListCtrl1::OnLvnEndlabeledit)
	ON_WM_MEASUREITEM_REFLECT()
	
	//ON_NOTIFY(HDN_TRACKW, 0, &CMyListCtrl1::OnHdnTrack)
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolNeedText)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CMyListCtrl1::OnCustomDraw)
	ON_NOTIFY_REFLECT(NM_CLICK, &CMyListCtrl1::OnNMClick)
	//ON_NOTIFY_REFLECT(NM_RCLICK, &CMyListCtrl1::OnNMRClick)
END_MESSAGE_MAP()

CMyListCtrl1::CMyListCtrl1()
{

}

bool CMyListCtrl1::Init()
{
	//组
	CreateSingleGroup(/*0, 0, _T("甲组")*/);

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
		| LVS_EX_COLUMNSNAPPOINTS | LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE
	/*| LVS_EX_GRIDLINES*/);
	
	//bool b = IsCommonControlsEnabled();
	EnableWindowTheme(m_hWnd, L"ListView", L"Explorer", NULL);

	//Disable the CToolTipCtrl of CListCtrl so it won't disturb the CWnd tooltip
	GetToolTips()->Activate(FALSE);
	EnableToolTips(TRUE);
	

	//SendMessage(WM_WINDOWPOSCHANGED, 0, 0);

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



//void CMyListCtrl1::OnLvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
//	// TODO: Add your control notification handler code here
//	const LVITEM& item = pDispInfo->item;
//
//	CT2A pszA(item.pszText);
//	//5个汉字或10个字母或组合
//	if(item.pszText && strlen(pszA) <= 10)
//		SetItemText(pDispInfo->item.iItem, 0, pDispInfo->item.pszText);
//
//	*pResult = 0;
//}







void CMyListCtrl1::MeasureItem(/*int nIDCtl, */LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: Add your message handler code here and/or call default
	/*当 combo box , list box, list-view,menu item 创建时，发送给owner window
	*/
	lpMeasureItemStruct->itemHeight = 70;

	//__super::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}


LRESULT CMyListCtrl1::CreateSingleGroup(/*int nIndex,
	int nGroupId, CString strHeader*/)
{
	SetRedraw(FALSE);

	//列
	CHeaderCtrl* pHeader = GetHeaderCtrl();
	LVCOLUMN lvCol;
	lvCol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM | LVCF_MINWIDTH;
	//lvCol.fmt = LVCFMT_LEFT;
	int colWidths[] = { 50,50,50,50,50,160 };
	int colWidthSum = 0, colWidth = 0;
	//int len = sizeof(g_strCols) / sizeof(g_strCols[0]);
	int len = m_vecColsName.size();
	for (int i = 0; i < len; ++i) {
		CString& str = m_vecColsName[i];

		lvCol.pszText = str.GetBuffer();
		lvCol.cchTextMax = str.GetLength();
		lvCol.iSubItem = i;
		colWidth = 2 * GetStringWidth(str);
		lvCol.cxMin = colWidth;
		lvCol.cx = colWidths[i];
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
	//_T("姓名"),_T("年龄"), _T("性别"), _T("爱好"), _T("工作进度"),_T("链接")
	std::vector<std::vector<CString>> vec = {
		{ _T("a"),_T("43"), _T("男"), _T("篮球"), _T("90%"),_T("http://www.stanford.edu") },
		{ _T("b"),_T("12"), _T("男"), _T("足球"), _T("90%"), _T("http://www.yahoo.com") },
		{ _T("c"),_T("3"), _T("女"), _T("篮球"), _T("90%"), _T("mailto:john@ficticious.edu") },
		{ _T("d"),_T("4"), _T("女"), _T("篮球"), _T("30%"), _T("Unpublished") },
		{ _T("e"),_T("56"), _T("男"), _T("篮球"), _T("90%"), _T("mailto:cassio@some_email.org") },
		{ _T("f"),_T("12"), _T("女"), _T("羽毛球"), _T("20%"), _T("Unpublished") },
		{ _T("g"),_T("32"), _T("女"), _T("保龄球"), _T("90%"), _T("Unpublished") },
		{ _T("h"),_T("22"), _T("男"), _T("高尔夫球"), _T("90%"), _T("Unpublished") },
		{ _T("i"),_T("25"), _T("男"), _T("篮球"), _T("90%"), _T("http://www.baidu.com") },
		{ _T("j"),_T("26"), _T("男"), _T("篮球"), _T("90%"), _T("http://www.symantec.com") }
	};
	const int nItemCnt = vec.size();
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;

	CString strLink;
	for (int i = 0; i < nItemCnt; ++i) {
		CString& str0 = vec[i][0];
		InsertItem(i, str0);

		for (int j = 1; j < len; ++j) {
			CString& str = vec[i][j];

			SetItemText(i, j, str);
			if (j == len - 1 && str != _T("Unpublished")) {//链接列
				auto& li = std::make_shared<CLinkItem>(str);
				strLink.Format(_T("%d-%d"), i, j);
				m_linkMap[strLink] = li;
				
				//lvItem.mask |= LVIF_PARAM;
				//lvItem.lParam = i * j/*(LPARAM)li.get()*/;
				//SetItem(&lvItem);
			}
		}
	}
	
	CString strHeader[] = { _T("甲组"),_T("乙组") ,_T("丙组") };
	int nGroupId = 0;
	EnableGroupView(TRUE);

	LVGROUP lg = { 0 };
	lg.cbSize = sizeof(lg);
	lg.mask = LVGF_GROUPID | LVGF_HEADER | LVGF_STATE;
	lg.iGroupId = nGroupId;
	lg.pszHeader = strHeader[0].GetBuffer();
	lg.cchHeader = strHeader[0].GetLength();
	//CString strFooter = _T("Group Footer");//只能一行
	//lg.pszFooter = strFooter.GetBuffer();
	//lg.cchFooter = strFooter.GetLength();
	//lg.uAlign = LVGA_FOOTER_CENTER;
	lg.state = LVGS_COLLAPSIBLE ;
	
	nGroupId = InsertGroup(0, &lg);//内部维护<索引,gid>
	if (-1 == nGroupId)
		return nGroupId;

	//绑定组：创建group就要绑定
	memset(&lvItem, 0, sizeof(LVITEM));
	lvItem.mask = LVIF_GROUPID;
	int cnt = nItemCnt / 4;//每组绑定多少个
	for (int nRow = /*nGroupId*cnt*/0; nRow < /*(nGroupId+1)*cnt*/nItemCnt; ++nRow)
	{
		lvItem.iItem = nRow;
		lvItem.iGroupId = nGroupId;
		SetItem(&lvItem);
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





INT_PTR CMyListCtrl1::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	// TODO: Add your specialized code here and/or call the base class

	int nRow, nCol;
	CellHitTest(point, nRow, nCol);//点击了哪行哪列

	if (-1 == nRow || -1 == nCol)
		return -1;

	//Get the client (area occupied by this control
	RECT rcClient;
	GetClientRect(&rcClient);

	//Fill in the TOOLINFO structure
	pTI->hwnd = m_hWnd;
	pTI->uId = (UINT)(nRow * 1000 + nCol);
	pTI->lpszText = LPSTR_TEXTCALLBACK;	// Send TTN_NEEDTEXT when tooltip should be shown
	pTI->rect = rcClient;

	return pTI->uId; // Must return a unique value for each cell (Marks a new tooltip)

	//return __super::OnToolHitTest(point, pTI);
}


void CMyListCtrl1::CellHitTest(const CPoint& pt, int& nRow, int& nCol) const
{
	nRow = -1;
	nCol = -1;

	LVHITTESTINFO lvhti = { 0 };
	lvhti.pt = pt;
	nRow = /*SubItemHitTest(&lvhti);*/ ListView_SubItemHitTest(m_hWnd, &lvhti);
	nCol = lvhti.iSubItem;
	if (!(lvhti.flags & LVHT_ONITEMLABEL))
		nRow = -1;
}



BOOL CMyListCtrl1::OnToolNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
{
	CPoint pt(GetMessagePos());
	ScreenToClient(&pt);

	int nRow, nCol;
	CellHitTest(pt, nRow, nCol);

	if (-1 == nRow || -1 == nCol) return FALSE;

	CString itemStr = GetItemText(nRow, nCol);
	auto it = g_mapTooltipStr.find(itemStr);
	CString tooltip = it == g_mapTooltipStr.end() ? _T("") : it->second;

	//if (nRow != -1 && nCol != -1)
	//	tooltip = GetItemText(nRow, nCol);	// Cell-ToolTip

	if (tooltip.IsEmpty())
		return FALSE;

	// Non-unicode applications can receive requests for tooltip-text in unicode
	TOOLTIPTEXT* pTTT = (TOOLTIPTEXT*)pNMHDR;
	int tipLen = tooltip.GetLength();
	CString bufStr;
	if (tipLen > 80) {
		//TCHAR* buf = new TCHAR[tooltip.GetLength()];
		pTTT->lpszText = bufStr.GetBuffer(tipLen);
		_tcscpy_s(pTTT->lpszText, tipLen + 1, tooltip.GetBuffer());
	}
	else {
		_tcscpy_s(pTTT->szText, 79, tooltip.GetBuffer());
	}
	bufStr.ReleaseBuffer();

	// If wanting to display a tooltip which is longer than 80 characters,
	// then one must allocate the needed text-buffer instead of using szText,
	// and point the TOOLTIPTEXT::lpszText to this text-buffer.
	// When doing this, then one is required to release this text-buffer again
	return TRUE;
}

//向导创建的 是LPNMCUSTOMDRAW结构，NMLVCUSTOMDRAW 比它信息更多
void CMyListCtrl1::OnCustomDraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
	*pResult = 0;
	std::shared_ptr<CLinkItem> pLink = nullptr;

	// TODO: Add your control notification handler code here
	switch (pLVCD->nmcd.dwDrawStage) {

	case CDDS_PREPAINT://开始绘制控件之前
		// If this is the beginning of the control's paint cycle, request
		// notifications for each item.
		*pResult = CDRF_NOTIFYITEMDRAW;//通知绘制item
		break;

	case CDDS_ITEMPREPAINT://item绘制之前
		//Ask for subitem notification.
		*pResult = CDRF_NOTIFYSUBITEMDRAW;//通知绘制subitem
		break;

	case CDDS_ITEMPREPAINT | CDDS_SUBITEM://CDDS_SUBITEM一定要组合
		if (pLVCD->iSubItem == 5) {
			CString strLink;
			strLink.Format(_T("%d-%d"), pLVCD->nmcd.dwItemSpec, pLVCD->iSubItem);
			pLink = m_linkMap[strLink];
			if (pLink) {
				pLVCD->clrText = pLink->m_bVisited ?
					pLink->m_pLinkProp.m_clrVisited : pLink->m_pLinkProp.m_clrLink;
				::SelectObject(pLVCD->nmcd.hdc, pLink->m_pLinkProp.m_fontLink);
			}	
		}
		pLVCD->clrTextBk = RGB(240, 247, 249);
		*pResult = CDRF_DODEFAULT;//剩下的交给控件自己绘制
		break;

	}

	if (pLVCD->nmcd.uItemState == CDIS_HOT && pLink) {
		//LVS_EX_ONECLICKACTIVATE 样式
		SetHotCursor(pLink->m_pLinkProp.m_hCursorHotSpot);
	}
}



void CMyListCtrl1::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	CString strLink;
	strLink.Format(_T("%d-%d"), pNMItemActivate->iItem, pNMItemActivate->iSubItem);
	auto& pLink = m_linkMap[strLink];

	if (pLink) {
		CString& url = pLink->m_strUrl;
		if (!url.IsEmpty()) {
			ShellExecute(m_hWnd, 0, url, 0, 0, SW_SHOWNORMAL);
			pLink->m_bVisited = TRUE;
		}
	}

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