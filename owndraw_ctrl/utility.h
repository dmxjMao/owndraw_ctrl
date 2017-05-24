#pragma once
#include <string>
#include <memory>

COLORREF GetRGBfromString(const std::string& rgb);


class CUICfg {
public:
	//����ui����
	CUICfg& operator& (const std::string& s);

protected:

private:
	//ui����ص�
	virtual bool regex_callback(const boost::smatch& what) = 0;

public:
protected:
	std::shared_ptr<std::string>			m_uicfg;//ui����
	boost::regex							m_uiregex;//ui����

private:

};


bool IsCommonControlsEnabled();
