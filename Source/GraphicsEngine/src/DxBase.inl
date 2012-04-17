// ***************************************************************
// Checks if the device is available
// ***************************************************************
inline HRESULT cDXBase::VIsAvailable() const
{
	    return(m_pd3dDevice->TestCooperativeLevel()) ;
}
// ***************************************************************

// ***************************************************************
// Function to end the rendering
// ***************************************************************
inline void cDXBase::VEndRender( const HRESULT hr )
{
	if(SUCCEEDED(hr))
	{
		m_pd3dDevice->EndScene() ;
	}
	// Present/Display the contents
	m_pd3dDevice->Present(NULL, NULL, NULL, NULL) ;
}
// ***************************************************************

// ***************************************************************
// Returns the directX device
// ***************************************************************
inline LPDIRECT3DDEVICE9 cDXBase::VGetDevice() const
{
	return m_pd3dDevice;
}
// ***************************************************************