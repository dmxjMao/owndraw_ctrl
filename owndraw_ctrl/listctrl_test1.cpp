#include "stdafx.h"
#include "resource.h"
#include "listctrl_test1.h"
//#include <array>
#include <vector>
#include <map>

namespace {
	std::map<CString, CString> g_mapTooltipStr = {
		{ _T("����"),_T("�����˶���1891����������ղķ˹��ʷ��˹�����ġ�") },
		{ _T("Ů"),_T("Ů�ϣ���������Դ") },
		{ _T("����"),_T("�����С������һ�˶�������������ȫ�����������Ӱ�����ĵ��������˶���") },
		{ _T("��ë��"),_T("��ë����һ�����ڣ����ⶼ���Խ��е������˶���") },
		{ _T("������"),_T("�������ֳƵع�������ľ����Ϲ��������һ�������˶���") },
		{ _T("��"),_T("ë����") },
		{ _T("h"),_T("����һ����boss��") },
	};
}


BEGIN_MESSAGE_MAP(CMyListCtrl1, CListCtrl)
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, &CMyListCtrl1::OnLvnEndlabeledit)
	ON_WM_MEASUREITEM_REFLECT()
	
	ON_NOTIFY(HDN_TRACKW, 0, &CMyListCtrl1::OnHdnTrack)
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolNeedText)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CMyListCtrl1::OnCustomDraw)
	ON_NOTIFY_REFLECT(NM_CLICK, &CMyListCtrl1::OnNMClick)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CMyListCtrl1::OnNMRClick)
END_MESSAGE_MAP()

CMyListCtrl1::CMyListCtrl1()
{

}

bool CMyListCtrl1::Init()
{
	//��
	CreateSingleGroup(/*0, 0, _T("����")*/);

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
//		int iItem;//item����
//		int iSubItem;//report
//		UINT state;//�����ǣ����϶��������еȣ��ظ���
//		UINT stateMask;//��Щstate�ɼ���
//		LPWSTR pszText;
//		int cchTextMax;
//		int iImage;
//		LPARAM lParam;
//		int iIndent;//������image��Ϊ��λ
//#if (NTDDI_VERSION >= NTDDI_WINXP)
//		int iGroupId;
//		UINT cColumns; // ������tile view columns
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
	//5�����ֻ�10����ĸ�����
	if(item.pszText && strlen(pszA) <= 10)
		SetItemText(pDispInfo->item.iItem, 0, pDispInfo->item.pszText);

	*pResult = 0;
}







void CMyListCtrl1::MeasureItem(/*int nIDCtl, */LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: Add your message handler code here and/or call default
	/*�� combo box , list box, list-view,menu item ����ʱ�����͸�owner window
	*/
	lpMeasureItemStruct->itemHeight = 70;

	//__super::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}


LRESULT CMyListCtrl1::CreateSingleGroup(/*int nIndex,
	int nGroupId, CString strHeader*/)
{
	SetRedraw(FALSE);

	//��
	CHeaderCtrl* pHeader = GetHeaderCtrl();
	CString strCols[] = { _T("����"),_T("����"), _T("�Ա�"), _T("����"), _T("��������"), _T("����") };
	int colWidths[] = { 50,50,50,50,80,160 };
	LVCOLUMN lvCol;
	lvCol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM | LVCF_MINWIDTH;
	//lvCol.fmt = LVCFMT_LEFT;

	int colWidthSum = 0, colWidth = 0;
	int len = sizeof(strCols) / sizeof(strCols[0]);
	for (int i = 0; i < len; ++i) {
		CString& str = strCols[i];

		lvCol.pszText = str.GetBuffer();
		lvCol.cchTextMax = str.GetLength();
		lvCol.iSubItem = i;
		colWidth = 2 * GetStringWidth(str);
		lvCol.cxMin = colWidth;
		lvCol.cx = colWidths[i];
		colWidthSum += colWidth;

		InsertColumn(i, &lvCol);	
	}
	//�������һ�п��
	//RECT rc;
	//GetClientRect(&rc);
	//SetColumnWidth(len - 1, rc.right - colWidthSum + colWidth);
	//��ֹ���϶�
	//GetHeaderCtrl()->EnableWindow(FALSE);
	//���õ�һ������С��ͷ
	HDITEM hditem = { 0 };
	hditem.mask = HDI_FORMAT;
	pHeader->GetItem(0, &hditem);
	hditem.fmt |= HDF_SORTDOWN;
	pHeader->SetItem(0, &hditem);

	//item
	//_T("����"),_T("����"), _T("�Ա�"), _T("����"), _T("��������"),_T("����")
	std::vector<std::vector<CString>> vec = {
		{ _T("a"),_T("43"), _T("��"), _T("����"), _T("90%"),_T("http://www.stanford.edu") },
		{ _T("b"),_T("12"), _T("��"), _T("����"), _T("90%"), _T("http://www.yahoo.com") },
		{ _T("c"),_T("3"), _T("Ů"), _T("����"), _T("90%"), _T("mailto:john@ficticious.edu") },
		{ _T("d"),_T("4"), _T("Ů"), _T("����"), _T("30%"), _T("Unpublished") },
		{ _T("e"),_T("56"), _T("��"), _T("����"), _T("90%"), _T("mailto:cassio@some_email.org") },
		{ _T("f"),_T("12"), _T("Ů"), _T("��ë��"), _T("20%"), _T("Unpublished") },
		{ _T("g"),_T("32"), _T("Ů"), _T("������"), _T("90%"), _T("Unpublished") },
		{ _T("h"),_T("22"), _T("��"), _T("�߶�����"), _T("90%"), _T("Unpublished") },
		{ _T("i"),_T("25"), _T("��"), _T("����"), _T("90%"), _T("http://www.baidu.com") },
		{ _T("j"),_T("26"), _T("��"), _T("����"), _T("90%"), _T("http://www.symantec.com") }
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
			if (j == len - 1 && str != _T("Unpublished")) {//������
				auto& li = std::make_shared<CLinkItem>(str);
				strLink.Format(_T("%d-%d"), i, j);
				m_linkMap[strLink] = li;
				
				//lvItem.mask |= LVIF_PARAM;
				//lvItem.lParam = i * j/*(LPARAM)li.get()*/;
				//SetItem(&lvItem);
			}
		}
	}
	
	CString strHeader[] = { _T("����"),_T("����") ,_T("����") };
	int nGroupId = 0;
	EnableGroupView(TRUE);

	LVGROUP lg = { 0 };
	lg.cbSize = sizeof(lg);
	lg.mask = LVGF_GROUPID | LVGF_HEADER | LVGF_STATE | LVGF_FOOTER | LVGF_ALIGN;
	lg.iGroupId = nGroupId;
	lg.pszHeader = strHeader[0].GetBuffer();
	lg.cchHeader = strHeader[0].GetLength();
	CString strFooter = _T("Group Footer");//ֻ��һ��
	lg.pszFooter = strFooter.GetBuffer();
	lg.cchFooter = strFooter.GetLength();
	lg.uAlign = LVGA_FOOTER_CENTER;
	lg.state = LVGS_COLLAPSIBLE ;
	
	nGroupId = InsertGroup(0, &lg);//�ڲ�ά��<����,gid>
	if (-1 == nGroupId)
		return nGroupId;

	for (int nRow = 0; nRow < GetItemCount(); ++nRow)
	{
		LVITEM lvItem = { 0 };
		lvItem.mask = LVIF_GROUPID;
		lvItem.iItem = nRow;
		//lvItem.iSubItem = 0;
		lvItem.iGroupId = nGroupId;
		SetItem(&lvItem);
	}

	SetRedraw();

	return nGroupId;
}





void CMyListCtrl1::OnHdnTrack(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: Add your control notification handler code here
	HDITEM* p = phdr->pitem; //����û��ȫ����Ϣ��

	//UINT mask = p->mask;
	//mask = mask & HDI_TEXT; Ϊ0��

	//��ȡitem��Ϣ
	//HDITEM item;
	//item.mask = HDI_TEXT;
	//TCHAR buf[MAX_PATH] = { 0 };
	//item.pszText = buf;
	//item.cchTextMax = MAX_PATH;
	//CHeaderCtrl* pHead = GetHeaderCtrl();
	//pHead->GetItem(phdr->iItem, &item);
	//
	//int minColWidth = 2 * GetStringWidth(item.pszText);
	////int nowColWidth = GetColumnWidth(phdr->iItem);//��minColWidthһ����
	//int nowColWidth = p->cxy;
	//if (nowColWidth < minColWidth) {
	//	SetColumnWidth(phdr->iItem, minColWidth);
	//	pHead->EnableWindow(FALSE);
	//}

	*pResult = 0;
}





INT_PTR CMyListCtrl1::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	// TODO: Add your specialized code here and/or call the base class

	int nRow, nCol;
	CellHitTest(point, nRow, nCol);//�������������

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

//�򵼴����� ��LPNMCUSTOMDRAW�ṹ��NMLVCUSTOMDRAW ������Ϣ����
void CMyListCtrl1::OnCustomDraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
	*pResult = 0;
	std::shared_ptr<CLinkItem> pLink = nullptr;

	// TODO: Add your control notification handler code here
	switch (pLVCD->nmcd.dwDrawStage) {

	case CDDS_PREPAINT://��ʼ���ƿؼ�֮ǰ
		// If this is the beginning of the control's paint cycle, request
		// notifications for each item.
		*pResult = CDRF_NOTIFYITEMDRAW;//֪ͨ����item
		break;

	case CDDS_ITEMPREPAINT://item����֮ǰ
		//Ask for subitem notification.
		*pResult = CDRF_NOTIFYSUBITEMDRAW;//֪ͨ����subitem
		break;

	case CDDS_ITEMPREPAINT | CDDS_SUBITEM://CDDS_SUBITEMһ��Ҫ���
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
		*pResult = CDRF_DODEFAULT;//ʣ�µĽ����ؼ��Լ�����
		break;

	}

	if (pLVCD->nmcd.uItemState == CDIS_HOT && pLink) {
		//LVS_EX_ONECLICKACTIVATE ��ʽ
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




void CMyListCtrl1::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	//AfxMessageBox(_T("123"));
	//HDHITTESTINFO hit;
	//hit.pt = pNMItemActivate->ptAction;
	//GetHeaderCtrl()->SendMessage(HDM_HITTEST, 0, (LPARAM)&hit);

	*pResult = 0;
}
