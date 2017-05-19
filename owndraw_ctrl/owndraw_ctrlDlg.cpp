
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
	DDX_Control(pDX, IDC_STATIC_1, m_static1);
}

BEGIN_MESSAGE_MAP(Cowndraw_ctrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_NCMOUSEMOVE()
END_MESSAGE_MAP()


bool Cowndraw_ctrlDlg::Init()
{
	bool b = m_static1.Init()  
		|| m_test1.Init();

	return b;
}

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
	SetWindowPos(NULL, 0, 0, DLG_SIZE_CX, DLG_SIZE_CY, SWP_NOZORDER | SWP_NOMOVE);
	RECT rcClient;
	GetClientRect(&rcClient);
	DLG_CLIENT_X = rcClient.right - rcClient.left;
	DLG_CLIENT_Y  = rcClient.bottom - rcClient.top;
	//ModifyStyle(WS_SIZEBOX,0);
	DrawTheMainDlg();//绘制主界面


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
	//控件默认ui属性
	if (!Init())
		return;
	
	//控件布局:控件在Create时就指定了ZOrder的顺序，先Create的控件ZOrder值最小（最先响应此控件）
	//如果调用了SetWindowPos，且第一个参数为NULL，也不指定SWP_NOZORDER属性，则系统会将此控件置顶，此时ZOrder值变为最小，最先响应。
	/*标题*/SetCtrlLocAbsolute(IDC_STATIC_1, 0, 0, ID_MY_STATIC_WIDTH, ID_MY_STATIC_HEIGHT);
	/*cancel按钮*/SetCtrlLocRelativeDlg(IDCANCEL, RELATIVE_LOC::RIGHT_BOTTOM, 10, 10);
	/*ok按钮*/SetCtrlLocRelativeCtrl(IDOK, IDCANCEL, RELATIVE_LOC::LEFT_TOP, 10, 0);
	
	/*关闭按钮*/
	m_test1.AutoLoad(ID_MYCTRL_TEST1, this);
	SetCtrlLocRelativeDlg(ID_MYCTRL_TEST1, RELATIVE_LOC::LEFT_BOTTOM, 30, 30);
	//m_test1.SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);//控件置顶，先响应消息
	//m_static1.SetWindowPos(&m_test1, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	//控件自定义属性
	m_static1 & "textpoint,15"  & "textpoint,13" & "textcolor-RGB(0,255,0)";
	//m_test1 & "ctrlbgcolor,RGB(49,113,170)";

	
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


void Cowndraw_ctrlDlg::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default


	CDialogEx::OnNcMouseMove(nHitTest, point);
}


