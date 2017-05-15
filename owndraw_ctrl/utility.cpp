#include "stdafx.h"
#include "utility.h"

boost::regex g_regexRGB("[0-9]+");//Æ¥ÅärgbÊıÖµ

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