#include "stdafx.h"
#include "Main.h"
#include "BaseApp.hxx"
#include "Game.hxx"
#include "vld.h"

using namespace GameBase;
using namespace Base;

static IBaseApp * pGame = NULL;

// ***************************************************************
// Main function
// ***************************************************************
int WINAPI WinMain(const HINSTANCE hInstance, 
				   HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, 
				   int nCmdShow)
{
	pGame = IGame::CreateGame("Game");

	pGame->VOnInitialization(hInstance, nCmdShow, "Options.ini");
	pGame->VRun();
	Cleanup() ;

	return 0;
}

// ***************************************************************
void Cleanup() 
{
	SafeDelete(&pGame);
}
