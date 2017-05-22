#include "stdafx.h"
#include "listctrl_test1.h"


BEGIN_MESSAGE_MAP(CMyListCtrl1, CListCtrl)
END_MESSAGE_MAP()

CMyListCtrl1::CMyListCtrl1()
{

}


bool CMyListCtrl1::Init()
{
	return true;
}


bool CMyListCtrl1::regex_callback(const boost::smatch& what)
{
	return true;
}

BOOL CMyListCtrl1::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0, LVS_ICON);


	return __super::PreCreateWindow(cs);
}
