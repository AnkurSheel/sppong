#ifndef Game_h__
#define Game_h__

#include "BaseApp.h"

namespace Graphics
{
	class IBaseControl;
}

enum Tests
{
	TEST_NONE,
	TEST_TRIANGLE,
	TEST_TEXTURETRIANGLE,
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
	void ButtonPressed(bool bPressed);
	void Button1Pressed( bool bPressed);
	void CheckBoxPressed(bool bPressed);
	void GotoNextTest();
	Tests GetCurrentTest() const;

private:
	bool VOnHandleMessage(const AI::Telegram & telegram){return false;}

private:
	Tests	m_currentTest;
};

#endif // Game_h__