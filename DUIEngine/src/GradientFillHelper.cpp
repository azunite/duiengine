#include "duistd.h"
#include "GradientFillHelper.h"

namespace DuiEngine{


	typedef BOOL (WINAPI * FnGradientFill)(HDC, PTRIVERTEX, ULONG, PVOID, ULONG, ULONG);

	BOOL GradientFill2(HDC hDC, PTRIVERTEX pVertices, DWORD nVertices, PVOID pMeshElements, ULONG nMeshElements, ULONG dwMode)
	{
		HMODULE hMod = ::LoadLibrary(_T("msimg32.dll"));
		if (hMod)
		{
			FnGradientFill pfnGradientFill = (FnGradientFill)::GetProcAddress(hMod, "GradientFill");
			if (pfnGradientFill)
				pfnGradientFill(hDC, pVertices, nVertices, pMeshElements, nMeshElements, dwMode);
			::FreeLibrary(hMod);
		}

		return TRUE;
	}

	void GradientFillRectV(HDC hdc, CRect &rcFill, FRG_PARAM params[], int nCount)
	{
		GRADIENT_RECT gRect = {0, 1};
		TRIVERTEX vert[2] = {
			{rcFill.left, rcFill.top, 0, 0, 0, 0}, 
			{rcFill.right, rcFill.top, 0, 0, 0, 0}
		};
		int i = 0;

		for (i = 1; i < nCount && vert[0].y <= rcFill.bottom; i ++)
		{
			vert[0].y = vert[1].y;
			vert[1].y += params[i].lOffset;
			vert[0].Red     = GetRValue(params[i - 1].crColor) << 8;
			vert[0].Green   = GetGValue(params[i - 1].crColor) << 8;
			vert[0].Blue    = GetBValue(params[i - 1].crColor) << 8;
			vert[1].Red     = GetRValue(params[i].crColor) << 8;
			vert[1].Green   = GetGValue(params[i].crColor) << 8;
			vert[1].Blue    = GetBValue(params[i].crColor) << 8;

			HMODULE hMod = ::LoadLibrary(_T("msimg32.dll"));
			if (hMod)
			{
				GradientFill2(hdc, vert, 2, &gRect, 1, GRADIENT_FILL_RECT_V);
			}
		}
	}

	void GradientFillRectH(HDC hdc, CRect &rcFill, FRG_PARAM params[], int nCount)
	{
		GRADIENT_RECT gRect = {0, 1};
		TRIVERTEX vert[2] = {
			{rcFill.left, rcFill.top, 0, 0, 0, 0}, 
			{rcFill.left, rcFill.bottom, 0, 0, 0, 0}
		};
		int i = 0;

		for (i = 1; i < nCount && vert[0].x <= rcFill.right; i ++)
		{
			vert[0].x = vert[1].x;
			vert[1].x += params[i].lOffset;
			vert[0].Red     = GetRValue(params[i - 1].crColor) << 8;
			vert[0].Green   = GetGValue(params[i - 1].crColor) << 8;
			vert[0].Blue    = GetBValue(params[i - 1].crColor) << 8;
			vert[1].Red     = GetRValue(params[i].crColor) << 8;
			vert[1].Green   = GetGValue(params[i].crColor) << 8;
			vert[1].Blue    = GetBValue(params[i].crColor) << 8;
			GradientFill2(hdc, vert, 2, &gRect, 1, GRADIENT_FILL_RECT_H);
		}
	}

	void GradientFillRectV(HDC hdc, CRect &rcFill, COLORREF crTop, COLORREF crBottom)
	{
		FRG_PARAM frgDraw[2] = {
			{0, crTop}, 
			{rcFill.Height(), crBottom}, 
		};

		GradientFillRectV(hdc, rcFill, frgDraw, 2);
	}

	void GradientFillRectH(HDC hdc, CRect &rcFill, COLORREF crLeft, COLORREF crRight)
	{
		FRG_PARAM frgDraw[2] = {
			{0, crLeft}, 
			{rcFill.Width(), crRight}, 
		};

		GradientFillRectH(hdc, rcFill, frgDraw, 2);
	}

}//namespace DuiEngine