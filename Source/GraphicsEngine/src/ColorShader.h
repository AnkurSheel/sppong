// ***************************************************************
//  ColorShader   version:  1.0   Ankur Sheel  date: 2012/09/15
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

#include "ColorShader.hxx"

namespace Utilities
{
	class IFileInput;
}
namespace Graphics
{
	class cColorShader
		: public IColorShader
		, public Base::cNonCopyable
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
		bool Initialize(const Base::cString & strVertexShaderPath,
			const Base::cString & strPixelShaderPath, const int iNumberOfLayouts);

		void Render(const D3DXMATRIX & inMatWorld, const D3DXMATRIX & inMatView,
			const D3DXMATRIX & inMatProjection);
		void Cleanup();

	private:
		bool CreateVertexShader( const Base::cString & strVertexShaderPath);
		bool CreatePixelShader( const Base::cString & strPixelShaderPath);
		bool CreateLayout( const int iNumberOfLayouts, const Utilities::IFileInput * const pFile );

	private:
		ID3D11VertexShader *	m_pVertexShader;
		ID3D11PixelShader *		m_pPixelShader;
		ID3D11InputLayout *		m_pLayout;
		ID3D11Buffer *			m_pMatrixBuffer;
	};
}