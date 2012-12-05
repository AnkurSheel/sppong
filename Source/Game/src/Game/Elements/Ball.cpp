// ***************************************************************
//  Ball   version:  1.0   Ankur Sheel  date: 05/13/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "Ball.h"
#include "RandomGenerator.hxx"

using namespace Graphics;
using namespace Base;
using namespace Utilities;
// ***************************************************************
// Constructor
// ***************************************************************
cBall::cBall()
: m_pRandomGenerator(NULL)
{
}
// ***************************************************************

// ***************************************************************
// Destructor
// ***************************************************************
cBall::~cBall()
{
}
// ***************************************************************

// ***************************************************************
// Initialize the ball
// ***************************************************************
void cBall::Init( const cVector3& vInitialPos, const cString & strFilename)
{
	//cPongGameElement::OnBeginInit(strFilename, cVector2((float)m_siTableHeight/30, (float)m_siTableHeight/25));
	//m_pRandomGenerator = IRandomGenerator::CreateRandomGenerator();
	//if (m_pRandomGenerator)
	//{
	//	Log_Write_L1(ILogger::LT_DEBUG, cString(100, "Random Generator created for Ball with seed %u", m_pRandomGenerator->GetRandomSeed()));
	//}
	//m_vSpeed = cVector3((float)m_siTableWidth/4, (float)m_siTableHeight/6, 0.0f);
	//cPongGameElement::OnEndInit(vInitialPos);
}
// ***************************************************************

// ***************************************************************
// Changes the speed in the X direction
// ***************************************************************
void cBall::ChangeSpeedX()
{
	m_vSpeed.x = -m_vSpeed.x;
}
// ***************************************************************

// ***************************************************************
// Changes the speed in the Y direction
// ***************************************************************
void cBall::ChangeSpeedY()
{
	m_vSpeed.y = - m_vSpeed.y;
}
// ***************************************************************

void cBall::OnRestart( const cVector3& vInitialPos )
{
	//cPongGameElement::OnRestart(vInitialPos);
	//int iSpeedDirection = m_pRandomGenerator->Random(2);
	//if (iSpeedDirection == 1)
	//{
	//	m_vSpeed.m_dX = -m_vSpeed.m_dX;
	//}

	//iSpeedDirection = m_pRandomGenerator->Random(2);
	//if (iSpeedDirection == 1)
	//{
	//	m_vSpeed.m_dY = -m_vSpeed.m_dY;
	//}
}
// ***************************************************************

void cBall::OnUpdate(float fElapsedTime)
{
	//m_vPosition += (m_vSpeed * fElapsedTime);
	//UpdatePosition();
}
// ***************************************************************

void cBall::Cleanup()
{
	//SAFE_DELETE(m_pRandomGenerator);
	//cGameElement::Cleanup();
}
// ***************************************************************

cBall * cBall::CastToBall()
{
	return this;
}
// ***************************************************************