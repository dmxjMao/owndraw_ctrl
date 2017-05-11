
// owndraw_ctrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "owndraw_ctrl.h"
#include "owndraw_ctrlDlg.h"
#include "afxdialogex.h"
#include "ctl_property.h"
#include "ctl_adjust.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cowndraw_ctrlDlg dialog



Cowndraw_ctrlDlg::Cowndraw_ctrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OWNDRAW_CTRL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cowndraw_ctrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cowndraw_ctrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// Cowndraw_ctrlDlg message handlers

BOOL Cowndraw_ctrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetWindowPos(NULL, 0, 0, 640, 480, SWP_NOZORDER | SWP_NOMOVE);
	DrawTheMainDlg();


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Cowndraw_ctrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Cowndraw_ctrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Cowndraw_ctrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cowndraw_ctrlDlg::DrawTheMainDlg(/*CConfig* 配置信息*/)
{

	//static
	m_static_1.Create(_T(""), WS_CHILD | WS_VISIBLE,
		CRect(0,0,0,0), this, ID_MY_STATIC_1);
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 20; lf.lfUnderline = TRUE;
	CFont* font = new CFont;
	font->CreateFontIndirect(&lf);
	m_static_1.SetFont(font);
	m_static_1.SetWindowText(_T("maoyinan"));
	m_static_1.SetWindowPos(0, 10, 10, 100, 50, SWP_NOZORDER);

	//button
	//GetDlgItem(IDCANCEL)->SetWindowPos(0, m_curSize.cx - 100, m_curSize.cy - 100, 100, 80, SWP_NOZORDER);
	//GetDlgItem(IDOK)->SetWindowPos(0, m_curSize.cx - 200, m_curSize.cy - 100, 100, 80, SWP_NOZORDER);
	//GetDlgItem(IDCANCEL)->MoveWindow(m_curSize.cx - 100, m_curSize.cy - 100, 100, 80);
	//GetDlgItem(IDOK)->MoveWindow(m_curSize.cx - 200, m_curSize.cy - 100, 100, 80);
	SET_CTL_LOC_ABSOLUTE(IDCANCEL, 1, m_curSize.cx - CANCEL_BTN_RIGHT_MARGIN - OK_BTN_WIDTH, m_curSize.cy - CANCEL_BTN_BOTTOM_MARGIN - CANCEL_BTN_HEIGHT, CANCEL_BTN_WIDTH, CANCEL_BTN_HEIGHT);
	SET_CTL_LOC_ABSOLUTE(IDOK, 1, m_curSize.cx - OK_AND_CANCEL_MARGIN - OK_BTN_WIDTH, m_curSize.cy - CANCEL_BTN_BOTTOM_MARGIN - OK_BTN_HEIGHT, OK_BTN_WIDTH, OK_BTN_HEIGHT);
	//SET_CTL_LOC_ABSOLUTE(IDOK, IDCANCEL, -OK_AND_CANCEL_MARGIN - OK_BTN_WIDTH, rc.top, OK_BTN_WIDTH, OK_BTN_HEIGHT)
	
	RECT rc; 
	GetDlgItem(IDCANCEL)->GetWindowRect(&rc); 
	ScreenToClient(&rc); 
	//if (b) {	
		RECT rc2; 
		GetDlgItem(IDOK)->GetClientRect(&rc2);//
		//ScreenToClient(&rc2);
		SET_CTL_LOC_ABSOLUTE(IDOK, 1, rc.left - OK_AND_CANCEL_MARGIN - rc2.right, rc.top, rc2.right, rc2.bottom);
	//}
	//else {		
	//	SET_CTL_LOC_ABSOLUTE(id, rc.left + offx, rc.top + offy, cx, cy); 
	//}
}


void Cowndraw_ctrlDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: Add your message handler code here and/or call default
	if (lpMMI->ptMinTrackSize.x <= 500) lpMMI->ptMinTrackSize.x = 500;
	if (lpMMI->ptMinTrackSize.y <= 300) lpMMI->ptMinTrackSize.y = 300;
	if (lpMMI->ptMaxTrackSize.x >= 640) lpMMI->ptMaxTrackSize.x = 640;
	if (lpMMI->ptMaxTrackSize.y >= 480) lpMMI->ptMaxTrackSize.y = 480;

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


void Cowndraw_ctrlDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_curSize.cx = cx; m_curSize.cy = cy;

	//适应控件布局

}
