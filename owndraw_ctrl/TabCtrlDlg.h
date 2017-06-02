#pragma once

#include "MyTabCtrl.h"
// CTabCtrlDlg dialog

class CTabCtrlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTabCtrlDlg)

protected:
	CMyTabCtrl m_tabctrl;

public:
	CTabCtrlDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTabCtrlDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TabCtrl };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
