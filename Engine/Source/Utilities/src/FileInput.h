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
		const unsigned char * const  ReadAll();
		const unsigned char * const  Read(unsigned long ulSize);
		bool Close();
		Base::cString ReadLine();
		bool IsEOF();
		const unsigned char * const GetBuffer() const;
		unsigned long VGetFileSize() const;

	protected:
		std::ifstream	m_inputFile;
		Base::cString	m_strFileName;
		Base::cString	m_strBuffer;
		unsigned char *	m_pBuffer;
		unsigned long	m_iFileSize;
	};
}
#endif // FileInput_h__