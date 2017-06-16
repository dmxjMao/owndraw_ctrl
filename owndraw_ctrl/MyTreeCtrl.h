#pragma once


// CMyTreeCtrl

class CMyTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CMyTreeCtrl)

public:
	CMyTreeCtrl();
	virtual ~CMyTreeCtrl();
	bool Init();


protected:
	DECLARE_MESSAGE_MAP()
	
	virtual bool	DoInsertRoot(HTREEITEM);
	virtual bool	DoInsertSibling(HTREEITEM);
	virtual bool	DoInsertChild(HTREEITEM);
	virtual bool	DoDeleteItem(HTREEITEM);

	//
	virtual bool	NewItem(TVINSERTSTRUCT & ins);
	virtual bool	HandleKeyDown(WPARAM wParam, LPARAM lParam);
private:
	void ExpandItem(HTREEITEM hti = TVI_ROOT, UINT nCode = TVE_EXPAND);

public:
protected:
	typedef bool (CMyTreeCtrl::*method)(HTREEITEM);
	typedef std::map<UINT, method>				cmdmap_t;
	cmdmap_t	m_Commandmap;//ÓÒ¼ü²Ëµ¥
	typedef std::map<bool, method>				shiftmap_t;
	typedef std::map<bool, shiftmap_t>			ctrlmap_t;
	typedef std::map<int, ctrlmap_t>			keymap_t;
	keymap_t	m_Keymap;//¿ì½Ý¼ü

private:

	virtual void PreSubclassWindow();
public:
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnContextCmd(UINT uID);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


//template<typename T>
//class ITCExpand : public T {
//public:
//	void ExpandItem(HTREEITEM hti = TVI_ROOT, UINT nCode = TVE_EXPAND);
//};
//
//template <typename T>
//void ITCExpand<T>::ExpandItem(HTREEITEM hti, UINT nCode)
//{
//	bool bOk = true;
//
//	bOk = Expand(hti, nCode) != 0;
//
//	if (bOk)
//	{
//		HTREEITEM htiChild = GetChildItem(hti);
//
//		while (htiChild != NULL)
//		{
//			ExpandItem(htiChild, nCode);//µÝ¹é
//
//			htiChild = GetNextSiblingItem(htiChild);
//		}
//	}
//}

