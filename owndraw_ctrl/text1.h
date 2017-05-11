#pragma once


class COwnDrawCtrl_CStatic_Text1 : public CStatic
{
public:
	COwnDrawCtrl_CStatic_Text1(const LOGFONT& lf);
	COwnDrawCtrl_CStatic_Text1(){}

	inline void SetFont(const LOGFONT& lf) { m_font.CreateFontIndirect(&lf); }

protected:
	CFont				m_font;
};