#pragma once
#include "duisingleton.h"

namespace DuiEngine{

class DuiSystem :
	public Singleton<DuiSystem>
{
public:
	DuiSystem(void);
	~DuiSystem(void);

protected:
	void createSingletons();
	void destroySingletons();
};

}//namespace DuiEngine