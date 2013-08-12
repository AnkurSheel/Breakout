// *****************************************************************************
//  Paddle   version:  1.0   Ankur Sheel  date: 2013/04/04
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef Paddle_h__
#define Paddle_h__

#include "BaseEntity.h"
#include "vector3.h"

namespace GameBase
{
	template<class BaseType, class SubType> 
	BaseType * GenericObjectCreationFunction();

	class cPhysicsComponent;
}

class cPaddle 
	: public GameBase::cBaseEntity
{
public:
	~cPaddle();

public:
	static const Base::cHashedString	m_Name;	///< The component name

private:
	cPaddle();
	void VInitialize();
	virtual void VOnUpdate(const float deltaTime);
	void VCleanup();
	cPaddle * CastToPaddle();
	Base::cHashedString VGetType() const { return m_Name; }
	unsigned long VGetHashedID() const { return m_Name.GetHash(); }
	Base::cString VGetName() const { return m_Name.GetString(); }
	void VHandleInput(const unsigned int CharID, const float deltaTime);
	void VOnCollided(IBaseEntity * const pEntityCollider);

private:
	Base::cVector3					m_ForceDirection;
	GameBase::cPhysicsComponent *	m_pPhysicsComponent;

private:
	template<class BaseType, class SubType> 
	friend BaseType * GameBase::GenericObjectCreationFunction();
};
#endif // Paddle_h__