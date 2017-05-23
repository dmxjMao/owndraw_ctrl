#include "stdafx.h"
#include "resource.h"
#include "listctrl_test1.h"


BEGIN_MESSAGE_MAP(CMyListCtrl1, CListCtrl)
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, &CMyListCtrl1::OnLvnEndlabeledit)
	ON_WM_MEASUREITEM_REFLECT()
END_MESSAGE_MAP()

CMyListCtrl1::CMyListCtrl1()
{

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

	int nImgCnt = m_imgList.GetImageCount();
	for (int i = 0; i < nImgCnt; ++i) {
		//InsertItem(i, _T("animal"), i);

	}

	RECT rc;
	GetItemRect(0, &rc, LVIR_LABEL);

	CFont* pf = GetFont();
	LOGFONT lf;
	pf->GetLogFont(&lf);
	lf.lfHeight = lf.lfHeight;
	//LVTILEINFO tileInfo;
	//GetTileInfo(&tileInfo);

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
