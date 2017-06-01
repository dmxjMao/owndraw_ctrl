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

private:
	void ExpandItem(HTREEITEM hti = TVI_ROOT, UINT nCode = TVE_EXPAND);

public:
protected:
private:

	virtual void PreSubclassWindow();
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
//			ExpandItem(htiChild, nCode);//ตÝน้
//
//			htiChild = GetNextSiblingItem(htiChild);
//		}
//	}
//}

