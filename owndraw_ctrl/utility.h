#pragma once

using std::string;
using std::vector;

//修改
struct CListCtrl_DataRecord
{
	CListCtrl_DataRecord()
	{}

	CListCtrl_DataRecord(const CString& city, const CString& state, const CString& country)
		:m_City(city)
		, m_State(state)
		, m_Country(country)
	{}

	CString	m_City;
	CString	m_State;
	CString	m_Country;

	const CString& GetCellText(int col, bool title) const
	{
		switch (col)
		{
		case 0: { static CString title0("City"); return title ? title0 : m_City; }
		case 1: { static CString title1("State"); return title ? title1 : m_State; }
		case 2: { static CString title2("Country"); return title ? title2 : m_Country; }
		default: { static CString emptyStr; return emptyStr; }
		}
	}

	int  GetColCount() const { return 3; }
};


class CListCtrl_DataModel
{
	vector<CListCtrl_DataRecord> m_Records;

public:
	CListCtrl_DataModel()
	{
		InitDataModel();
	}

	void InitDataModel()
	{
		m_Records.clear();
		m_Records.emplace_back(_T("Copenhagen"), _T("Sjaelland"), _T("Denmark"));
		m_Records.emplace_back(_T("Aarhus"), _T("Jutland"), _T("Denmark"));
		m_Records.emplace_back(_T("Odense"), _T("Fyn"), _T("Denmark"));
		m_Records.emplace_back(_T("Malmoe"), _T("Skaane"), _T("Sweeden"));
		m_Records.emplace_back(_T("ABC垃圾，可以丢掉了，可是我喜欢阿！白痴！"), 
			_T("啦啦啦啦啦啦啦啦啦啦啦"), _T("Sweeden"));
	}

	const CString& GetCellText(size_t lookupId, int col) const
	{
		if (lookupId >= m_Records.size())
		{
			static const CString oob("Out of Bound");
			return oob;
		}

		for (size_t rowId = 0; rowId < m_Records.size(); ++rowId)
		{
			if (rowId == lookupId)
				break;
		}
		
		return m_Records.at(lookupId).GetCellText(col, false);
	}

	inline size_t GetRowIds() const { return m_Records.size(); }
	inline int GetColCount() const { return CListCtrl_DataRecord().GetColCount(); }
	inline const CString& GetColTitle(int col) const { return CListCtrl_DataRecord().GetCellText(col, true); }

	inline vector<CListCtrl_DataRecord>& GetRecords() { return m_Records; }
};


COLORREF GetRGBfromString(const std::string& rgb);


class CUICfg {
public:
	//设置ui属性
	CUICfg& operator& (const std::string& s);

protected:

private:
	//ui正则回调
	virtual bool regex_callback(const boost::smatch& what) = 0;

public:
protected:
	std::shared_ptr<std::string>			m_uicfg;//ui配置
	boost::regex							m_uiregex;//ui正则

private:

};


bool IsCommonControlsEnabled();
LRESULT EnableWindowTheme(HWND hwnd, LPCWSTR classList, LPCWSTR subApp, LPCWSTR idlist);