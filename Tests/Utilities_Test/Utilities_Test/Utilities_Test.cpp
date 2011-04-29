// Utilities_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ZipFile.hxx"
#include "Logger.hxx"
#include "ResCache.hxx"
#include "RandomGenerator.hxx"
#include <direct.h>
#include <vector>
#include <memory>

using namespace Utilities;
using namespace Base;
using namespace std;
using namespace std::tr1;

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

void TestZipFile();
void TestResourceCache();
void TestRandomGenerator();

void main(int argc, char * argv[])
{
	CheckForMemoryLeaks() ;
	ILogger::TheLogger()->StartConsoleWin(80,60, "Log.txt");

	printf("Testing Zip File\n");
	TestZipFile();

	printf("\n\n\nTesting Resource Cache\n");
	TestResourceCache();

	printf("\n\n\nTesting Random Generator\n");
	TestRandomGenerator();


	ILogger::TheLogger()->Destroy();

	system("pause");
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

void TestZipFile()
{
	IZipFile * pZip = IZipFile::CreateZipFile();;

	
	if(pZip)
	{
		char szPath[MAX_PATH_WIDTH];
		printf("Enter Zip file path : ");
		gets(szPath);
		if (!pZip->Init(szPath))
		{
			printf("Bad Zip file: \"%s\"\n",szPath);
		}
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
		}
	}
	else
	{
		printf("Could Not Create Zipfile object\n");
	}
	SAFE_DELETE(pZip);
}


void TestResourceCache()
{
	char szPath[MAX_PATH_WIDTH];
	printf("Enter Zip file path : ");
	gets(szPath);

	IResCache * pResCache =  IResCache::CreateResourceCache(1, szPath);
	if(!pResCache->Init())
	{
		printf("Bad Zip file for Resource Cache: \"%s\"\n",szPath);
	}
	else
	{
		IZipFile * pZip = IZipFile::CreateZipFile();;

		vector<cString> strFileNames;
		if(pZip)
		{
			if (!pZip->Init(szPath))
				printf("Bad Zip file: \"%s\"\n",szPath);
			else
			{
				for (int i = 0; i < pZip->GetNumFiles(); i++)
				{
					int len = pZip->GetFileLen(i);
					if(len > 0)
					{
						strFileNames.push_back(pZip->GetFilename(i));
					}
				}
				pZip->End();
				SAFE_DELETE(pZip);
			}
		}
		vector<cString>::iterator iter;
		for (iter = strFileNames.begin(); iter != strFileNames.end(); iter++)
		{
			IResource * pResource = IResource::CreateResource(*iter);
			shared_ptr<IResHandle> texture = pResCache->GetHandle(*pResource);
			if(texture.get() == NULL)
			{
				printf("Could not create cache for %s\n", (*iter).GetData());
			}
			else
			{
				printf("added in cache : %s\n", (*iter).GetData());
			}
			SAFE_DELETE(pResource);
		}	

		strFileNames.clear();
	}
	SAFE_DELETE(pResCache);
}

void TestRandomGenerator()
{
	IRandomGenerator * pRandomGenerator =	IRandomGenerator::CreateRandomGenerator();

	printf("Generating Random Seed \n");
	pRandomGenerator->Randomize();
	int nSeed = pRandomGenerator->GetRandomSeed();
	printf("Seed : %d\n", nSeed);
	printf("Generating 100 Random no.s between 1 to 100\n");
	for (int i = 0; i < 100; i++)
	{
		printf("%d ", pRandomGenerator->Random(100));
	}

	SAFE_DELETE(pRandomGenerator);

	pRandomGenerator =	IRandomGenerator::CreateRandomGenerator();
	pRandomGenerator->SetRandomSeed(nSeed);
	printf("\n\nRegenerating Random no.s using seed : %d\n", nSeed);
	printf("Generating 100 Random no.s between 1 to 100\n");
	for (int i = 0; i < 100; i++)
	{
		printf("%d ", pRandomGenerator->Random(100));
	}

	SAFE_DELETE(pRandomGenerator);
}
