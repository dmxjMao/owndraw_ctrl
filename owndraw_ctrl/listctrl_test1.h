#pragma once
#include "utility.h"

class CMyListCtrl1 : public CListCtrl, public CUICfg
{
	//����
public:
	DECLARE_MESSAGE_MAP()

	CMyListCtrl1();
	bool Init();
protected:
private:
	//����
public:
protected:
private:
	virtual bool regex_callback(const boost::smatch& what);//ui����ص�
};