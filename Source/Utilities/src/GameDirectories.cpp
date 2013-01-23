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

static cGameDirectories gameDirectories;

// *****************************************************************************
const cGameDirectories & cGameDirectories::GameDirectories()
{
	return gameDirectories;
}

// *****************************************************************************
void cGameDirectories::Initialize(const IParamLoader * const pParamLoader)
{
	if (pParamLoader)
	{
		gameDirectories.strMediaDirectory = pParamLoader->VGetParameterValueAsString("-MediaDirectory", "");
		gameDirectories.strFontDirectory = pParamLoader->VGetParameterValueAsString("-FontDirectory", "");
		gameDirectories.strShaderDirectory = pParamLoader->VGetParameterValueAsString("-ShaderDirectory", "");
		gameDirectories.strSpriteDirectory = pParamLoader->VGetParameterValueAsString("-SpriteDirectory", "");
		gameDirectories.strSoundDirectory = pParamLoader->VGetParameterValueAsString("-SoundDirectory", "");
	}

}