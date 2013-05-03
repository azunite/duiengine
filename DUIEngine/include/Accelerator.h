#pragma once

#include "wtl.mini/duistr.h"

namespace DuiEngine
{

	class DUI_EXP CAccelerator
	{
	public:
		CAccelerator(void);
		~CAccelerator(void);

		CDuiStringT GetKeyName(WORD vk);

		CDuiStringT FormatHotkey();

		WORD GetModifier() const {return m_wModifier;}
		WORD GetKey() const {return m_wVK;}
	protected:
		WORD 	m_wModifier;
		WORD	m_wVK;
	};

	// 想要注册键盘加速键的类需要实现本接口.
	class DUI_EXP CAcceleratorTarget
	{
	public:
		// 如果加速键被处理, 方法应该返回true.
		virtual bool OnAcceleratorPressed(const CAccelerator& accelerator) = 0;

	protected:
		virtual ~CAcceleratorTarget() {}
	};

}//end of namespace DuiEngine
