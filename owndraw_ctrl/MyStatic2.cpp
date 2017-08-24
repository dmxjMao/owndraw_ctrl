// MyStatic2.cpp : implementation file
//

#include "stdafx.h"
#include "owndraw_ctrl.h"
#include "MyStatic2.h"


// CMyStatic2

IMPLEMENT_DYNAMIC(CMyStatic2, CStatic)

CMyStatic2::CMyStatic2()
{

}

CMyStatic2::~CMyStatic2()
{
}


BEGIN_MESSAGE_MAP(CMyStatic2, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CMyStatic2 message handlers




void CMyStatic2::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CStatic::OnPaint() for painting messages

	Graphics gh(dc.GetSafeHdc());
	//�ͻ����� & ��������
	CRect rc;
	GetClientRect(&rc);
	int x = rc.left, y = rc.top, w = rc.Width(), h = rc.Height();

	//��������
	FontFamily ff(_T("����"));
	Gdiplus::Font font(&ff, 12, FontStyleBold, UnitPixel);
	CString strTitle;
	GetWindowText(strTitle);
	REAL fontHeight = font.GetHeight(0.0f);//����߶�
	REAL fontWidth = font.GetSize() * strTitle.GetLength();
	//REAL font = font.GetSize(); //�������ص�

	//���򣺾��� + ����
	//���������ȡ������̫����
	REAL fY = fontHeight / 2; //���㲼������
	y += static_cast<int>(fY);

	Rect rcBorder(10, y, w - 20, h - 2 * y);
	//Region region(rc2);
	//region.Union()
	
	//·�������� + ����
	Gdiplus::GraphicsPath ghpath;
	ghpath.AddRectangle(rcBorder);
	ghpath.AddString(strTitle, strTitle.GetLength(),&ff, FontStyleBold,48,
		Rect(5,0, (int)fontWidth, (int)fontHeight),nullptr);
	Pen pen(Color(125, 0, 255, 0));
	gh.DrawPath(&pen, &ghpath);

	HICON hIcon = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	Bitmap bmpApp(hIcon);
	gh.DrawImage(&bmpApp, 10, 10);

}
