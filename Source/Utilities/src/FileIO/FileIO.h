#pragma once

class cFileIO
{
public:
	bool OpenTry(const char * const strFileName);

private:
	FILE *			m_fStdOut;
	char			m_strFileName[MAX_PATH];
};
