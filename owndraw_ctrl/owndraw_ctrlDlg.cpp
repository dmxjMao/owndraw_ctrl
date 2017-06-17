
// owndraw_ctrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "owndraw_ctrl.h"
#include "owndraw_ctrlDlg.h"
#include "afxdialogex.h"
#include "ctl_property.h"
#include "ctl_adjust.h"
#include "TabCtrlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_tbInt 100

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
	DDX_Control(pDX, IDC_STATIC_1, m_static1);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_TREE1, m_tree1);
}

BEGIN_MESSAGE_MAP(Cowndraw_ctrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BtnTabCtrl, &Cowndraw_ctrlDlg::OnBnClickedBtntabctrl)
	ON_NOTIFY_EX(TTN_GETDISPINFO, IDD_OWNDRAW_CTRL_DIALOG, &OnTTNGetDispInfo)
	//ON_COMMAND(ID_tbInt_Range, &Cowndraw_ctrlDlg::OnTbintRange)
END_MESSAGE_MAP()


//bool Cowndraw_ctrlDlg::Init()
//{
//	bool b = m_static1.Init()  
//		|| m_test1.Init();
//
//	return b;
//}

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
	//SetWindowPos(NULL, 0, 0, DLG_SIZE_CX, DLG_SIZE_CY, SWP_NOZORDER | SWP_NOMOVE);
	RECT rcClient;
	GetClientRect(&rcClient);
	DLG_CLIENT_X = rcClient.right - rcClient.left;
	DLG_CLIENT_Y  = rcClient.bottom - rcClient.top;

	//tooltip
	if (m_tip.Create(this, TTS_ALWAYSTIP | TTS_BALLOON)) {
		m_tip.AddTool(this, _T("This is a very long string.\nhello,world!"), &rcClient, IDD_OWNDRAW_CTRL_DIALOG);
		m_tip.SetMaxTipWidth(150);
		//CToolInfo ti;
		//m_tip.GetToolInfo(ti, this);
	}
	//toolbar
	int l, t;
	BOOL bRet = m_tb.Create(this, WS_CHILD | WS_VISIBLE | TBSTYLE_TOOLTIPS | TBSTYLE_TRANSPARENT, ID_tbInt);
	UINT btns[] = { IDM_intRange , IDM_intRegular, IDM_intFix };
	m_tb.SetButtons(btns, sizeof(btns) / sizeof(btns[0]));
	m_tb.CleanUpLockedImages();
	m_tb.LoadBitmap(IDB_tbInt_16px);

	m_tb.SetPaneStyle(m_tb.GetPaneStyle() &~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_ANY));
	//m_tb.SetOwner(this);
	//m_tb.SetRouteCommandsViaFrame(FALSE);

	//CMenu mu;
	//mu.LoadMenu(IDR_test);
	m_tbmu.CreatePopupMenu();
	m_tbmu.AppendMenu(MF_STRING, IDM_int1, _T("测试菜单1"));

	//int iImage = GetCmdMgr()->GetCmdImage(IDM_intRange);
	//构造一个菜单按钮,(UINT)-1的话，点击按钮就下拉
	CMFCToolBarMenuButton tbmu(IDM_intRange, m_tbmu.GetSafeHmenu(), -1);
	m_tb.ReplaceButton(IDM_intRange, tbmu);
	//CMFCToolBarMenuButton* pBtn = (CMFCToolBarMenuButton*)m_tb.GetButton(0);
	//pBtn->m_bText = FALSE;
	//pBtn->m_bImage = TRUE;
	//pBtn->SetImage(GetCmdMgr()->GetCmdImage(IDM_intRange));
	//pBtn->SetMessageWnd(this);
	//toolbar布局
	CRect rc;
	GetDlgItem(IDC_BtnTabCtrl)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	l = rc.left; t = rc.top + rc.Height() + 2;
	CSize sz = m_tb.CalcFixedLayout(FALSE, TRUE);
	m_tb.SetWindowPos(0, l, t, sz.cx, sz.cy, SWP_NOACTIVATE | SWP_NOZORDER);


	//布局控件
	LayoutMainDlg();


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


void Cowndraw_ctrlDlg::LayoutMainDlg(/*CConfig* 配置信息*/)
{	
	//控件布局
	/*标题*///SetCtrlLocAbsolute(IDC_STATIC_1, 0, 0, ID_MY_STATIC_WIDTH, ID_MY_STATIC_HEIGHT);
	/*cancel按钮*///SetCtrlLocRelativeDlg(IDCANCEL, RELATIVE_LOC::RIGHT_BOTTOM, 10, 10);
	/*ok按钮*///SetCtrlLocRelativeCtrl(IDOK, IDCANCEL, RELATIVE_LOC::LEFT_TOP, 10, 0);
	
	/*关闭按钮*/
	m_test1.AutoLoad(ID_MYCTRL_TEST1, this);
	SetCtrlLocRelativeDlg(ID_MYCTRL_TEST1, RELATIVE_LOC::LEFT_BOTTOM, 30, 30);

	/*listctrl*/
	//SetCtrlLocAbsolute(IDC_LIST1, 10, 100, DLG_CLIENT_X - 20, 250);

	//控件自定义属性
	m_static1 & "textpoint,15"  & "textpoint,13" & "textcolor-RGB(0,255,0)";
	//m_test1 & "ctrlbgcolor,RGB(49,113,170)";

	//控件默认ui属性，改为PreCreateWindow
	m_list1.Init();

	//树控件
	m_tree1.Init();	
}






void Cowndraw_ctrlDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	/*static CPoint PrePoint = CPoint(0, 0);
	if (MK_LBUTTON == nFlags)
	{
		if (point != PrePoint)
		{
			CPoint ptTemp = point - PrePoint;
			CRect rcWindow;
			GetWindowRect(&rcWindow);
			rcWindow.OffsetRect(ptTemp.x, ptTemp.y);
			MoveWindow(&rcWindow);
			return;
		}
	}
	PrePoint = point;*/
	CDialogEx::OnMouseMove(nFlags, point);
}


void Cowndraw_ctrlDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//SetCapture();

	CDialogEx::OnLButtonDown(nFlags, point);
}


void Cowndraw_ctrlDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//ReleaseCapture();

	CDialogEx::OnLButtonUp(nFlags, point);
}





BOOL Cowndraw_ctrlDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	//CRect rc;
	//GetClientRect(&rc);
	//pDC->FillSolidRect(&rc, RGB(123, 123, 123));
	//return TRUE;

	return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL Cowndraw_ctrlDlg::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialogEx::PreCreateWindow(cs);
}


void Cowndraw_ctrlDlg::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::PreSubclassWindow();
}


//template class ITCExpand<CMyTreeCtrl>;//控制实例化

void Cowndraw_ctrlDlg::OnBnClickedBtntabctrl()
{
	// TODO: Add your control notification handler code here
	CTabCtrlDlg dlg;
	dlg.DoModal();
}


BOOL Cowndraw_ctrlDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	m_tip.RelayEvent(pMsg);
	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL Cowndraw_ctrlDlg::OnTTNGetDispInfo(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTTDISPINFO pInfo = (LPNMTTDISPINFO)pNMHDR;
	m_tip.SetMaxTipWidth(150);
	_tcscpy_s(pInfo->szText, 79, _T("This is \n a very long text string that must be broken into several lines."));
	return TRUE;
}

//工具条响应
void Cowndraw_ctrlDlg::OnTbintRange()
{
	// TODO: Add your command handler code here
	AfxMessageBox(_T("hello"));
}
