#pragma once

using std::string;
using std::vector;

//修改
struct CListCtrl_DataRecord
{
	CListCtrl_DataRecord()
	{}

	CListCtrl_DataRecord(const string& city, const string& state, const string& country)
		:m_City(city)
		, m_State(state)
		, m_Country(country)
	{}

	string	m_City;
	string	m_State;
	string	m_Country;

	const string& GetCellText(int col, bool title) const
	{
		switch (col)
		{
		case 0: { static string title0("City"); return title ? title0 : m_City; }
		case 1: { static string title1("State"); return title ? title1 : m_State; }
		case 2: { static string title2("Country"); return title ? title2 : m_Country; }
		default: { static string emptyStr; return emptyStr; }
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
		m_Records.emplace_back("Copenhagen", "Sjaelland", "Denmark");
		m_Records.emplace_back("Aarhus", "Jutland", "Denmark");
		m_Records.emplace_back("Odense", "Fyn", "Denmark");
		m_Records.emplace_back("Malmoe", "Skaane", "Sweeden");
	}

	const string& GetCellText(size_t lookupId, int col) const
	{
		if (lookupId >= m_Records.size())
		{
			static const string oob("Out of Bound");
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
	inline const string& GetColTitle(int col) const { return CListCtrl_DataRecord().GetCellText(col, true); }

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