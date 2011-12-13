// ***************************************************************
//  Score   version:  1.0   Ankur Sheel  date: 05/15/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Score_h__
#define Score_h__

namespace Base
{
	class cString;
}

namespace Graphics
{
	class IFont ;
}
class cScore
{
private:
	cScore(const cScore&){}
	cScore operator = (const cScore&){}
public:
	cScore();
	~cScore();
	void Init(const D3DXVECTOR3& vInitialPos);
	void Cleanup();
	void IncrementScore();
	shared_ptr<Graphics::IFont> GetFont();

private:
	shared_ptr<Graphics::IFont>		m_pFont;
	UINT							m_iValue;
};
#endif // Score_h__