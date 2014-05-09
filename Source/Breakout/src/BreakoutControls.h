//  *******************************************************************************************************************
//  BreakoutControls version: 1.0 Ankur Sheel  date: 2014/05/09
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#include "GameControls.h"

namespace BreakoutControls
{
	enum Enum
	{
		MOVE_LEFT,
		MOVE_RIGHT,
	};
}

class cBreakoutControls
	: public GameBase::cGameControls
{
public:
	cBreakoutControls(const Base::cString & inFileName);
	~cBreakoutControls();
	void VSetDefaults();
};