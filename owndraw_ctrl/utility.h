#pragma once
#include <string>
#include <memory>

COLORREF GetRGBfromString(const std::string& rgb);


class CUICfg {
public:
	//设置ui属性
	virtual CUICfg& operator& (const std::string& s) = 0;

protected:

private:
	//ui正则回调
	virtual bool regex_callback(const boost::smatch& what) = 0;

public:
protected:
	std::shared_ptr<std::string>			m_uicfg;//ui配置
private:

};