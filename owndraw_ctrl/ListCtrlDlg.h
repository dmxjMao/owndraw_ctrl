#pragma once



// CListCtrlDlg 对话框

class CMyListCtrl2;

class CListCtrlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CListCtrlDlg)

public:
	CListCtrlDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CListCtrlDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	std::shared_ptr<CMyListCtrl2> m_pList = 0;
public:
	virtual BOOL OnInitDialog();
};
