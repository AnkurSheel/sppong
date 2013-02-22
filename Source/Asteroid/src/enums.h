#ifndef enums_h__
#define enums_h__

enum GAMESOUNDS
{
	GS_UNKNOWN = -1,
	GS_BALL_WALL_COLLISION,
	GS_BALL_PADDLE_COLLISION,
	GS_WIN,
	GS_MAIN_MENU_MUSIC,
	GS_TOTAL
};

enum ShipMovement
{
	SM_MOVE_FWD,
	SM_MOVE_BK,
	SM_ROTATE_LEFT,
	SM_ROTATE_RIGHT,
};

#endif // enums_h__