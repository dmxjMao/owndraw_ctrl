#include "stdafx.h"
#include "text1.h"


COwnDrawCtrl_CStatic_Text1::COwnDrawCtrl_CStatic_Text1(const LOGFONT& lf)
{
	m_font.CreateFontIndirect(&lf);
}