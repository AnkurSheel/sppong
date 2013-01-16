#ifndef GameOptions_h__
#define GameOptions_h__

namespace Utilities
{
	class IParamLoader;
}

namespace GameBase
{
	class cGameOptions
		: public Base::cNonCopyable
	{
	public:
		cGameOptions();
		~cGameOptions();
		void Init(const Base::cString & strPlayerOptionsFile);

	public:
		bool	m_bFullScreen;
		int		m_iWidth;
		int		m_iHeight;

		int		m_iSFXVolume;
		int		m_iMusicVolume;
	};
}
#endif GameOptions_h__
