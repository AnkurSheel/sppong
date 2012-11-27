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

namespace Graphics
{
	class IBaseControl;
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
	shared_ptr<Graphics::IBaseControl> GetLabel();

private:
	shared_ptr<Graphics::IBaseControl>	m_pLabel;
	UINT								m_iValue;
};
#endif // Score_h__