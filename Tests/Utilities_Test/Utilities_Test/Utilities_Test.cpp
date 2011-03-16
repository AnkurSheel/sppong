// Utilities_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FileIO\ZipFile.hxx"
#include "Debugging\Logger.hxx"
#include <direct.h>

using namespace Utilities;
using namespace Base;


void CheckForMemoryLeaks() 
{
#ifdef	_DEBUG
	// Get Current flag
	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) ; 

	// Turn on leak-checking bit
	flag |= (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF) ; 

	// Set flag to the new value
	_CrtSetDbgFlag(flag) ; 
#endif	_DEBUG
}

void TestZipFile(cString & strPath);

void main(int argc, char * argv[])
{
	CheckForMemoryLeaks() ;
	ILogger::TheLogger()->StartConsoleWin(80,60, "Log.txt");
	TestZipFile(Base::cString("test.zip"));

	ILogger::TheLogger()->Destroy();
}

void MakePath(const char *pszPath)
{
	if (pszPath[0] == '\0')
		return;

	char buf[1000];
	const char *p = pszPath;

	 printf("MakePath(\"%s\")\n", pszPath);

	// Skip machine name in network paths like \\MyMachine\blah...
	if (p[0] == '\\' && p[1] == '\\')
		p = strchr(p+2, '\\');

	while (p != NULL && *p != '\0')
	{
		p = strchr(p, '\\');

		if (p)
		{
			memcpy(buf, pszPath, p - pszPath);
			buf[p - pszPath] = 0;
			p++;
		}
		else
			strcpy(buf, pszPath);

		if (buf[0] != '\0' && strcmp(buf, ".") && strcmp(buf, ".."))
		{
			//      printf("  Making path: \"%s\"\n", buf);
			_mkdir(buf);
		}
	}
}

void TestZipFile(cString & strPath)
{
	IZipFile * pZip = IZipFile::CreateZipFile();;

	if(pZip)
	{
		if (!pZip->Init(strPath))
			printf("Bad Zip file: \"%s\"\n",strPath.GetData());
		else
		{
			for (int i = 0; i < pZip->GetNumFiles(); i++)
			{
				int len = pZip->GetFileLen(i);
				cString strFileName;

				strFileName = pZip->GetFilename(i);

				printf("File \"%s\" (%d bytes): ", strFileName.GetData(), len);

				char *pData = new char[len];
				if (!pData)
					printf("OUT OF MEMORY\n");
				else if (true == pZip->ReadFile(i, pData))
				{
					printf("OK\n");
					cString dpath(100, "Data\\Test\\%s", strFileName.GetData());

					char *p = strrchr(const_cast<char *>(dpath.GetData()), '\\');
					if (p)
					{
						*p = '\0';
						MakePath(dpath.GetData());
						*p = '\\';
					}
					FILE *fo = fopen(dpath.GetData(), "wb");
					if (fo)
					{
						fwrite(pData, len, 1, fo);
						fclose(fo);
					}
				}
				else
					printf("ERROR\n");
				delete[] pData;
			}
			pZip->End();
			SAFE_DELETE(pZip);
		}
	}
	else
	{
		printf("Could Not Create Zipfile object\n");
	}
}

