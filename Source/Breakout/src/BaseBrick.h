//  *******************************************************************************************************************
//  BaseBrick   version:  1.0   Ankur Sheel  date: 2013/05/14
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef BaseBrick_h__
#define BaseBrick_h__

#include "BaseEntity.h"

namespace Base
{
	template<class BaseType, class SubType> 
	BaseType * GenericObjectCreationFunction();
}

class cBaseBrick 
	: public GameBase::cBaseEntity
{
public:
	~cBaseBrick();
	void VInitialize();

public:
	static const Base::cHashedString	m_Name;	///< The component name

private:
	cBaseBrick();
	virtual void VOnUpdate(const float deltaTime);
	void VCleanup();
	cBaseBrick * CastToBaseBrick();
	Base::cHashedString VGetType() const { return m_Name; }
	unsigned long VGetHashedID() const { return m_Name.GetHash(); }
	Base::cString VGetName() const { return m_Name.GetString(); }
	void VOnCollided(IBaseEntity * const pEntityCollider);

private:
	template<class BaseType, class SubType> 
	friend BaseType * Base::GenericObjectCreationFunction();
};
#endif // BaseBrick_h__