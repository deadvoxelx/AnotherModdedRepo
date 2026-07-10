#pragma once

using namespace std;

#if defined(__PS3__) || defined(__ORBIS__) || defined __PSVITA__
#define LOCALE_COUNT 21
#elif defined _XBOX_ONE
#define LOCALE_COUNT 19
#else
#define LOCALE_COUNT 11
#endif

class StringTable
{
private:
	bool isStatic;

	unordered_map<wstring, wstring> m_stringsMap;
	vector<wstring> m_stringsVec;

	byteArray src;

public:
	StringTable(void);
	StringTable(PBYTE pbData, DWORD dwSize);
	~StringTable(void);
	void ReloadStringTable();

	void getData(PBYTE *ppbData, UINT *pdwSize);

	LPCWSTR getString(const wstring &id);
	LPCWSTR getString(int id);
	void registerString(int id, const wstring &value);

private:
	void ProcessStringTableData(void);

};

