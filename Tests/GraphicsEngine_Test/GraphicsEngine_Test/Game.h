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
	HWND OnInit(const HINSTANCE hInstance, const int nCmdShow,const bool bFullscreen);
	Base::cString GetGameTitle() const; 
	void OnMsgProc(const Graphics::AppMsg & msg);
	void Run();

private:
	Graphics::IBaseControl *		m_pParentControl;
	Graphics::IBaseControl *		m_pWindowControl;
	Graphics::IBaseControl *		m_pLabelControl;

};

#endif // Game_h__