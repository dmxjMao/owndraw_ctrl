#include "stdafx.h"
#include "btn_test1.h"
#include "ctl_property.h"


BEGIN_MESSAGE_MAP(CMyBitmapButton, CBitmapButton)
	
	ON_CONTROL_REFLECT(BN_CLICKED, &CMyBitmapButton::OnBnClicked)
END_MESSAGE_MAP()

CMyBitmapButton::CMyBitmapButton()
{
	//try {
	//	//ui��������
	//	m_uiregex.assign(
	//		"ctrlbgcolor\\s*[-:,./]\\s*(RGB[^@]+)"//�ؼ�����ɫ
	//		, boost::regex_constants::icase);
	//}
	//catch (boost::regex_error e) {

	//}
}


//bool CMyBitmapButton::Init()
//{
//	//��ʼ��Ĭ��UI
//	//m_colorCtrlBG = COLOR_LIGHT_BLUE;
//	return true;
//}


CSize CMyBitmapButton::GetBitmapSize()
{
	BITMAP bmInfo;
	m_bitmap.GetObject(sizeof(BITMAP), &bmInfo);
	return CSize(bmInfo.bmWidth, bmInfo.bmHeight);
}

bool CMyBitmapButton::regex_callback(const boost::smatch& what)
{
	//const int uicfgCnt = 1;//ui��������
	//					   //std::bitset<uicfgCnt> bts;

	//int i;//ƥ�������
	//for (i = 1; i < uicfgCnt; ++i) {
	//	if (what[i].matched)
	//		break;
	//}

	//switch (i) {
	//case 1:
	//{
	//	m_colorCtrlBG = GetRGBfromString(what[i].str());
	//	break;
	//}
	//}

	return true;
}


void CMyBitmapButton::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0, BS_OWNERDRAW);

	__super::PreSubclassWindow();
}


void CMyBitmapButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	//CRgn rgn;
	//CRect rct;
	//GetClientRect(&rct);
	//m_rgn.CreateEllipticRgnIndirect(&rct);//�ڰ�ť�����ڴ�����Բ����  
	//SetWindowRgn(m_rgn, true);//����Բ����Ӧ�õ���ť�ϣ�����WS_CHILD��Ч

	__super::DrawItem(lpDIS);
}


void CMyBitmapButton::OnBnClicked()
{
	// TODO: Add your control notification handler code here
	//HWND hDlg = (HWND)(*GetParent());//CWnd*  û��HWND������
	//::EndDialog(hDlg, IDCANCEL);
	GetParent()->PostMessage(WM_CLOSE);
	//����ȷ��������
}


