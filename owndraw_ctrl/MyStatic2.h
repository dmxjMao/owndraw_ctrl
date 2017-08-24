#pragma once


// CMyStatic2

class CMyStatic2 : public CStatic
{
	DECLARE_DYNAMIC(CMyStatic2)

public:
	CMyStatic2();
	virtual ~CMyStatic2();
	inline void SetNotice(const CString& msg) { m_strNotice = msg; }

protected:
	DECLARE_MESSAGE_MAP()
	CString m_strNotice;

public:
	afx_msg void OnPaint();
};


