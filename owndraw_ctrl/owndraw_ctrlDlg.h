
// owndraw_ctrlDlg.h : header file
//

#pragma once

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


// Implementation
protected:
	HICON m_hIcon;
	CStatic				m_static_1;

private:
	SIZE				m_curSize;//当前客户区大小

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
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
