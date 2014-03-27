//  *******************************************************************************************************************
//  BreakoutConfig   version:  1.0   Ankur Sheel  date: 2014/03/27
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef BreakoutConfig_h__
#define BreakoutConfig_h__

#include "Config.h"

class cGame;

namespace GameBase
{
	class IBaseApp;
}

class cBreakoutConfig 
	: public GameBase::cConfig
{
public:
	cBreakoutConfig();
	~cBreakoutConfig();

private:
	void VInitialize(const Base::cString & FileName);

private:
	int	m_Lives;
};
#endif // BreakoutConfig_h__