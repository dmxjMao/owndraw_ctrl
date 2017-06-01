// MyTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "owndraw_ctrl.h"
#include "MyTreeCtrl.h"

namespace {
	//插入item
	void SetupInsertStruct(TVINSERTSTRUCT & ins, HTREEITEM hParent, HTREEITEM hAfter = TVI_LAST) {
		memset(&ins, 0, sizeof(ins));
		ins.item.mask = TVIF_TEXT;
		ins.item.pszText = _T("New Item");
		ins.hParent = hParent;
		ins.hInsertAfter = hAfter;
	}
}

// CMyTreeCtrl

IMPLEMENT_DYNAMIC(CMyTreeCtrl, CTreeCtrl)

CMyTreeCtrl::CMyTreeCtrl()
{
	//m_Keymap[VK_F2][false][false] = &CMyTreeCtrl::DoEditLabel;
	m_Keymap[VK_INSERT][true][false] = &CMyTreeCtrl::DoInsertChild;
	m_Keymap[VK_INSERT][false][true] = &CMyTreeCtrl::DoInsertRoot;
	m_Keymap[VK_INSERT][false][false] = &CMyTreeCtrl::DoInsertSibling;
	m_Keymap[VK_DELETE][false][false] = &CMyTreeCtrl::DoDeleteItem;
	//m_Keymap['S'][true][false] = &CMyTreeCtrl::DoSortCurrentLevel;
	//m_Keymap['S'][true][true] = &CMyTreeCtrl::DoSortCurrentLevelAndBelow;

	m_Commandmap[ID_ADD_ROOT] = &CMyTreeCtrl::DoInsertRoot;
	m_Commandmap[ID_ADD_SIBLING] = &CMyTreeCtrl::DoInsertSibling;
	m_Commandmap[ID_ADD_CHILD] = &CMyTreeCtrl::DoInsertChild;
}

CMyTreeCtrl::~CMyTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyTreeCtrl, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CMyTreeCtrl::OnNMRClick)
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, &CMyTreeCtrl::OnTvnEndlabeledit)
	ON_COMMAND_RANGE(ID_ADD_SIBLING, ID_MAX_CMD - 1, &CMyTreeCtrl::OnContextCmd)
END_MESSAGE_MAP()



// CMyTreeCtrl message handlers
void CMyTreeCtrl::OnContextCmd(UINT id) {
	HTREEITEM hCur = GetSelectedItem();

	method fnc = m_Commandmap[id];
	if (fnc) {
		(this->*fnc)(hCur);
		return;
	}

	//// unknown command in context menu
	//ASSERT(false);
}


bool CMyTreeCtrl::Init()
{
	HTREEITEM item;
	item = InsertItem(_T("root"));
	InsertItem(_T("item1"), item);
	InsertItem(_T("item1"), item);
	
	HTREEITEM item2;
	item2 = InsertItem(_T("item1"), item);
	InsertItem(_T("item1_sub1"), item2);

	//Expand(item, TVE_EXPAND);
	ExpandItem();

	return true;
}

void CMyTreeCtrl::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0, /*TVS_CHECKBOXES | */TVS_HASBUTTONS | TVS_TRACKSELECT
	| TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS | TVS_EDITLABELS);

	CTreeCtrl::PreSubclassWindow();
}



void CMyTreeCtrl::ExpandItem(HTREEITEM hti, UINT nCode)
{
	bool bOk = true;

	bOk = Expand(hti, nCode) != 0;

	if (bOk)
	{
		HTREEITEM htiChild = GetChildItem(hti);

		while (htiChild != NULL)
		{
			ExpandItem(htiChild, nCode);//递归

			htiChild = GetNextSiblingItem(htiChild);
		}
	}
}

void CMyTreeCtrl::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	
	CPoint ptScreen;
	GetCursorPos(&ptScreen);
	CPoint pt(ptScreen);
	ScreenToClient(&pt);
	
	UINT flags;
	HTREEITEM hitem = HitTest(pt, &flags);
	bool bOnItem = false;
	if (hitem && (flags & TVHT_ONITEM)) {
		bOnItem = true;
		SelectItem(hitem);
	}

	//构造右键菜单
	CMenu add;
	add.CreatePopupMenu();
	if (bOnItem) {
		add.AppendMenu(MF_STRING, ID_ADD_SIBLING, _T("New Sibling\tINS"));
		add.AppendMenu(MF_STRING, ID_ADD_CHILD, _T("New Child\tCtrl+INS"));
	}
	add.AppendMenu(MF_STRING, ID_ADD_ROOT, _T("New Root\tShift+INS"));

	CMenu menu;//右键菜单
	menu.CreatePopupMenu();
	//if (bOnItem) {
	//	menu.AppendMenu(MF_STRING, ID_RENAME, _T("Rename\tF2"));
	//	menu.AppendMenu(MF_STRING, ID_DELETE, _T("Delete\tDel"));
	//}
	menu.AppendMenu(MF_POPUP, (UINT)add.GetSafeHmenu(), _T("Add"));
	menu.AppendMenu(MF_STRING, ID_SELECT_ALL, _T("Select All"));

	menu.TrackPopupMenu(TPM_LEFTALIGN, ptScreen.x, ptScreen.y, this); //屏幕坐标

	*pResult = 0;
}


void CMyTreeCtrl::OnTvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	// TODO: Add your control notification handler code here
	TVITEM& item = pTVDispInfo->item;
	if (GetRootItem() == item.hItem)
		return;

	if (item.pszText) {
		SetItem(&item);
	}

	*pResult = 0;
}



bool CMyTreeCtrl::DoInsertRoot(HTREEITEM hItem) {
	TVINSERTSTRUCT ins;
	SetupInsertStruct(ins, TVI_ROOT, hItem);
	return NewItem(ins);
}

bool CMyTreeCtrl::DoInsertSibling(HTREEITEM hItem)
{
	TVINSERTSTRUCT ins;
	SetupInsertStruct(ins, GetParentItem(hItem), hItem);
	return NewItem(ins);
}

bool CMyTreeCtrl::DoInsertChild(HTREEITEM hItem)
{
	TVINSERTSTRUCT ins;
	SetupInsertStruct(ins, hItem, hItem);
	return NewItem(ins);
}

bool CMyTreeCtrl::DoDeleteItem(HTREEITEM hItem)
{
	return hItem ? (DeleteItem(hItem) != FALSE) : false;
}

bool CMyTreeCtrl::NewItem(TVINSERTSTRUCT & ins) {

	//if (!CanInsertItem(ins.hParent))
	//	return false;

	HTREEITEM hItem = InsertItem(&ins);
	if (hItem) {
		SelectItem(hItem);
		EditLabel(hItem);
	}
	return hItem != 0;
}

BOOL CMyTreeCtrl::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
		if (HandleKeyDown(pMsg->wParam, pMsg->lParam)) {
			return TRUE;
		}
		break;
	default:
		break;
	}

	return CTreeCtrl::PreTranslateMessage(pMsg);
}


bool CMyTreeCtrl::HandleKeyDown(WPARAM wParam, LPARAM lParam)
{
	//GetKeyState 返回SHORT ，高位1代表按下，否则没按下；低位1代表触发（指示灯亮）
	bool bCtrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
	bool bShift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
	HTREEITEM hCur = GetSelectedItem();

	if (GetEditControl() == 0) {
		method fnc = m_Keymap[int(wParam)][bCtrl][bShift];
		if (fnc)
			return (this->*fnc)(hCur);
	}

	switch (int(wParam)) {
	//case VK_ESCAPE:
	//	if (m_pDragData) {
	//		DragStop();
	//		return true;
	//	}
		/*FALLTHRU*/

	case VK_RETURN:
		if (GetEditControl()) {//编辑状态
			GetEditControl()->SendMessage(WM_KEYDOWN, wParam, lParam);
			return true;
		}
		break;

	default:
		break;
	}

	return false;
}