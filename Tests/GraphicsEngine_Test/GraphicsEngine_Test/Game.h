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
	cGame();
	~cGame();
	HWND OnInit(const HINSTANCE hInstance, const int nCmdShow,const bool bFullscreen, const int iFullScreenWidth, const int iFullScreenHeight);
	void OnLostDevice();

	HRESULT OnResetDevice();
	void Run();
	Base::cString GetGameTitle() const; 
	bool OnMsgProc(const Graphics::AppMsg & msg);
private:
	Graphics::IBaseControl *	m_pParentControl;
};

#endif // Game_h__