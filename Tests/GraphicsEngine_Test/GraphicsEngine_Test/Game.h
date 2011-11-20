#ifndef Game_h__
#define Game_h__

#include "BaseApp.h"

class cGame : 
	public GameBase::cBaseApp
{
public:
	HWND OnInit(const HINSTANCE hInstance, const int nCmdShow,const bool bFullscreen);
	Base::cString GetGameTitle() const; 
	void OnMsgProc(const GameBase::AppMsg & msg);
	void Run();

};

#endif // Game_h__