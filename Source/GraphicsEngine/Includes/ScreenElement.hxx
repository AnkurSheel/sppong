#pragma once

#include "GraphicEngineDefines.h"
#include "Constants.h"

namespace Base
{
	class cString;
}

namespace Graphics
{
	class IScreenElement
	{
	public:
		virtual ~IScreenElement(){};
		GRAPHIC_API virtual void OnLostDevice() = 0;
		GRAPHIC_API virtual void OnResetDevice() = 0;
		GRAPHIC_API virtual bool IsVisible() = 0;
		GRAPHIC_API virtual void Render(LPDIRECT3DDEVICE9 const pDevice) = 0;
	};
}