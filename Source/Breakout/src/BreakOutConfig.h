// *****************************************************************************
//  BreakOutConfig   version:  1.0   Ankur Sheel  date: 2013/05/06
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#ifndef BreakOutConfig_h__
#define BreakOutConfig_h__

#include "Config.h"

namespace GameBase
{
	class cEntityDef;
}

namespace GameBase
{
	class cBreakOutConfig
		: public GameBase::cConfig
	{
	public:
		cBreakOutConfig();
		~cBreakOutConfig();
		void VInitialize(const Base::cString & FileName);
	};

}
#endif // BreakOutConfig_h__
