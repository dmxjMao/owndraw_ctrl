#pragma once



// CListCtrlDlg �Ի���

class CMyListCtrl2;

class CListCtrlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CListCtrlDlg)

public:
	CListCtrlDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CListCtrlDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	std::shared_ptr<CMyListCtrl2> m_pList = 0;
public:
	virtual BOOL OnInitDialog();
};
