
// owndraw_ctrlDlg.h : header file
//

#pragma once
#include "afxwin.h"
//#include <memory>
#include "sts_test1.h"
//#include "btn_test1.h"

class COwnDrawCtrl_CStatic_Text1;

// Cowndraw_ctrlDlg dialog
class Cowndraw_ctrlDlg : public CDialogEx
{
// Construction
public:
	Cowndraw_ctrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OWNDRAW_CTRL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	bool Init();


// Implementation
protected:
	HICON m_hIcon;

	LONG				DLG_CLIENT_X;//当前客户区大小
	LONG				DLG_CLIENT_Y;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	//自定义
private:
	//绘制主界面
	void DrawTheMainDlg(/*CConfig* 配置信息*/);
public:

protected:
	CMyStatic1			m_static1;
	CMyBitmapButton		m_test1;
	

public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
};
