// *****************************************************************************
//  Paddle   version:  1.0   Ankur Sheel  date: 2013/04/04
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef Paddle_h__
#define Paddle_h__

#include "BaseEntity.h"

class cPaddle 
	: public GameBase::cBaseEntity
{
public:
	cPaddle(const Base::cString & strName);
	~cPaddle();
	void VInitialize();
	virtual void VOnUpdate();
	void VCleanup();
	cPaddle * CastToPaddle();
};
#endif // Paddle_h__