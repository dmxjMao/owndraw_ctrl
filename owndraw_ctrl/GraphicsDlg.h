#pragma once
#include "afxwin.h"


// CGraphicsDlg dialog
class CMyStatic2;

class CGraphicsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGraphicsDlg)
	DECLARE_MESSAGE_MAP()

public:
	CGraphicsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGraphicsDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Graphics };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CMyStatic2* m_pstsNotice;

protected:
	CRect m_rcClient;
};
