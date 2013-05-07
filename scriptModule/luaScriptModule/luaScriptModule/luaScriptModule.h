#pragma  once

#ifdef LUASCRIPTMODULE_EXPORTS
#define LUASCRIPTMODULE_API __declspec(dllexport)
#else
#define LUASCRIPTMODULE_API __declspec(dllimport)
#endif

#include <DuiScriptModule.h>

extern "C"
{
#include "../lua-5.1/lua.h"
#include "../lua-5.1/lualib.h"
#include "../lua-5.1/lauxlib.h"
};

// 此类是从 luaScriptModule.dll 导出的
class LUASCRIPTMODULE_API CLuaScriptModule : public DuiEngine::IScriptModule{
public:
	CLuaScriptModule(void);

	~CLuaScriptModule();

	virtual void * GetScriptEngine () {return d_state;}

	virtual int loadScriptFile(LPCSTR pszScriptFile);

	virtual int loadScriptString(LPCSTR pszScriptStr);

	virtual	void	executeScriptFile(LPCSTR pszScriptFile);


	/*!
	\brief
		Execute a scripted global 'event handler' function.  The function should take some kind of EventArgs like parameter
		that the concrete implementation of this function can create from the passed EventArgs based object.  The function
		should not return anything.

	\param handler_name
		String object holding the name of the scripted handler function.

	\param CDuiWindow *pSender
		CDuiWindow based object that should be passed, by any appropriate means, to the scripted function.

	\param LPNMHDR pNmhdr
		notify message 

	\return
		- true if the event was handled.
		- false if the event was not handled.
	*/
	virtual	bool	executeScriptedEventHandler(LPCSTR handler_name, DuiEngine::CDuiWindow *pSender, LPNMHDR pNmhdr);


    /*!
    \brief
        Execute script code contained in the given String object.

    \param str
        String object holding the valid script code that should be executed.

    \return
        Nothing.
    */
    virtual void executeString(LPCSTR str);



    /*!
    \brief
        Return identification string for the ScriptModule.  If the internal id string has not been
        set by the ScriptModule creator, a generic string of "Unknown scripting module" will be returned.

    \return
        String object holding a string that identifies the ScriptModule in use.
    */
    virtual LPCSTR getIdentifierString() const;

    /*!
    \brief
            Subscribes or unsubscribe the named Event to a scripted function

    \param target
            The target EventSet for the subscription.

    \param uEvent
            Event ID to subscribe to.

    \param subscriber_name
            String object containing the name of the script function that is to be subscribed to the Event.

    \return 
    */
    virtual bool subscribeEvent(DuiEngine::CDuiWindow* target, UINT uEvent, LPCSTR subscriber_name);
	virtual bool unsubscribeEvent(DuiEngine::CDuiWindow* target, UINT uEvent, LPCSTR subscriber_name );
protected:
	lua_State * d_state;
};
