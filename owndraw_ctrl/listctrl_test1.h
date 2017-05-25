#pragma once
#include "utility.h"
#include <vector>

class CMyListCtrl1 : public CListCtrl, public CUICfg
{
	DECLARE_MESSAGE_MAP()
	friend int CALLBACK SortFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

public:
	CMyListCtrl1();
	bool Init();

	afx_msg void OnLvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult);

protected:
private:
	virtual bool regex_callback(const boost::smatch& what);//ui����ص�
	virtual void PreSubclassWindow();

	LRESULT	CreateGroup(int nIndex, int nGroupId, CString strHeader);





public:
	enum SORTTYPE {//����������
		STRING,//�ַ���
		INTEGER,//����
		PERCENTAGE//�ٷֱ�
	};


protected:
	CImageList				m_imgList;//32pxͼ��
	CImageList				m_imgListSmall;//16pxͼ��
	CImageList				m_imgListState;//stateͼ��
	CImageList				m_imgListGroup;//groupͼ��

private:
	int m_SortCol = -1;//��ǰѡ�����
	int m_preSortCol = -1;//֮ǰѡ�����
	bool m_Ascending = true;//����

	std::vector<CString>	m_vecColsName //����
		= { _T("����"),_T("����"), _T("�Ա�"), _T("����"), _T("��������") };
	std::vector<SORTTYPE>	m_vecSortType//����������
		= { STRING, INTEGER, STRING, STRING, PERCENTAGE };
	std::vector<CString>	m_vecGroupName
		= { _T("����"),_T("����"), _T("����"), _T("����") };

};