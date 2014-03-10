// *****************************************************************************
//  LifeLostEventData version:  1.0   Ankur Sheel  date: 2013/08/07
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef LifeLostEventData_h__
#define LifeLostEventData_h__

#include "BaseEventData.h"

namespace GameBase
{
	class cLifeLostEventData
		: public GameBase::cBaseEventData
	{
	public:
		cLifeLostEventData();
		~cLifeLostEventData();
		unsigned long VGetHashedID() const { return m_Name.GetHash(); }
		virtual Base::cString VGetName() const { return m_Name.GetString(); }
	
	public:
		static Base::cHashedString m_Name;
	};
}
#endif //LifeLostEventData_h__