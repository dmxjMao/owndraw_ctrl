#pragma once
#include "utility.h"

class CMyListCtrl1 : public CListCtrl, public CUICfg
{
	//方法
public:
	DECLARE_MESSAGE_MAP()

	CMyListCtrl1();
	bool Init();
protected:
private:
	//属性
public:
protected:
private:
	virtual bool regex_callback(const boost::smatch& what);//ui正则回调
};