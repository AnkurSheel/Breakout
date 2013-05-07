// *****************************************************************************
//  BreakOutEntityFactory   version:  1.0   Ankur Sheel  date: 2013/05/06
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#ifndef BreakOutEntityFactory_h__
#define BreakOutEntityFactory_h__

#include "EntityFactory.h"

namespace GameBase
{
	class IBaseEntity;
}

class cBreakOutEntityFactory
	: public GameBase::cEntityFactory
{
public:
	cBreakOutEntityFactory();
	~cBreakOutEntityFactory();
	void RegisterEntities();
	GameBase::IBaseEntity * VCreateEntity(const Base::cHashedString & Type);
};

#endif // BreakOutEntityFactory_h__
