// ***************************************************************
// Checks if the device is available
// ***************************************************************
inline HRESULT cDXBase::IsAvailable() const
{
	    return(m_pd3dDevice->TestCooperativeLevel()) ;
}
// ***************************************************************

// ***************************************************************
// Function to end the rendering
// ***************************************************************
inline void cDXBase::EndRender( const HRESULT hr )
{
	if(SUCCEEDED(hr))
	{
		m_pd3dDevice->EndScene() ;
	}
	m_pd3dDevice->Present(NULL, NULL, NULL, NULL) ;
	}
// ***************************************************************

// ***************************************************************
// Returns the directX device
// ***************************************************************
inline LPDIRECT3DDEVICE9 cDXBase::GetDevice() const
{
	return m_pd3dDevice;
}
// ***************************************************************

// ***************************************************************
// Returns the display height
// ***************************************************************
inline UINT cDXBase::GetDisplayHeight() const
{
	return m_displayMode.Height;
}
// ***************************************************************

// ***************************************************************
// Returns the display width
// ***************************************************************
inline UINT cDXBase::GetDisplayWidth() const
{
	return m_displayMode.Width;
}
// ***************************************************************