// ListCtrlDlg.cpp : ʵ���ļ�
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

// CListCtrlDlg �Ի���

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


// CListCtrlDlg ��Ϣ�������


BOOL CListCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rc;
	GetClientRect(&rc);
	int x, y, w, h;
	x = y = w = h = 0;
	DWORD flag = SWP_NOZORDER | SWP_NOACTIVATE;

	m_pList->SetWindowPos(0, 10, 10, rc.Width() - 20, rc.Height() - 20, flag);
	m_pList->LoadData();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


