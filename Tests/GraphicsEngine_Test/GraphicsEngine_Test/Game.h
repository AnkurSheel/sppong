#ifndef Game_h__
#define Game_h__

#include "BaseApp.h"

namespace Graphics
{
	class IBaseControl;
	union unUIEventCallbackParam;
}

enum Tests
{
	TEST_NONE,
	TEST_MODELCOLOR,
	TEST_MODELTEXTURE,
	TEST_SPRITE,
	TEST_FONT,
	TEST_UICONTROLS,
	TEST_ALL,
};

class cGame : 
	public GameBase::cBaseApp
{
public:
	cGame(const Base::cString strName);
	~cGame();
	void VOnInitialization(const HINSTANCE & hInstance, const int nCmdShow,
		const Base::cString & strOptionsFileName);
	Base::cString VGetGameTitle() const; 
	void VCreateHumanView();
	void ButtonPressed(const Graphics::unUIEventCallbackParam & params);
	void Button1Released(const Graphics::unUIEventCallbackParam & params);
	void CheckBoxPressed(const Graphics::unUIEventCallbackParam & params);
	void GotoNextTest();
	Tests GetCurrentTest() const;

private:
	bool VOnHandleMessage(const AI::Telegram & telegram){return false;}

private:
	Tests	m_currentTest;
};

#endif // Game_h__