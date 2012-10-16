#pragma once
#include "duisingleton.h"

namespace DuiEngine{

class DUI_EXP DuiSystem :
	public Singleton<DuiSystem>
{
public:
	DuiSystem(HINSTANCE hInst,LPCTSTR pszHostClassName=_T("DuiHostWnd"));
	~DuiSystem(void);

	void LockSharePtr( void * pObj );
	void * GetSharePtr();
	void * ReleaseSharePtr();

	HINSTANCE GetInstance(){return m_hInst;}
	ATOM GetHostWndAtom(){return m_atomWnd;}
protected:
	void createSingletons();
	void destroySingletons();
	void * m_p;
	CRITICAL_SECTION m_cs;

	ATOM			m_atomWnd;

	HINSTANCE m_hInst;
};

}//namespace DuiEngine