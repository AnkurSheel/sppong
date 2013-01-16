#ifndef GameOptions_h__
#define GameOptions_h__

namespace Utilities
{
	class IParamLoader;
}

namespace GameBase
{
	struct stGameOptions
	{
		bool	bFullScreen;	/*!< True if in fullscreen mode */
		int		iWidth;			/*!< Window/Fullscreen width */
		int		iHeight;		/*!< Window/Fullscreen height */

		int		iSFXVolume;
		int		iMusicVolume;
	};
}
#endif GameOptions_h__
