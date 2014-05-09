#include "stdafx.h"
#include "BreakoutControls.h"

using namespace Base;
using namespace GameBase;

//  *******************************************************************************************************************
cBreakoutControls::cBreakoutControls(const cString & inFileName)
	: cGameControls(inFileName)
{

}

//  *******************************************************************************************************************
cBreakoutControls::~cBreakoutControls()
{

}

//  *******************************************************************************************************************
void cBreakoutControls::VSetDefaults()
{
	m_KeyMap.clear();

	m_KeyMap[BreakoutControls::MOVE_LEFT] = stGameControl("Move Paddle Left", VK_LEFT);
	m_KeyMap[BreakoutControls::MOVE_RIGHT] = stGameControl("Move Paddle Right", VK_RIGHT);
}