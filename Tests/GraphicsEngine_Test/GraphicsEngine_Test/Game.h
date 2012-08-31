#ifndef Game_h__
#define Game_h__

#include "BaseApp.h"

namespace Graphics
{
	class IBaseControl;
}

enum Tests
{
	NONE,
	UICONTROLS,
	ALL,
};

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

	void GotoNextTest();
	void TestUIControls();

private:
	Graphics::IBaseControl *	m_pParentControl;
	Graphics::IBaseControl *	m_pInfoLabelControl;
	Tests						m_currentTest;
};

#endif // Game_h__