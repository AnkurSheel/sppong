#ifndef Game_h__
#define Game_h__

#include "BaseApp.h"

namespace Graphics
{
	class IBaseControl;
}

class cGame : 
	public GameBase::cBaseApp
{
public:
	cGame(const Base::cString strName);
	~cGame();
	HWND  VOnInitialization(const HINSTANCE hInstance, const int nCmdShow,const bool bFullscreen, const int iFullScreenWidth, const int iFullScreenHeight);
	void VOnLostDevice();
	HRESULT VOnResetDevice();
	void VRun();
	Base::cString VGetGameTitle() const; 
	bool VOnMsgProc(const Graphics::AppMsg & msg);

	void ButtonPressed(bool bPressed);
	void Button1Pressed( bool bPressed);
	void CheckBoxPressed(bool bPressed);
private:
	void VOnUpdate(){}
	bool VOnHandleMessage(const AI::Telegram & telegram){return false;}
private:
	Graphics::IBaseControl *	m_pParentControl;
};

#endif // Game_h__