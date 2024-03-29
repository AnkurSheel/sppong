
// ***************************************************************
//  DxBase   version:  1.0   Ankur Sheel  date: 04/29/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "DxBase.h" 

using namespace Utilities;
using namespace Base;
using namespace Graphics;

IDXBase * cDXBase::s_pDXBase = NULL;

// ***************************************************************
Graphics::cDXBase::cDXBase()
: m_bVsyncEnabled(false)
, m_pSwapChain(NULL)
, m_pDevice(NULL)
, m_pDeviceContext(NULL)
, m_pRenderTargetView(NULL)
, m_pDepthStencilBuffer(NULL)
, m_p3DDepthStencilState(NULL)
, m_p2DDepthStencilState(NULL)
, m_pDepthStencilView(NULL)
, m_pRasterState(NULL)
, m_iScreenWidth(0)
, m_iScreenHeight(0)
, m_pAlphaEnableBlendingState(NULL)
, m_pAlphaDisableBlendingState(NULL)
{

}

// ***************************************************************
Graphics::cDXBase::~cDXBase()
{
	Cleanup();
}

// ***************************************************************
void Graphics::cDXBase::VInitialize( const HWND & hWnd, const Base::cColor & bkColor,
										  const bool bFullScreen, const bool bVsyncEnabled,
										  const int iWidth, const int iHeight,
										  const float fScreenDepth, const float fScreenNear )
{

	m_bVsyncEnabled = bVsyncEnabled;
	m_iScreenWidth = iWidth;
	m_iScreenHeight = iHeight;

	bkColor.GetColorComponentsInFloat(m_afBackGroundcolor[0], m_afBackGroundcolor[1],
		m_afBackGroundcolor[2], m_afBackGroundcolor[3]);

	if(!SetupRenderTargets(iWidth, iHeight, hWnd, bFullScreen))
		return;

	if(!SetupRasterStates())
		return;

	if(!CreateBlendStates())
		return;

	SetupViewPort(iWidth, iHeight);

	SetupProjectionMatrix(iWidth, iHeight, fScreenNear, fScreenDepth);
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixOrthoLH(&m_matOrtho, (float)iWidth, (float)iHeight, fScreenNear, fScreenDepth);
	VTurnOnAlphaBlending();
}

// ***************************************************************
void Graphics::cDXBase::VBeginRender()
{
	// Clear the back buffer.
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, m_afBackGroundcolor);

	// Clear the depth buffer.
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

// ***************************************************************
void Graphics::cDXBase::VEndRender()
{
	// Present the back buffer to the screen since rendering is complete.
	if(m_bVsyncEnabled)
	{
		// Lock to screen refresh rate.
		m_pSwapChain->Present(1, 0);
	}
	else
	{
		// Present as fast as possible.
		m_pSwapChain->Present(0, 0);
	}

}

// ***************************************************************
ID3D11Device * Graphics::cDXBase::VGetDevice() const
{
	return m_pDevice;
}

// ***************************************************************
ID3D11DeviceContext * Graphics::cDXBase::VGetDeviceContext() const
{
	return m_pDeviceContext;
}

// ***************************************************************
const D3DMATRIX & Graphics::cDXBase::VGetWorldMatrix() const
{
	return m_matWorld;
}

// ***************************************************************
const D3DMATRIX & Graphics::cDXBase::VGetProjectionMatrix() const
{
	return m_matProjection;
}

// ***************************************************************
const D3DMATRIX & Graphics::cDXBase::VGetOrthoMatrix() const
{
	return m_matOrtho;
}

// ***************************************************************
int Graphics::cDXBase::VGetScreenWidth() const
{
	return m_iScreenWidth;
}

// ***************************************************************
int Graphics::cDXBase::VGetScreenHeight() const
{
	return m_iScreenHeight;
}

// ***************************************************************
void Graphics::cDXBase::VTurnZBufferOn()
{
	m_pDeviceContext->OMSetDepthStencilState(m_p3DDepthStencilState, 1);
}

// ***************************************************************
void Graphics::cDXBase::VTurnZBufferOff()
{
	m_pDeviceContext->OMSetDepthStencilState(m_p2DDepthStencilState, 1);
}

// ***************************************************************
void Graphics::cDXBase::VTurnOnAlphaBlending()
{
	float blendFactor[4];

	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;

	// Turn on the alpha blending.
	m_pDeviceContext->OMSetBlendState(m_pAlphaEnableBlendingState, blendFactor, 0xffffffff);
}

// ***************************************************************
void Graphics::cDXBase::VTurnOffAlphaBlending()
{
	float blendFactor[4];

	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;

	// Turn on the alpha blending.
	m_pDeviceContext->OMSetBlendState(m_pAlphaDisableBlendingState, blendFactor, 0xffffffff);
}

// *************************************************************************
void Graphics::cDXBase::VSetFullScreenMode(const bool bIsFullScreen)
{
	if (m_pSwapChain)
	{
		m_pSwapChain->SetFullscreenState(bIsFullScreen, NULL);
	}
}

// ***************************************************************
bool Graphics::cDXBase::SetupRenderTargets( const int iWidth,
										   const int iHeight, const HWND & hWnd,
										   const bool bFullScreen )
{
	if(!SetupSwapChain(iWidth, iHeight, hWnd, bFullScreen))
		return false;

	if(!CreateDepthStencilBuffer(iWidth, iHeight))
		return false;

	if(!SetupDepthStencilStateFor3D())
		return false;

	if(!SetupDepthStencilStateFor2D())
		return false;

	m_pDeviceContext->OMSetDepthStencilState(m_p3DDepthStencilState, 1);

	if(!CreateDepthStencilView())
		return false;

	// Bind the render target view and depth stencil buffer to the output render pipeline.
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	return true;
}

// ***************************************************************
bool Graphics::cDXBase::SetupSwapChain( const int iWidth, const int iHeight,
									 const HWND & hWnd, const bool bFullScreen )
{
	if(!GetDisplayMode(iWidth, iHeight))
		return false;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = iWidth;
	swapChainDesc.BufferDesc.Height = iHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	if(m_bVsyncEnabled)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = m_DisplayMode.RefreshRate.Numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = m_DisplayMode.RefreshRate.Denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	swapChainDesc.Windowed = !bFullScreen;

	unsigned int iCreationFlags = 0;
#ifdef _DEBUG
	iCreationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE, D3D_DRIVER_TYPE_SOFTWARE
	};

	D3D_FEATURE_LEVEL featureLevel;
	HRESULT result;
	for( int i = 0; i < 4; ++i )
	{
		result = D3D11CreateDeviceAndSwapChain(NULL, driverTypes[i],
			NULL, iCreationFlags, NULL, NULL, D3D11_SDK_VERSION, &swapChainDesc, 
			&m_pSwapChain, &m_pDevice, &featureLevel, &m_pDeviceContext);

		if( SUCCEEDED( result ) )
			break;
	}
	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not create the  swap chain, Direct3D device, and Direct3D device context : ") 
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		PostQuitMessage(0);
		return false;
	}

	if(!AttachBackBufferToSwapChain())
		return false;
	
	return true;
}

// ***************************************************************
bool Graphics::cDXBase::SetupDepthStencilStateFor3D()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	// Initialize the description of the stencil state.
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	HRESULT result = m_pDevice->CreateDepthStencilState(&depthStencilDesc, &m_p3DDepthStencilState);
	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not create the depth stencil state")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		PostQuitMessage(0);
		return false;
	}

	return true;
}

// ***************************************************************
bool Graphics::cDXBase::SetupDepthStencilStateFor2D()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	// Initialize the description of the stencil state.
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	depthStencilDesc.DepthEnable = false;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	HRESULT result = m_pDevice->CreateDepthStencilState(&depthStencilDesc, &m_p2DDepthStencilState);
	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not create the depth stencil state for 2D drawing")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		PostQuitMessage(0);
		return false;
	}

	return true;
}

// ***************************************************************
bool Graphics::cDXBase::CreateDepthStencilView()
{
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	HRESULT result = m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, &depthStencilViewDesc, &m_pDepthStencilView);
	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not create the depth stencil view")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		PostQuitMessage(0);
		return false;
	}
	return true;
}

// ***************************************************************
bool Graphics::cDXBase::CreateBlendStates()
{
	D3D11_BLEND_DESC blendStateDescription;
	ZeroMemory(&blendStateDescription, sizeof(D3D11_BLEND_DESC));

	// Create an alpha enabled blend state description.
	blendStateDescription.RenderTarget[0].BlendEnable = TRUE;
	blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].RenderTargetWriteMask = 0x0f;

	HRESULT result = m_pDevice->CreateBlendState(&blendStateDescription, &m_pAlphaEnableBlendingState);
	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not create the blend State")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		return false;
	}

	blendStateDescription.RenderTarget[0].BlendEnable = FALSE;
	
	result = m_pDevice->CreateBlendState(&blendStateDescription,
		&m_pAlphaDisableBlendingState);
	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not create the blend State")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		return false;
	}
	return true;
}

// ***************************************************************
bool Graphics::cDXBase::SetupRasterStates()
{
	D3D11_RASTERIZER_DESC rasterDesc;
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	HRESULT result = m_pDevice->CreateRasterizerState(&rasterDesc, &m_pRasterState);
	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not create raster State")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		PostQuitMessage(0);
		return false;
	}

	m_pDeviceContext->RSSetState(m_pRasterState);
	return true;
}

// ***************************************************************
void Graphics::cDXBase::SetupViewPort( const int iWidth, const int iHeight )
{
	D3D11_VIEWPORT viewport;
	// Setup the viewport for rendering.
	viewport.Width = static_cast<float>(iWidth);
	viewport.Height = static_cast<float>(iHeight);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	// Create the viewport.
	m_pDeviceContext->RSSetViewports(1, &viewport);
}

// ***************************************************************
bool Graphics::cDXBase::GetDisplayMode(const int iWidth, const int iHeight)
{
	HRESULT result;

	IDXGIFactory * pFactory = NULL;
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory);
	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not create IDXGIFactory factory")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		PostQuitMessage(0);
		return false;
	}

	IDXGIAdapter * pAdapter = NULL;
	result = pFactory->EnumAdapters(0, &pAdapter);
	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not create  an adapter for the video card")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		PostQuitMessage(0);
		return false;
	}

	IDXGIOutput* pAdapterOutput = NULL;
	result = pAdapter->EnumOutputs(0, &pAdapterOutput);
	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not Enumerate the monitor")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		PostQuitMessage(0);
		return false;
	}

	unsigned int iNumModes;
	result = pAdapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, 
		DXGI_ENUM_MODES_INTERLACED, &iNumModes, NULL);
	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not get the number of modes for the monitor with DXGI_FORMAT_R8G8B8A8_UNORM display format.")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		PostQuitMessage(0);
		return false;
	}

	DXGI_MODE_DESC * pDisplayModeList = DEBUG_NEW DXGI_MODE_DESC[iNumModes];
	result = pAdapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_ENUM_MODES_INTERLACED, &iNumModes, pDisplayModeList);
	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not get the display modes for this monitor/video card combination.")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		PostQuitMessage(0);
		return false;
	}

	// Get the numerator and denominator for the refresh rate
	for(unsigned int i = 0; i < iNumModes; i++)
	{
		if(pDisplayModeList[i].Width == (unsigned int)iWidth)
		{
			if(pDisplayModeList[i].Height == (unsigned int)iHeight)
			{
				m_DisplayMode = pDisplayModeList[i];
				break;
			}
		}
	}

	SAFE_DELETE(pDisplayModeList);
	SAFE_RELEASE(pAdapterOutput);
	SAFE_RELEASE(pAdapter);
	SAFE_RELEASE(pFactory);

	return true;
}

// ***************************************************************
bool Graphics::cDXBase::AttachBackBufferToSwapChain()
{
	ID3D11Texture2D * pbackBufferTexture = NULL;
	bool bSuccess = true;
	HRESULT result = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), 
		(LPVOID*)&pbackBufferTexture);
	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not get a pointer to the back buffer.")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		PostQuitMessage(0);
		bSuccess = false;
	}
	else
	{
		result = m_pDevice->CreateRenderTargetView(pbackBufferTexture, NULL, &m_pRenderTargetView);
		if(FAILED(result))
		{
			Log_Write_L1(ILogger::LT_ERROR, cString("Could not create a render target view with the back buffer pointer.")
				+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
			PostQuitMessage(0);
			bSuccess = false;
		}
	}
	SAFE_RELEASE(pbackBufferTexture);
	return bSuccess;
}

// ***************************************************************
bool Graphics::cDXBase::CreateDepthStencilBuffer( const int iWidth, const int iHeight )
{
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// Set up the description of the depth buffer.
	depthBufferDesc.Width = iWidth;
	depthBufferDesc.Height = iHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	HRESULT result = m_pDevice->CreateTexture2D(&depthBufferDesc, NULL, &m_pDepthStencilBuffer);
	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not create the 2D texture for the depth buffer")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		PostQuitMessage(0);
		return false;
	}
	return true;
}

// ***************************************************************
void Graphics::cDXBase::SetupProjectionMatrix( const int iWidth, const int iHeight, const float fScreenNear, const float fScreenDepth )
{
	float fFieldOfView= (float)D3DX_PI / 4.0f;
	float fScreenAspect = (float)iWidth / (float)iHeight;

	// Create the projection matrix for 3D rendering.
	D3DXMatrixPerspectiveFovLH(&m_matProjection, fFieldOfView, fScreenAspect, fScreenNear, fScreenDepth);
}

// ***************************************************************
void Graphics::cDXBase::Cleanup()
{
	// Before shutting down set to windowed mode or when you release the swap chain it will throw an exception.
	VSetFullScreenMode(false);

	SAFE_RELEASE(m_pRasterState);
	SAFE_RELEASE(m_pDepthStencilView);
	SAFE_RELEASE(m_p3DDepthStencilState);
	SAFE_RELEASE(m_p2DDepthStencilState);
	SAFE_RELEASE(m_pDepthStencilBuffer);
	SAFE_RELEASE(m_pRenderTargetView);
	SAFE_RELEASE(m_pAlphaEnableBlendingState);
	SAFE_RELEASE(m_pAlphaDisableBlendingState);

	SAFE_RELEASE(m_pDeviceContext);
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pSwapChain);
}

// ***************************************************************
Graphics::IDXBase * Graphics::IDXBase::GetInstance()
{
	if (cDXBase::s_pDXBase == NULL)
		cDXBase::s_pDXBase = DEBUG_NEW cDXBase();
	return cDXBase::s_pDXBase ;
}

// ***************************************************************
void Graphics::IDXBase::Destroy()
{
	SAFE_DELETE(cDXBase::s_pDXBase);
}
