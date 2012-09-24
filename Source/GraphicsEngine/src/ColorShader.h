// ***************************************************************
//  ColorShader   version:  1.0   Ankur Sheel  date: 2012/09/15
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

#include "BaseShader.h"

namespace Utilities
{
	class IFileInput;
}

namespace Graphics
{
	class cColorShader
		: public cBaseShader
	{
		struct MatrixBufferType
		{
			D3DXMATRIX world;
			D3DXMATRIX view;
			D3DXMATRIX projection;
		};
	public:
		cColorShader();
		~cColorShader();

	private:
		bool VCreateLayout( const int iNumberOfLayouts,
			const Utilities::IFileInput * const pVertexShaderFile );
	};
}