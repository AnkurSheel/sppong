// ***************************************************************
//  FileInput   version:  1.0   Ankur Sheel  date: 2011/04/12
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef FileInput_h__
#define FileInput_h__

#include "FileInput.hxx"
#include <fstream>

namespace Utilities
{
	class cFileInput
		: public IFileInput
		, public Base::cNonCopyable
	{
	public:
		cFileInput();
		~cFileInput();
		bool Open(const Base::cString & strFileName, const std::ios_base::openmode mode);
		const BYTE * const  ReadAll();
		const BYTE * const  Read(std::streamoff);
		bool Close();
		void ReadLine();
		bool IsEOF();
		const BYTE * const GetBuffer() const;
		std::streamoff VGetFileSize() const;

	protected:
		std::ifstream	m_inputFile;
		Base::cString	m_strFileName;
		Base::cString	m_strBuffer;
		BYTE *			m_pBuffer;
		std::streamoff	m_iFileSize;
	};
}
#endif // FileInput_h__