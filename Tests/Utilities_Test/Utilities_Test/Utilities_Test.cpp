// Utilities_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ZipFile.hxx"
#include "Logger.hxx"
#include "ResCache.hxx"
#include "RandomGenerator.hxx"
#include "FileInput.hxx"
#include "ParamLoaders.hxx"
#include <direct.h>
#include <vector>
#include <memory>
#include <conio.h>
#include "Optional.h"

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
void TestFileInput();
void TestParamLoader();

void main(int argc, char * argv[])
{
	CheckForMemoryLeaks() ;

	ILogger::GetInstance()->StartConsoleWin(120,60, "Log.txt");

	TestZipFile();
	Log_Write_L1(ILogger::LT_UNKNOWN, "");

	TestResourceCache();
	Log_Write_L1(ILogger::LT_UNKNOWN, "");

	TestRandomGenerator();
	Log_Write_L1(ILogger::LT_UNKNOWN, "");

	TestFileInput();

	Log_Write_L1(ILogger::LT_UNKNOWN, "");
	TestParamLoader();

	ILogger::Destroy();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE| FOREGROUND_RED | FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	printf("Press Any Key to continue");
	while (!_kbhit())
	{
	}
}

void MakePath(const char *pszPath)
{
	if (pszPath[0] == '\0')
		return;

	char buf[1000];
	const char *p = pszPath;

	Log_Write_L1(ILogger::LT_COMMENT, cString("MakePath ") + pszPath);

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

	Log_Write_L1(ILogger::LT_UNKNOWN, "***************************************************************");
	Log_Write_L1(ILogger::LT_UNKNOWN, "Start Test: Zip File");
	Log_Write_L1(ILogger::LT_UNKNOWN, "***************************************************************");

	IZipFile * pZip = IZipFile::CreateZipFile();;

	if(pZip)
	{
		char szPath[MAX_PATH_WIDTH];
		printf("Enter Zip file path (resources\\resources.zip): ");
		gets(szPath);
		if (!pZip->Init(szPath))
		{
			Log_Write_L1(ILogger::LT_ERROR, cString("Bad Zip file: ") + szPath);
		}
		else
		{
			for (int i = 0; i < pZip->GetNumFiles(); i++)
			{
				int len = pZip->GetFileLen(i);
				cString strFileName;

				strFileName = pZip->GetFilename(i);
				Log_Write_L1(ILogger::LT_DEBUG, "File: " + strFileName + cString(20, " : %d bytes", len));

				char *pData = new char[len];
				if (!pData)
				{
					Log_Write_L1(ILogger::LT_ERROR, "OUT OF MEMORY", );
				}
				else if (true == pZip->ReadFile(i, pData))
				{
					Log_Write_L1(ILogger::LT_COMMENT, "OK");
					cString dpath= "Data\\Test\\" + strFileName;

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
				{
					Log_Write_L1(ILogger::LT_ERROR, "ERROR");
				}
				delete[] pData;
			}
			pZip->End();
		}
	}
	else
	{
		Log_Write_L1(ILogger::LT_ERROR, "Could Not Create Zipfile object");
	}
	SAFE_DELETE(pZip);

	Log_Write_L1(ILogger::LT_UNKNOWN, "***************************************************************");
	Log_Write_L1(ILogger::LT_UNKNOWN, "End Test: Zip File");
	Log_Write_L1(ILogger::LT_UNKNOWN, "***************************************************************");
}


void TestResourceCache()
{
	Log_Write_L1(ILogger::LT_UNKNOWN, "***************************************************************");
	Log_Write_L1(ILogger::LT_UNKNOWN, "Start Test: Resource Cache");
	Log_Write_L1(ILogger::LT_UNKNOWN, "***************************************************************");

	char szPath[MAX_PATH_WIDTH];
	printf("Enter Zip file path (resources\\resources.zip): ");
	gets(szPath);

	IResCache * pResCache =  IResCache::CreateResourceCache(1, szPath);
	if(!pResCache->Init())
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Bad Zip file for Resource Cache") + szPath );
	}
	else
	{
		IZipFile * pZip = IZipFile::CreateZipFile();

		vector<cString> strFileNames;
		if(pZip)
		{
			if (!pZip->Init(szPath))
			{
				Log_Write_L1(ILogger::LT_ERROR, cString("Bad Zip file: ") + szPath);
			}
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
				Log_Write_L1(ILogger::LT_ERROR, "Could not create cache for " + (*iter));
			}
			else
			{
				Log_Write_L1(ILogger::LT_DEBUG, "added in cache : " + (*iter));
			}
			SAFE_DELETE(pResource);
		}	

		strFileNames.clear();
	}
	SAFE_DELETE(pResCache);
	
	Log_Write_L1(ILogger::LT_UNKNOWN, "***************************************************************");
	Log_Write_L1(ILogger::LT_UNKNOWN, "End Test: Resource Cache");
	Log_Write_L1(ILogger::LT_UNKNOWN, "***************************************************************");
}

void TestRandomGenerator()
{
	Log_Write_L1(ILogger::LT_UNKNOWN, "***************************************************************");
	Log_Write_L1(ILogger::LT_UNKNOWN, "Start Test: Random Generator");
	Log_Write_L1(ILogger::LT_UNKNOWN, "***************************************************************");

	IRandomGenerator * pRandomGenerator =	IRandomGenerator::CreateRandomGenerator();

	Log_Write_L1(ILogger::LT_COMMENT, "Generating Random Seed");
	pRandomGenerator->Randomize();
	int nSeed = pRandomGenerator->GetRandomSeed();
	Log_Write_L1(ILogger::LT_DEBUG, "Seed : " + cString(20, "%d", nSeed));
	Log_Write_L1(ILogger::LT_COMMENT, "Generating 100 Random no.s between 1 to 100");
	for (int i = 0; i < 100; i++)
	{
		Log_Write_L1(ILogger::LT_DEBUG, "Random Number " + cString(20, "%d: %d", i, pRandomGenerator->Random(100)));
	}

	SAFE_DELETE(pRandomGenerator);

	pRandomGenerator =	IRandomGenerator::CreateRandomGenerator();
	pRandomGenerator->SetRandomSeed(nSeed);
	Log_Write_L1(ILogger::LT_DEBUG, "Regenerating Random no.s using seed : " + cString(20, "%d", nSeed));
	Log_Write_L1(ILogger::LT_COMMENT, "Generating 100 Random no.s between 1 to 100");
	for (int i = 0; i < 100; i++)
	{
		Log_Write_L1(ILogger::LT_DEBUG, "Random Number " + cString(20, "%d: %d", i, pRandomGenerator->Random(100)));
	}

	SAFE_DELETE(pRandomGenerator);

	Log_Write_L1(ILogger::LT_UNKNOWN, "***************************************************************");
	Log_Write_L1(ILogger::LT_UNKNOWN, "End Test: Random Generator");
	Log_Write_L1(ILogger::LT_UNKNOWN, "***************************************************************");
}

void TestFileInput()
{
	Log_Write_L1(ILogger::LT_UNKNOWN, "***************************************************************");
	Log_Write_L1(ILogger::LT_UNKNOWN, "Start Test: FileInput");
	Log_Write_L1(ILogger::LT_UNKNOWN, "***************************************************************");

	char szPath[MAX_PATH_WIDTH];
	printf("Enter file path (params.ini): ");
	gets(szPath);

	IFileInput * pFile = IFileInput::CreateInputFile();

	if(pFile != NULL)
	{
		Log_Write_L1(ILogger::LT_COMMENT, "Reading the whole file");
		Log_Write_L1(ILogger::LT_UNKNOWN, "***************************************************************");
		if(pFile->Open(szPath, std::ios_base::in))
		{
			cString str = pFile->ReadAll();
			if(str.IsEmpty())
			{
					Log_Write_L1(ILogger::LT_ERROR, "Failed");
			}
			else
			{
				Log_Write_L1(ILogger::LT_COMMENT, "Successfull");
			}
				
			pFile->Close();
		}
		Log_Write_L1(ILogger::LT_UNKNOWN, "***************************************************************");
		Log_Write_L1(ILogger::LT_UNKNOWN, "");
		Log_Write_L1(ILogger::LT_COMMENT, "Reading the file 1 string at time");
		Log_Write_L1(ILogger::LT_UNKNOWN, "***************************************************************");
		if(pFile->Open(szPath, std::ios_base::in))
		{
			while(!pFile->IsEOF())
			{
				pFile->ReadLine();
				Log_Write_L1(ILogger::LT_DEBUG, pFile->GetBuffer());
			}
			pFile->Close();
		}
		Log_Write_L1(ILogger::LT_UNKNOWN, "***************************************************************");
		Log_Write_L1(ILogger::LT_UNKNOWN, "");
	}

	SAFE_DELETE(pFile);

	Log_Write_L1(ILogger::LT_UNKNOWN, "***************************************************************");
	Log_Write_L1(ILogger::LT_UNKNOWN, "End Test: FileInput");
	Log_Write_L1(ILogger::LT_UNKNOWN, "***************************************************************");
}

void TestParamLoader()
{
	Log_Write_L1(ILogger::LT_UNKNOWN, "***************************************************************");
	Log_Write_L1(ILogger::LT_UNKNOWN, "Start Test: ParamLoader");
	Log_Write_L1(ILogger::LT_UNKNOWN, "***************************************************************");

	char szPath[MAX_PATH_WIDTH];
	printf("Enter file path (params.ini): ");
	gets(szPath);

	IParamLoader * pFile = IParamLoader::CreateParamLoader();

	if(pFile != NULL)
	{
		pFile->VLoadParametersFromFile(szPath);
		/*if(pFile->VOpen(szPath))
		{
			Log_Write_L1(ILogger::LT_COMMENT, "Getting Next Parameter As Int");
			tOptional<int> intVal = pFile->VGetNextParameterAsInt();
			if(intVal.IsValid())
			{
				Log_Write_L1(ILogger::LT_DEBUG, cString(50, "Parameter Value %d", *intVal));
			}
			Log_Write_L1(ILogger::LT_COMMENT, "Getting Next Parameter As Int");
			intVal = pFile->VGetNextParameterAsInt();
			if(intVal.IsValid())
			{
				Log_Write_L1(ILogger::LT_DEBUG, cString(50, "Parameter Value %d", *intVal));
			} 
			Log_Write_L1(ILogger::LT_COMMENT, "Getting Next Parameter As Int");
			intVal = pFile->VGetNextParameterAsInt();
			if(intVal.IsValid())
			{
				Log_Write_L1(ILogger::LT_DEBUG, cString(50, "Parameter Value %d", *intVal));
			} 

			Log_Write_L1(ILogger::LT_COMMENT, "Getting Next Parameter As Float");
			tOptional<float> floatVal = pFile->VGetNextParameterAsFloat();
			if(floatVal.IsValid())
			{
				Log_Write_L1(ILogger::LT_DEBUG, cString(50, "Parameter Value %f", *floatVal));
			}
			Log_Write_L1(ILogger::LT_COMMENT, "Getting Next Parameter As Float");
			floatVal = pFile->VGetNextParameterAsFloat();
			if(floatVal.IsValid())
			{
				Log_Write_L1(ILogger::LT_DEBUG, cString(50, "Parameter Value %f", *floatVal));
			}
			Log_Write_L1(ILogger::LT_COMMENT, "Getting Next Parameter As Float");
			floatVal = pFile->VGetNextParameterAsFloat();
			if(floatVal.IsValid())
			{
				Log_Write_L1(ILogger::LT_DEBUG, cString(50, "Parameter Value %f", *floatVal));
			}
			floatVal = pFile->VGetNextParameterAsFloat();
			Log_Write_L1(ILogger::LT_COMMENT, "Getting Next Parameter As Float");
			if(floatVal.IsValid())
			{
				Log_Write_L1(ILogger::LT_DEBUG, cString(50, "Parameter Value %f", *floatVal));
			}

			Log_Write_L1(ILogger::LT_COMMENT, "Getting Next Parameter As bool");
			tOptional<bool> boolVal = pFile->VGetNextParameterAsBool();
			if(boolVal.IsValid())
			{
				Log_Write_L1(ILogger::LT_DEBUG, cString(50, "Parameter Value %d", *boolVal));
			}
			Log_Write_L1(ILogger::LT_COMMENT, "Getting Next Parameter As bool");
			boolVal = pFile->VGetNextParameterAsBool();
			if(boolVal.IsValid())
			{
				Log_Write_L1(ILogger::LT_DEBUG, cString(50, "Parameter Value %d", *boolVal));
			}
			Log_Write_L1(ILogger::LT_COMMENT, "Getting Next Parameter As bool");
			boolVal = pFile->VGetNextParameterAsBool();
			if(boolVal.IsValid())
			{
				Log_Write_L1(ILogger::LT_DEBUG, cString(50, "Parameter Value %d", *boolVal));
			}
			pFile->VClose();
		}*/
	}
	SAFE_DELETE(pFile);

	Log_Write_L1(ILogger::LT_UNKNOWN, "***************************************************************");
	Log_Write_L1(ILogger::LT_UNKNOWN, "End Test: ParamLoader");
	Log_Write_L1(ILogger::LT_UNKNOWN, "***************************************************************");
}
