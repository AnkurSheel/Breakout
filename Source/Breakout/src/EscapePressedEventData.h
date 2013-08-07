// *****************************************************************************
//  EscapePressedEventData version:  1.0   Ankur Sheel  date: 2013/08/07
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef EscapePressedEventData_h__
#define EscapePressedEventData_h__

#include "BaseEventData.h"

namespace GameBase
{
	class cEscapePressedEventData
		: public GameBase::cBaseEventData
	{
	public:
		cEscapePressedEventData();
		~cEscapePressedEventData();
		unsigned long VGetHashedID() const { return m_Name.GetHash(); }
		virtual Base::cString VGetName() const { return m_Name.GetString(); }
	
	public:
		static Base::cHashedString m_Name;
	};
}
#endif //EscapePressedEventData_h__