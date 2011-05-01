#pragma once

#include "HumanView.h"

namespace Game
{
	class cMPongView : public GameBase::cHumanView
	{
	public:
		cMPongView();
		~cMPongView();
		void OnRender(float fTime, float fElapsedTime);
		void OnUpdate( int deltaMilliseconds );
		void OnLostDevice();
		HRESULT OnResetDevice();
	};
}
