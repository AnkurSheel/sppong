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
	class IMyFont;
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
	shared_ptr<Graphics::IMyFont> GetFont();

private:
	shared_ptr<Graphics::IMyFont>	m_pFont;
	UINT							m_iValue;
};
#endif // Score_h__