// ***************************************************************
//  ZipFile   version:  1.0   Ankur Sheel  date: 2011/03/12
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "ZipFile.h"
#include "zlib\zlib.h"
#include "FileInput.hxx"

using namespace Utilities;
// --------------------------------------------------------------------------
// Basic types.
// --------------------------------------------------------------------------
typedef unsigned long dword;
typedef unsigned short word;
typedef unsigned char byte;

// --------------------------------------------------------------------------
// ZIP file structures. Note these have to be packed.
// --------------------------------------------------------------------------

#pragma pack(1)
// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
struct cZipFile::TZipLocalHeader
{
	enum
	{
		SIGNATURE = 0x04034b50,
	};
	dword   sig;
	word    version;
	word    flag;
	word    compression;      // Z_NO_COMPRESSION or Z_DEFLATED
	word    modTime;
	word    modDate;
	dword   crc32;
	dword   cSize;
	dword   ucSize;
	word    fnameLen;         // Filename string follows header.
	word    xtraLen;          // Extra field follows filename.
};

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
struct cZipFile::TZipDirHeader
{
	enum
	{
		SIGNATURE = 0x06054b50
	};
	dword   sig;
	word    nDisk;
	word    nStartDisk;
	word    nDirEntries;
	word    totalDirEntries;
	dword   dirSize;
	dword   dirOffset;
	word    cmntLen;
};

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
struct cZipFile::TZipDirFileHeader
{
	enum
	{
		SIGNATURE   = 0x02014b50
	};
	dword   sig;
	word    verMade;
	word    verNeeded;
	word    flag;
	word    compression;      // COMP_xxxx
	word    modTime;
	word    modDate;
	dword   crc32;
	dword   cSize;            // Compressed size
	dword   ucSize;           // Uncompressed size
	word    fnameLen;         // Filename string follows header.
	word    xtraLen;          // Extra field follows filename.
	word    cmntLen;          // Comment field follows extra field.
	word    diskStart;
	word    intAttr;
	dword   extAttr;
	dword   hdrOffset;

	char *GetName   () const { return (char *)(this + 1);   }
	char *GetExtra  () const { return GetName() + fnameLen; }
	char *GetComment() const { return GetExtra() + xtraLen; }
};

#pragma pack()

using namespace Base;
using namespace Utilities;

cZipFile::cZipFile()
: m_nEntries(0)
, m_pDirData(NULL)
{ 
}

cZipFile::~cZipFile() 
{ 
	End(); 
}

bool cZipFile::Init(const Base::cString & resFileName)
{
	End();

	if(!Open(resFileName))
	{
		return false;
	}

	// Assuming no extra comment at the end, read the whole end record.
	TZipDirHeader dh;

	fseek(m_fStdOut, -(int)sizeof(dh), SEEK_END);
	long dhOffset = ftell(m_fStdOut);
	memset(&dh, 0, sizeof(dh));
	fread(&dh, sizeof(dh), 1, m_fStdOut);

	// Check
	if (dh.sig != TZipDirHeader::SIGNATURE)
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Dir Header Signature did not match for file: %s", m_strFileName.GetData()));
		return false;
	}

	//Set the file position to the beginning of the array of TZipDirFileHeader structures
	fseek(m_fStdOut, dhOffset - dh.dirSize, SEEK_SET);

	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Dir Size : %d in file %s", dh.dirSize, m_strFileName.GetData()));
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "No. of Entries : %d in file %s", dh.nDirEntries, m_strFileName.GetData()));

	// Allocate the data buffer, and read the whole thing.
	m_pDirData = DEBUG_NEW char[dh.dirSize + dh.nDirEntries*sizeof(*m_papDir)];

	if (!m_pDirData)
		return false;
	memset(m_pDirData, 0, dh.dirSize + dh.nDirEntries*sizeof(*m_papDir));
	fread(m_pDirData, dh.dirSize, 1, m_fStdOut);

	// Now process each entry.
	char *pfh = m_pDirData;
	m_papDir = (const TZipDirFileHeader **)(m_pDirData + dh.dirSize);

	for (int i = 0; i < dh.nDirEntries; i++)
	{
		TZipDirFileHeader &fh = *(TZipDirFileHeader*)pfh;

		// Store the address of nth file for quicker access.
		m_papDir[i] = &fh;

		// Check the directory entry integrity.
		if (fh.sig != TZipDirFileHeader::SIGNATURE)
		{
			Log_Write_L1(ILogger::LT_ERROR, cString(100, "Dir File Header Signature did not match for file: %s", m_strFileName.GetData()));
			SAFE_DELETE_ARRAY(m_pDirData);
			return false;
		}
		else
		{
			pfh += sizeof(fh);

			// Convert UNIX slashes to DOS backlashes.
			for (int j = 0; j < fh.fnameLen; j++)
			{
				if (pfh[j] == '/')
				{
					pfh[j] = '\\';
				}
			}

			char fileName[_MAX_PATH];
			memcpy(fileName, pfh, fh.fnameLen);
			fileName[fh.fnameLen]=0;
			_strlwr_s(fileName, _MAX_PATH);

			std::string spath = fileName;
			m_ZipContentsMap[spath] = i;

			// Skip name, extra and comment fields.
			pfh += fh.fnameLen + fh.xtraLen + fh.cmntLen;
		}
	}
	m_nEntries = dh.nDirEntries;
	return true;
}

int cZipFile::Find(const Base::cString & strPath) const
{
	char lwrPath[MAX_PATH_WIDTH];
	strcpy_s(lwrPath, MAX_PATH_WIDTH, strPath.GetData());
	_strlwr_s(lwrPath, MAX_PATH_WIDTH);
	ZipContentsMap::const_iterator i = m_ZipContentsMap.find(lwrPath);
	if (i==m_ZipContentsMap.end())
		return -1;

	return (*i).second;
}

void cZipFile::End()
{
	m_ZipContentsMap.empty();
	SAFE_DELETE_ARRAY(m_pDirData);
	m_nEntries = 0;
}

cString cZipFile::GetFilename(int i)  const
{
	if (i < 0 || i >= m_nEntries)
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Passed Index %d invalid: in %s. Total Entries : %d", i, m_strFileName.GetData(), m_nEntries));
		return "";
	}
	else
	{
		char szDest[MAX_FILENAME_WIDTH];
		memcpy(szDest, m_papDir[i]->GetName(), m_papDir[i]->fnameLen);
		szDest[m_papDir[i]->fnameLen] = '\0';
		return szDest;
	}
}

int cZipFile::GetFileLen(int i) const
{
	if (i < 0 || i >= m_nEntries)
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Passed Index %d invalid: in %s. Total Entries : %d", i, m_strFileName.GetData(), m_nEntries));
		return -1;
	}
	else
	{
		return m_papDir[i]->ucSize;
	}
}

// --------------------------------------------------------------------------
// Function:      ReadFile
// Purpose:       Uncompress a complete file
// Parameters:    The file index and the pre-allocated buffer
// --------------------------------------------------------------------------
bool cZipFile::ReadFile(int i, void *pBuf)
{
	if (pBuf == NULL || i < 0 || i >= m_nEntries)
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Passed Index %d invalid: in %s. Total Entries : %d", i, m_strFileName.GetData(), m_nEntries));
		return false;
	}

	// Go to the actual file and read the local header.
	fseek(m_fStdOut, m_papDir[i]->hdrOffset, SEEK_SET);
	TZipLocalHeader h;

	memset(&h, 0, sizeof(h));
	fread(&h, sizeof(h), 1, m_fStdOut);
	if (h.sig != TZipLocalHeader::SIGNATURE)
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Corrupt ZipFile: %s. Local Header Signature did not match", m_strFileName.GetData()));
		return false;
	}

	// Skip extra fields
	fseek(m_fStdOut, h.fnameLen + h.xtraLen, SEEK_CUR);

	if (h.compression == Z_NO_COMPRESSION)
	{
		Log_Write_L2(ILogger::LT_COMMENT, cString(100, "No Compression for file %s in ZipFile: %s.", GetFilename(i).GetData(), m_strFileName.GetData()));
		// Simply read in raw stored data.
		fread(pBuf, h.cSize, 1, m_fStdOut);

		return true;
	}
	else if (h.compression != Z_DEFLATED)
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Unknown Compression for file %s in ZipFile: %s. ", GetFilename(i).GetData(), m_strFileName.GetData()));
		return false;
	}
	// Alloc compressed data buffer and read the whole stream
	char *pcData = DEBUG_NEW char[h.cSize];
	if (!pcData)
		return false;

	memset(pcData, 0, h.cSize);
	fread(pcData, h.cSize, 1, m_fStdOut);

	bool ret = true;

	// Setup the inflate stream.
	z_stream stream;
	int err;

	stream.next_in = (Bytef*)pcData;
	stream.avail_in = (uInt)h.cSize;
	stream.next_out = (Bytef*)pBuf;
	stream.avail_out = h.ucSize;
	stream.zalloc = Z_NULL;
	stream.zfree = Z_NULL;

	// Perform inflation. wbits < 0 indicates no zlib header inside the data.
	err = inflateInit2(&stream, -MAX_WBITS);
	if (err == Z_OK)
	{
		err = inflate(&stream, Z_FINISH);
		inflateEnd(&stream);
		if (err == Z_STREAM_END)
			err = Z_OK;
		inflateEnd(&stream);
	}
	if (err != Z_OK)
		ret = false;

	SAFE_DELETE_ARRAY(pcData);
	return ret;
}



// --------------------------------------------------------------------------
// Function:      ReadLargeFile
// Purpose:       Uncompress a complete file with callbacks.
// Parameters:    The file index and the pre-allocated buffer
// --------------------------------------------------------------------------
bool cZipFile::ReadLargeFile(int i, void *pBuf, void (*callback)(int, bool &))

{
	if (pBuf == NULL || i < 0 || i >= m_nEntries)
		return false;

	// Quick'n dirty read, the whole file at once.
	// Ungood if the ZIP has huge files inside

	// Go to the actual file and read the local header.
	fseek(m_fStdOut, m_papDir[i]->hdrOffset, SEEK_SET);
	TZipLocalHeader h;

	memset(&h, 0, sizeof(h));
	fread(&h, sizeof(h), 1, m_fStdOut);
	if (h.sig != TZipLocalHeader::SIGNATURE)
		return false;

	// Skip extra fields
	fseek(m_fStdOut, h.fnameLen + h.xtraLen, SEEK_CUR);

	if (h.compression == Z_NO_COMPRESSION)
	{
		// Simply read in raw stored data.
		fread(pBuf, h.cSize, 1, m_fStdOut);
		return true;
	}
	else if (h.compression != Z_DEFLATED)
		return false;

	// Alloc compressed data buffer and read the whole stream
	char *pcData = DEBUG_NEW char[h.cSize];
	if (!pcData)
		return false;

	memset(pcData, 0, h.cSize);
	fread(pcData, h.cSize, 1, m_fStdOut);

	bool ret = true;

	// Setup the inflate stream.
	z_stream stream;
	int err;

	stream.next_in = (Bytef*)pcData;
	stream.avail_in = (uInt)h.cSize;
	stream.next_out = (Bytef*)pBuf;
	stream.avail_out = (128 * 1024); //  read 128k at a time h.ucSize;
	stream.zalloc = Z_NULL;
	stream.zfree = Z_NULL;

	// Perform inflation. wbits < 0 indicates no zlib header inside the data.
	err = inflateInit2(&stream, -MAX_WBITS);
	if (err == Z_OK)
	{
		uInt count = 0;
		bool cancel = false;
		while (stream.total_in < (uInt)h.cSize && !cancel)
		{
			err = inflate(&stream, Z_SYNC_FLUSH);
			if (err == Z_STREAM_END)
			{
				err = Z_OK;
				break;
			}
			else if (err != Z_OK)
			{
				//assert(0 && "Something happened.");
				break;
			}

			stream.avail_out = (128 * 1024); 
			stream.next_out += stream.total_out;

			callback(count * 100 / h.cSize, cancel);
		}
		inflateEnd(&stream);
	}
	if (err != Z_OK)
		ret = false;

	SAFE_DELETE_ARRAY(pcData);
	return ret;
}

IZipFile * IZipFile::CreateZipFile()
{
	IZipFile * pZipFile = DEBUG_NEW cZipFile();
	return pZipFile;
}
