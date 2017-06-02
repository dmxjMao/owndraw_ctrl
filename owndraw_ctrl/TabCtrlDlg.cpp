// TabCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "owndraw_ctrl.h"
#include "TabCtrlDlg.h"
#include "afxdialogex.h"


// CTabCtrlDlg dialog

IMPLEMENT_DYNAMIC(CTabCtrlDlg, CDialogEx)

CTabCtrlDlg::CTabCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TabCtrl, pParent)
{

}

CTabCtrlDlg::~CTabCtrlDlg()
{
}

void CTabCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_TAB1, m_tabctrl);
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabCtrlDlg, CDialogEx)
END_MESSAGE_MAP()


// CTabCtrlDlg message handlers


BOOL CTabCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	static CString titles[] = { _T("t1"), _T("t2") ,_T("t3") };
	int len = sizeof(titles) / sizeof(titles[0]);
	for (decltype(len) i = 0; i < len; ++i) {
		m_tabctrl.InsertItem(i, titles[i]);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
