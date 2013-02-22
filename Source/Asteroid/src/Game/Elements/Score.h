// *****************************************************************************
//  Score   version:  1.0   Ankur Sheel  date: 05/15/2008
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef Score_h__
#define Score_h__

namespace Base
{
	class cVector2;
}

namespace Graphics
{
	class IBaseControl;
}

class cScore
	: public Base::cNonCopyable
{
public:
	cScore();
	~cScore();
	void Init(const Base::cVector2 & vInitialPos);
	void Cleanup();
	void IncrementScore();
	shared_ptr<Graphics::IBaseControl> GetLabel();

private:
	shared_ptr<Graphics::IBaseControl>	m_pLabel;
	UINT								m_iValue;
};
#endif // Score_h__