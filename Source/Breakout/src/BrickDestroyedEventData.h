//  *******************************************************************************************************************
//  BrickDestroyedEventData version:  1.0   Ankur Sheel  date: 2014/04/01
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef BrickDestroyedEventData_h__
#define BrickDestroyedEventData_h__

#include "BaseEventData.h"

namespace GameBase
{
	class IBaseEntity;
}

class cBrickDestroyedEventData
	: public GameBase::cBaseEventData
{
public:
	cBrickDestroyedEventData();
	~cBrickDestroyedEventData();
	unsigned long VGetHashedID() const { return m_Name.GetHash(); }
	virtual Base::cString VGetName() const { return m_Name.GetString(); }

public:
	static Base::cHashedString m_Name;
	GameBase::IBaseEntity * m_pDestroyedEntity;
};

#endif //BrickDestroyedEventData_h__