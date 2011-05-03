// ***************************************************************
//  MPongView   version:  1.0   Ankur Sheel  date: 2011/05/02
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef MPongView_h__
#define MPongView_h__

#include "HumanView.h"

class cMPongView : public GameBase::cHumanView
{
public:
	cMPongView();
	~cMPongView();
	HRESULT OnResetDevice();
};
#endif // MPongView_h__
