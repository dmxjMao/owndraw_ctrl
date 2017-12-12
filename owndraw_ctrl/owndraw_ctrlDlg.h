
// owndraw_ctrlDlg.h : header file
//

#pragma once
#include "afxwin.h"
//#include <memory>
#include "sts_test1.h"
#include "btn_test1.h"
#include "listctrl_test1.h"
#include "MyTreeCtrl.h"


class CMyListCtrl2;

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
	//bool Init();


// Implementation
protected:
	HICON m_hIcon;
	CToolTipCtrl m_tip;
	CMFCToolBar m_tb;
	CMenu m_tbmu;

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
	void LayoutMainDlg(/*CConfig* 配置信息*/);
public:

protected:
	CMyStatic1			m_static1;
	CMyBitmapButton		m_test1;
	CMyListCtrl1		m_list1;
	//ITCExpand<CMyTreeCtrl>			m_tree1;
	CMyTreeCtrl			m_tree1;
	CMyStatic1 m_sts2;
	std::shared_ptr<CMyListCtrl2> m_list2 = 0;

public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
	afx_msg void OnBnClickedBtntabctrl();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg BOOL OnTTNGetDispInfo(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTbintRange();
	afx_msg void OnBnClickedbtnGraphics();
};
