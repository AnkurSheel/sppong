// ***************************************************************
//  Ball   version:  1.0   Ankur Sheel  date: 05/13/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Ball_h__
#define Ball_h__

#include "PongGameElement.h"

namespace Base
{
	class cString;
}
namespace Utilities
{
	class IRandomGenerator;
}

class cBall  
	: public cPongGameElement
{
	cBall(const cBall&){}
	cBall operator = (const cBall&) {}
public:
	cBall();
	~cBall();
	void Init(const D3DXVECTOR3& vInitialPos, const Base::cString & strFilename);
	void Render(LPDIRECT3DDEVICE9 const pDevice, const DWORD dwFlags = NULL, const D3DCOLOR& tint = Graphics::WHITE, const RECT* pSrcRect = NULL);
	void OnResetDevice(LPDIRECT3DDEVICE9 const pDevice);
	void ChangeSpeedX();
	void ChangeSpeedY();
	void OnRestart(const D3DXVECTOR3& vInitialPos);
	void Cleanup();
	cBall * CastToBall();
private:
	D3DXVECTOR3			m_vSpeed;
	Utilities::IRandomGenerator *	m_pRandomGenerator;
};
#endif // Ball_h__
