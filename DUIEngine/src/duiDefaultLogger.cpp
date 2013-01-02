/***********************************************************************
    filename:   duiDefaultLogger.cpp
    created:    25/1/2006
    author:     Andrew Zabolotny

    purpose:    Implementation of the DefaultLogger class
*************************************************************************/
/***************************************************************************
 *   Copyright (C) 2004 - 2006 Paul D Turner & The DuiEngine Development Team
 *
 *   Permission is hereby granted, free of charge, to any person obtaining
 *   a copy of this software and associated documentation files (the
 *   _T("Software")), to deal in the Software without restriction, including
 *   without limitation the rights to use, copy, modify, merge, publish,
 *   distribute, sublicense, and/or sell copies of the Software, and to
 *   permit persons to whom the Software is furnished to do so, subject to
 *   the following conditions:
 *
 *   The above copyright notice and this permission notice shall be
 *   included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED _T("AS IS"), WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 ***************************************************************************/
#include "duistd.h"
#include "DuiDefaultLogger.h"
#include <ctime>
#include <iomanip>
#include <stdio.h>
#include <tchar.h>


// Start of DuiEngine namespace section
namespace DuiEngine
{

    /*************************************************************************
        Constructor
    *************************************************************************/
    DefaultLogger::DefaultLogger(void) :
            d_caching(true),d_pFile(NULL)
    {
        // create log header
        logEvent(_T("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"));
        logEvent(_T("+                     DuiEngine - Event log                                   +"));
        logEvent(_T("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n"));
        TCHAR addr_buff[32];
        _stprintf(addr_buff, _T("(%p)"), static_cast<void*>(this));
		logEvent(_T("DuiEngine::Logger singleton created. "));
		logEvent(addr_buff);
    }

    /*************************************************************************
        Destructor
    *************************************************************************/
    DefaultLogger::~DefaultLogger(void)
    {
        if (d_pFile)
        {
            TCHAR addr_buff[32];
            _stprintf(addr_buff, _T("(%p)"), static_cast<void*>(this));
            logEvent(_T("DuiEngine::Logger singleton destroyed. "));
			logEvent(addr_buff);
			fclose(d_pFile);
        }
    }

    /*************************************************************************
        Logs an event
    *************************************************************************/
    void DefaultLogger::logEvent(LPCTSTR message, LoggingLevel level /* = Standard */)
    {
        time_t  et;
        time(&et);
        tm* etm = localtime(&et);

        if (etm)
        {
            // clear sting stream
			CString d_strbuf=_T("");

            // write date
//             d_workstream << setfill('0') << setw(2) << etm->tm_mday << '/' <<
//             setfill('0') << setw(2) << 1 + etm->tm_mon << '/' <<
//             setw(4) << (1900 + etm->tm_year) << ' ';

            // write time
//             d_workstream << setfill('0') << setw(2) << etm->tm_hour << ':' <<
//             setfill('0') << setw(2) << etm->tm_min << ':' <<
//             setfill('0') << setw(2) << etm->tm_sec << ' ';

            // write event type code
            switch(level)
            {
            case Errors:
                d_strbuf+= _T("(Error)\t");
                break;

            case Warnings:
                d_strbuf+= _T("(Warn)\t");
                break;

            case Standard:
                d_strbuf+= _T("(Std) \t");
                break;

            case Informative:
                d_strbuf+= _T("(Info) \t");
                break;

            case Insane:
                d_strbuf+= _T("(Insan)\t");
                break;

            default:
                d_strbuf+= _T("(Unkwn)\t");
                break;
            }

            d_strbuf+= message;
			d_strbuf+=_T("\n");

            if (d_caching)
            {
                d_cache.push_back(STL_NS::make_pair(d_strbuf, level));
            }
            else if (d_level >= level)
            {
                // write message
				_ftprintf(d_pFile,(LPCTSTR)d_strbuf);
				fflush(d_pFile);
            }
        }
    }


    void DefaultLogger::setLogFilename(LPCTSTR filename, bool append)
    {
		if(d_pFile)
		{
			fclose(d_pFile);
			d_pFile=NULL;
		}
		d_pFile=_tfopen(filename,append?_T("a+"):_T("w"));


        // write out cached log strings.
        if (d_caching)
        {
            d_caching = false;

            STL_NS::vector<STL_NS::pair<CString, LoggingLevel> >::iterator iter = d_cache.begin();

            while (iter != d_cache.end())
            {
                if (d_level >= (*iter).second)
                {
					_ftprintf(d_pFile,(LPCTSTR)(*iter).first);
					fflush(d_pFile);
                }

                ++iter;
            }

            d_cache.clear();
        }
    }

} // End of  DuiEngine namespace section
