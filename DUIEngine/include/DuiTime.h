#ifndef DuiTime_h__
#define DuiTime_h__

#pragma  once

#include <time.h>

namespace DuiEngine
{
class DUI_EXP CTime
{
public:
	static CTime GetCurrentTime() throw();
	CTime(__time64_t tm=0):m_time(tm){}

	__time64_t	GetTime() const throw();
	struct tm* GetLocalTm(struct tm* ptm) const;

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	int GetHour() const;
	int GetMinute() const;
	int GetSecond() const;
	int GetDayOfWeek() const;

	CTime& operator=( __time64_t time ) throw();

	bool operator==( CTime time ) const throw();
	bool operator!=( CTime time ) const throw();
	bool operator<( CTime time ) const throw();
	bool operator>( CTime time ) const throw();
	bool operator<=( CTime time ) const throw();
	bool operator>=( CTime time ) const throw();
protected:

	__time64_t m_time;
};

inline struct tm* CTime::GetLocalTm(struct tm* ptm) const
{
	// Ensure ptm is valid
	DUIASSERT( ptm != NULL );

	if (ptm != NULL)
	{
		struct tm ptmTemp;
		errno_t err = _localtime64_s(&ptmTemp, &m_time);

		if (err != 0)
		{
			return NULL;    // indicates that m_time was not initialized!
		}

		*ptm = ptmTemp;
		return ptm;
	}

	return NULL;
}

inline CTime CTime::GetCurrentTime() throw()
{
	return( CTime( ::_time64( NULL ) ) );
}

inline __time64_t CTime::GetTime() const throw()
{
	return( m_time );
}

inline int CTime::GetYear() const
{ 
	struct tm ttm;
	struct tm * ptm;

	ptm = GetLocalTm(&ttm);
	return ptm ? (ptm->tm_year) + 1900 : 0 ; 
}

inline int CTime::GetMonth() const
{ 
	struct tm ttm;
	struct tm * ptm;

	ptm = GetLocalTm(&ttm);
	return ptm ? ptm->tm_mon + 1 : 0;
}

inline int CTime::GetDay() const
{
	struct tm ttm;
	struct tm * ptm;

	ptm = GetLocalTm(&ttm);
	return ptm ? ptm->tm_mday : 0 ; 
}

inline int CTime::GetHour() const
{
	struct tm ttm;
	struct tm * ptm;

	ptm = GetLocalTm(&ttm);
	return ptm ? ptm->tm_hour : -1 ; 
}

inline int CTime::GetMinute() const
{
	struct tm ttm;
	struct tm * ptm;

	ptm = GetLocalTm(&ttm);
	return ptm ? ptm->tm_min : -1 ; 
}

inline int CTime::GetSecond() const
{ 
	struct tm ttm;
	struct tm * ptm;

	ptm = GetLocalTm(&ttm);
	return ptm ? ptm->tm_sec : -1 ;
}

inline int CTime::GetDayOfWeek() const
{ 
	struct tm ttm;
	struct tm * ptm;

	ptm = GetLocalTm(&ttm);
	return ptm ? ptm->tm_wday + 1 : 0 ;
}

inline CTime& CTime::operator=( __time64_t time ) throw()
{
	m_time = time;

	return( *this );
}

inline bool CTime::operator==( CTime time ) const throw()
{
	return( m_time == time.m_time );
}

inline bool CTime::operator!=( CTime time ) const throw()
{
	return( m_time != time.m_time );
}

inline bool CTime::operator<( CTime time ) const throw()
{
	return( m_time < time.m_time );
}

inline bool CTime::operator>( CTime time ) const throw()
{
	return( m_time > time.m_time );
}

inline bool CTime::operator<=( CTime time ) const throw()
{
	return( m_time <= time.m_time );
}

inline bool CTime::operator>=( CTime time ) const throw()
{
	return( m_time >= time.m_time );
}
}//end of namespace DuiEngine


#endif // DuiTime_h__
