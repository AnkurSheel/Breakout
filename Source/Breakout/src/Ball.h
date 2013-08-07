// *****************************************************************************
//  Ball   version:  1.0   Ankur Sheel  date: 2013/05/13
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef Ball_h__
#define Ball_h__

#include "BaseEntity.h"

namespace GameBase
{
	template<class BaseType, class SubType> 
	BaseType * GenericObjectCreationFunction();
}

class cBall 
	: public GameBase::cBaseEntity
{
public:
	~cBall();
	void VInitialize();
	virtual void VOnUpdate(const float deltaTime);
	void VCleanup();
	cBall * CastToBall();
	unsigned long VGetHashedID() const { return m_Name.GetHash(); }
	Base::cString VGetName() const { return m_Name.GetString(); }

	public:
		static const Base::cHashedString	m_Name;	///< The component name

private:
	cBall();

	template<class BaseType, class SubType> 
	friend BaseType * GameBase::GenericObjectCreationFunction();
};
#endif // Ball_h__