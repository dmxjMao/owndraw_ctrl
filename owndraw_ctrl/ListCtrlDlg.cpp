// ListCtrlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "owndraw_ctrl.h"
#include "ListCtrlDlg.h"
#include "afxdialogex.h"
#include "MyListCtrl2.h"

namespace {
	using std::shared_ptr;
	using std::make_shared;
	using std::vector;
};

// CListCtrlDlg 对话框

IMPLEMENT_DYNAMIC(CListCtrlDlg, CDialogEx)

CListCtrlDlg::CListCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	m_pList = make_shared<CMyListCtrl2>();
}

CListCtrlDlg::~CListCtrlDlg()
{
}

void CListCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, *m_pList);
}


BEGIN_MESSAGE_MAP(CListCtrlDlg, CDialogEx)
END_MESSAGE_MAP()


// CListCtrlDlg 消息处理程序


BOOL CListCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rc;
	GetClientRect(&rc);
	int x, y, w, h;
	x = y = w = h = 0;
	DWORD flag = SWP_NOZORDER | SWP_NOACTIVATE;

	m_pList->SetWindowPos(0, 10, 10, rc.Width() - 20, rc.Height() - 20, flag);
	m_pList->LoadData();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


