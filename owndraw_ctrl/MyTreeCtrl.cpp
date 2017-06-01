// MyTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "owndraw_ctrl.h"
#include "MyTreeCtrl.h"


// CMyTreeCtrl

IMPLEMENT_DYNAMIC(CMyTreeCtrl, CTreeCtrl)

CMyTreeCtrl::CMyTreeCtrl()
{

}

CMyTreeCtrl::~CMyTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyTreeCtrl, CTreeCtrl)
END_MESSAGE_MAP()



// CMyTreeCtrl message handlers


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
	| TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS);

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
			ExpandItem(htiChild, nCode);//ตÝน้

			htiChild = GetNextSiblingItem(htiChild);
		}
	}
}