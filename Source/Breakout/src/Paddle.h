// *****************************************************************************
//  Paddle   version:  1.0   Ankur Sheel  date: 2013/04/04
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef Paddle_h__
#define Paddle_h__

#include "BaseEntity.h"

namespace GameBase
{
	template<class BaseType, class SubType> 
	BaseType * GenericObjectCreationFunction();
}

class cPaddle 
	: public GameBase::cBaseEntity
{
public:
	~cPaddle();
	void VInitialize();
	virtual void VOnUpdate();
	void VCleanup();
	cPaddle * CastToPaddle();
	unsigned long VGetHashedID() const { return m_Name.GetHash(); }
	Base::cString VGetName() const { return m_Name.GetString(); }

	public:
		static const Base::cHashedString	m_Name;	///< The component name

private:
	cPaddle();

	template<class BaseType, class SubType> 
	friend BaseType * GameBase::GenericObjectCreationFunction();
};
#endif // Paddle_h__