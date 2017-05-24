#include "stdafx.h"
#include "resource.h"
#include "listctrl_test1.h"
//#include <array>
#include <vector>


BEGIN_MESSAGE_MAP(CMyListCtrl1, CListCtrl)
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, &CMyListCtrl1::OnLvnEndlabeledit)
	ON_WM_MEASUREITEM_REFLECT()
	
	ON_NOTIFY(HDN_TRACKW, 0, &CMyListCtrl1::OnHdnTrack)
END_MESSAGE_MAP()

CMyListCtrl1::CMyListCtrl1()
{

}

bool CMyListCtrl1::Init()
{
	//��
	CreateSingleGroup(0, 0, _T("����"));

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
	SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER | LVS_EX_HEADERDRAGDROP
		| LVS_EX_COLUMNSNAPPOINTS);
	
	bool b = IsCommonControlsEnabled();


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


LRESULT CMyListCtrl1::CreateSingleGroup(int nIndex,
	int nGroupId, CString strHeader)
{
	SetRedraw(FALSE);

	//��
	CHeaderCtrl* pHeader = GetHeaderCtrl();
	CString strCols[] = { _T("����"),_T("����"), _T("�Ա�"), _T("����"), _T("��������") };
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
		lvCol.cx = lvCol.cxMin = colWidth;
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
	//_T("����"),_T("����"), _T("�Ա�"), _T("����"), _T("��������")
	std::vector<std::vector<CString>> vec = {
		{ _T("a"),_T("43"), _T("��"), _T("����"), _T("90%") },
		{ _T("b"),_T("12"), _T("��"), _T("����"), _T("90%") },
		{ _T("c"),_T("3"), _T("Ů"), _T("����"), _T("90%") },
		{ _T("d"),_T("4"), _T("Ů"), _T("����"), _T("30%") },
		{ _T("e"),_T("56"), _T("��"), _T("����"), _T("90%") },
		{ _T("f"),_T("12"), _T("Ů"), _T("��ë��"), _T("20%") },
		{ _T("g"),_T("32"), _T("Ů"), _T("������"), _T("90%") },
		{ _T("h"),_T("22"), _T("��"), _T("�߶�����"), _T("90%") },
		{ _T("i"),_T("25"), _T("��"), _T("����"), _T("90%") },
		{ _T("j"),_T("26"), _T("��"), _T("����"), _T("90%") }
	};
	const int nItemCnt = vec.size();
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;

	for (int i = 0; i < nItemCnt; ++i) {
		CString& str0 = vec[i][0];
		InsertItem(i, str0);

		for (int j = 1; j < len; ++j) {
			CString& str = vec[i][j];
			SetItemText(i, j, str);
		}
	}
	

	EnableGroupView(TRUE);

	LVGROUP lg = { 0 };
	lg.cbSize = sizeof(lg);
	lg.mask = LVGF_GROUPID | LVGF_HEADER | LVGF_STATE | LVGF_FOOTER | LVGF_ALIGN;
	lg.iGroupId = nGroupId;
	lg.pszHeader = strHeader.GetBuffer();
	lg.cchHeader = strHeader.GetLength();
	CString strFooter = _T("Group Footer");//ֻ��һ��
	lg.pszFooter = strFooter.GetBuffer();
	lg.cchFooter = strFooter.GetLength();
	lg.uAlign = LVGA_FOOTER_CENTER;
	lg.state = LVGS_COLLAPSIBLE ;
	
	nGroupId = InsertGroup(nIndex, &lg);//�ڲ�ά��<����,gid>
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



