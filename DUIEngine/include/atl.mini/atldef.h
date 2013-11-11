#pragma  once

#define HIMETRIC_PER_INCH   2540
#define MAP_PIX_TO_LOGHIM(x,ppli)   MulDiv(HIMETRIC_PER_INCH, (x), (ppli))
#define MAP_LOGHIM_TO_PIX(x,ppli)   MulDiv((ppli), (x), HIMETRIC_PER_INCH)

#undef ATLENSURE_THROW
#define ATLENSURE_THROW(a,b)
#define ATLTRACENOTIMPL(funcname)   return E_NOTIMPL

#ifndef ATLASSERT
#define ATLASSERT DUIASSERT
#endif // ATLASSERT

#ifndef ATLASSUME
#define ATLASSUME(expr) do { ATLASSERT(expr); __analysis_assume(!!(expr)); } while(0)
#endif // ATLASSUME

#define ATL_NO_VTABLE	DUI_NO_VTABLE
