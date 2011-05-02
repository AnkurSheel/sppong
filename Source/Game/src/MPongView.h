#pragma once

#include "HumanView.h"

class cMPongView : public GameBase::cHumanView
{
public:
	cMPongView();
	~cMPongView();
	void OnRender(TICK tickCurrent, float fElapsedTime);
	void OnUpdate( int deltaMilliseconds );
	void OnLostDevice();
	HRESULT OnResetDevice();
};
