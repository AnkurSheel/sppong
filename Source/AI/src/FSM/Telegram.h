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


struct Telegram
{
	unsigned int Sender;
	unsigned int Receiver;
	unsigned int Msg;
	double DispatchTime;
	void *ExtraInfo;

};

Telegram::Telegram():Sender(0),
					 Receiver(0),
					 Msg(0),
					 DispatchTime(-1),
					 ExtraInfo(NULL)
{
}
Telegram::Telegram(unsigned int sender, unsigned int Receiver, unsigned int msg, double dispatchTime, void *extraInfo):Sender(sender),
																													   Receiver(Receiver),
																													   Msg(msg),
																													   DispatchTime(dispatchTime),
																													   ExtraInfo(extraInfo)
{
}

template <class T>
inline T DereferenceToType(void* p)
{
	return *(T*)(p);
}

inline bool operator==(const Telegram &t1, const Telegram &t2)
{
	//return ( fabs(t1.DispatchTime-t2.DispatchTime) < SmallestDelay)
	// && (t1.Sender == t2.Sender)
	// && (t1.Receiver == t2.Receiver)
	// && (t1.Msg == t2.Msg);
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
#endif
#endif // Telegram_h__