// *****************************************************************************
//  Ball   version:  1.0   Ankur Sheel  date: 2013/05/13
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef Ball_h__
#define Ball_h__

#include "BaseEntity.h"

namespace Base
{
	class cVector3;

	template<class BaseType, class SubType> 
	BaseType * GenericObjectCreationFunction();
}

namespace GameBase
{
	class cPhysicsComponent;
}

namespace Utilities
{
	class IRandomGenerator;
}

class cBall 
	: public GameBase::cBaseEntity
{
public:
	~cBall();
	void ApplyForce(const Base::cVector3 & direction);

public:
	static const Base::cHashedString	m_Name;	///< The component name

private:
	cBall();
	void VInitialize();
	virtual void VOnUpdate(const float deltaTime);
	void VCleanup();
	cBall * CastToBall();
	Base::cHashedString VGetType() const { return m_Name; }
	unsigned long VGetHashedID() const { return m_Name.GetHash(); }
	Base::cString VGetName() const { return m_Name.GetString(); }
	void VOnCollided(IBaseEntity * const pEntityCollider);

private:
	GameBase::cPhysicsComponent *	m_pPhysicsComponent;
	Utilities::IRandomGenerator *	m_pRandomGenerator;

	template<class BaseType, class SubType> 
	friend BaseType * Base::GenericObjectCreationFunction();
};
#endif // Ball_h__