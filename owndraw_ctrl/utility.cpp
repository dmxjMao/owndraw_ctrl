#include "stdafx.h"
#include "utility.h"

boost::regex g_regexRGB("[0-9]+");//ƥ��rgb��ֵ

COLORREF GetRGBfromString(const std::string& rgb)
{
	int a[3] = { 0 };
	int i = 0;
	boost::sregex_token_iterator it(rgb.begin(), rgb.end(), g_regexRGB) , itend;
	for (; it != itend; ++it,++i) {
		a[i] = stoi(it->str());
	}

	return RGB(a[0], a[1], a[2]);
}


CUICfg& CUICfg::operator & (const std::string& s)
{

	if (!m_uicfg)
		m_uicfg = std::make_shared<std::string>();
	//�����ظ�����
	size_t pos = s.find_first_of("-:,./");
	std::string strCfgname = s.substr(0, pos);
	pos = m_uicfg->find(strCfgname);
	if (std::string::npos == pos)
		(*m_uicfg) += s + '@';
	else {
		size_t posEnd = m_uicfg->find_first_of('@', pos);
		m_uicfg->replace(pos, posEnd - pos, s);
	}

	boost::sregex_iterator it(m_uicfg->begin(), m_uicfg->end(), m_uiregex), itend;
	//��ÿһ��ƥ��������Ȼ�����ظ����ã����Ƕ���ui�������ִ�����Ӱ��Ч��
	//std::for_each(it, itend, &regex_callback);
	for (; it != itend; ++it) {
		regex_callback(*it);
	}

	return(*this);
}