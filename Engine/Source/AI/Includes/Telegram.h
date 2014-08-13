// ***************************************************************
//  Telegram   version:  1.0   Ankur Sheel  date: 05/23/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Telegram_h__
#define Telegram_h__

#include <math.h>

namespace AI
{
	struct Telegram
	{
		unsigned int Sender;
		unsigned int Receiver;
		unsigned int Msg;
		double DispatchTime;
		std::tr1::shared_ptr<void> pExtraInfo;

		Telegram()
		: Sender(0)
		, Receiver(0)
		, Msg(0) 
		, DispatchTime(-1)
		, pExtraInfo(NULL)
		{
		}
		
		Telegram(unsigned int sender, unsigned int Receiver, unsigned int msg,
			double dispatchTime, shared_ptr<void> extraInfo)
		: Sender(sender)
		, Receiver(Receiver)
		, Msg(msg)
		, DispatchTime(dispatchTime)
		, pExtraInfo(extraInfo)
		{
		}
	};

	const double SmallestDelay = 0.25;

	inline bool operator==(const Telegram &t1, const Telegram &t2)
	{
		return ( (t1.Sender == t2.Sender)
			&& (t1.Receiver == t2.Receiver)
			&& (t1.Msg == t2.Msg)
			&& fabs(t1.DispatchTime-t2.DispatchTime) < SmallestDelay);
	}

	inline bool operator<(const Telegram &t1, const Telegram &t2)
	{
		if (t1 == t2)
		{
			return false;
		}

		else
		{
			return  (t1.DispatchTime < t2.DispatchTime);
		}
	}
}
#endif // Telegram_h__