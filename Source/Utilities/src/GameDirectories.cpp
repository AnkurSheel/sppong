// *****************************************************************************
//  GameDirectories   version:  1.0   Ankur Sheel  date: 2013/01/22
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "GameDirectories.h"
#include "ParamLoaders.hxx"

using namespace Utilities;

static stGameDirectories gameDirectories;

// *****************************************************************************
const stGameDirectories & stGameDirectories::GameDirectories()
{
	return gameDirectories;
}

// *****************************************************************************
void stGameDirectories::Initialize(const IParamLoader * const pParamLoader)
{
	if (pParamLoader)
	{
		gameDirectories.strMediaDirectory = pParamLoader->VGetParameterValueAsString("-MediaDirectory", "");
		gameDirectories.strFontDirectory = pParamLoader->VGetParameterValueAsString("-FontDirectory", "");
	}
}