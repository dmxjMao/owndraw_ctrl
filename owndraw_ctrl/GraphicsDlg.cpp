// GraphicsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "owndraw_ctrl.h"
#include "GraphicsDlg.h"
#include "afxdialogex.h"

#include "MyStatic2.h" //自绘组合框

// CGraphicsDlg dialog

IMPLEMENT_DYNAMIC(CGraphicsDlg, CDialogEx)

CGraphicsDlg::CGraphicsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Graphics, pParent)
{
	m_pstsNotice = new CMyStatic2; //公告栏
}

CGraphicsDlg::~CGraphicsDlg()
{
}

void CGraphicsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_sts_Notice, *m_pstsNotice);
}


BEGIN_MESSAGE_MAP(CGraphicsDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CGraphicsDlg message handlers


BOOL CGraphicsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	GetClientRect(&m_rcClient);
	int x = m_rcClient.left, y = m_rcClient.top;
	int w = m_rcClient.Width(), h = m_rcClient.Height();

	m_pstsNotice->SetWindowPos(0, x, y, w, h / 4, SWP_NOACTIVATE | SWP_NOZORDER);
	m_pstsNotice->SetWindowText(_T("公告栏"));
	m_pstsNotice->SetNotice(_T("尊敬的天跃屏幕墙用户您好"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CGraphicsDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
	Graphics myGraphics(dc.GetSafeHdc());
	Pen myPen(Color(255, 255, 0, 0), 1);

	

}


