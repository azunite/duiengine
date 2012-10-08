#include "duistd.h"
#include "duiwndrichtxt.h"

namespace DuiEngine{

//////////////////////////////////////////////////////////////////////////
// Rich Text Control
//

CDuiRichText::CDuiRichText()
: m_XmlElemChildren("")
, m_dwFont(0)
, m_bLinkLoaded(FALSE)
, m_posHover(NULL)
, m_posPushDown(NULL)
{

}

CDuiRichText::~CDuiRichText()
{
}

BOOL CDuiRichText::Load(TiXmlElement* pTiXmlElem)
{
	if (!CDuiWindow::Load(pTiXmlElem))
		return FALSE;


	return LoadChildren(pTiXmlElem);
}

BOOL CDuiRichText::LoadChildren(TiXmlElement* pTiXmlElem)
{
	m_lstLink.RemoveAll();
	m_bLinkLoaded = FALSE;
	m_posHover = NULL;

	if(pTiXmlElem) m_XmlElemChildren = *pTiXmlElem;

	return TRUE;
}

BOOL CDuiRichText::OnDuiSetCursor(const CPoint &pt)
{
	::SetCursor(::LoadCursor(NULL, (0 != m_posHover) ? IDC_HAND : IDC_ARROW));
	return TRUE;
}


void CDuiRichText::OnWindowPosChanged(LPDUIWNDPOS lpWndPos)
{
	__super::OnWindowPosChanged(lpWndPos);

	m_lstLink.RemoveAll();
	m_bLinkLoaded = FALSE;
	m_posHover = NULL;
}

void CDuiRichText::OnPaint(CDCHandle dc)
{
	HFONT hftOld = dc.SelectFont(DuiFontPool::getSingleton().GetFont(LOWORD(m_dwFont)));

	CRect rcDraw = m_rcWindow;
	CRgn rgnDraw;

	rcDraw.DeflateRect(m_style.m_nMarginX, m_style.m_nMarginY);
	//         rgnDraw.CreateRectRgnIndirect(rcDraw);

	int nDC = dc.SaveDC();
	//         dc.SelectClipRgn(rgnDraw);

	POINT pt = rcDraw.TopLeft();

	_DrawElement(dc, &m_XmlElemChildren, LOWORD(m_dwFont), pt);

	_DrawLinks(dc);

	dc.RestoreDC(nDC);

	dc.SelectFont(hftOld);

	m_bLinkLoaded = TRUE;
}

void CDuiRichText::OnMouseMove(UINT nFlags, CPoint point)
{
	POSITION posHover = NULL;
	POSITION pos = m_lstLink.GetHeadPosition();

	while (pos)
	{
		posHover = pos;
		const _LinkInfo& link = m_lstLink.GetNext(pos);

		if (link.rcLink.PtInRect(point))
		{
			if (m_posHover != posHover)
			{
				if (m_posHover)
				{
					_LinkInfo& linkOldHover = m_lstLink.GetAt(m_posHover);
					NotifyInvalidateRect(linkOldHover.rcLink);
				}

				m_posHover = posHover;
				NotifyInvalidateRect(link.rcLink);
			}

			return;
		}
	}

	OnMouseLeave();
}

void CDuiRichText::OnMouseLeave()
{
	if (m_posHover)
	{
		const _LinkInfo& linkOldHover = m_lstLink.GetAt(m_posHover);
		NotifyInvalidateRect(linkOldHover.rcLink);
	}

	m_posHover = NULL;
}

void CDuiRichText::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_posHover)
	{
		m_posPushDown = m_posHover;
	}
}

void CDuiRichText::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_posPushDown && m_posHover == m_posPushDown)
	{
		const _LinkInfo& link = m_lstLink.GetAt(m_posPushDown);

		DUINMCOMMAND nms;
		nms.hdr.code = DUINM_COMMAND;
		nms.hdr.hwndFrom = NULL;
		nms.hdr.idFrom = GetCmdID();
		nms.uItemID = link.uCmdID;
		nms.szItemClass = GetObjectClass();

		LRESULT lRet =DuiNotify((LPNMHDR)&nms);
	}

	m_posPushDown = NULL;
}

void CDuiRichText::_AddLink(CDCHandle &dc, TiXmlElement *pElemChild, POINT &pt)
{
	_LinkInfo newLink;

	HFONT hftOld = NULL;

	if (NULL != m_styleLink.m_ftText)
		hftOld = dc.SelectFont(m_styleLink.m_ftText);

	newLink.strText = CA2T(pElemChild->GetText(), CP_UTF8);

	SIZE sz = {0, 0};

	dc.GetTextExtent(newLink.strText, newLink.strText.GetLength(), &sz);

	if (NULL != m_styleLink.m_ftText)
		dc.SelectFont(hftOld);

	if (pt.x + sz.cx > m_rcWindow.right - m_style.m_nMarginX)
	{
		pt.x = m_rcWindow.left + m_style.m_nMarginX;
		pt.y += m_style.m_nLineSpacing;
	}

	newLink.rcLink.SetRect(pt.x, pt.y, pt.x + sz.cx, pt.y + sz.cy);

	pt.x = newLink.rcLink.right + m_style.m_nSpacing;

	pElemChild->Attribute("id", (int *)&newLink.uCmdID);

	m_lstLink.AddTail(newLink);
}

void CDuiRichText::_DrawElement(CDCHandle &dc, TiXmlElement *pElemChild, WORD wFont, POINT &pt)
{
	TiXmlNode *pNodeChild = NULL;

	WORD wNewFont = wFont;
	COLORREF crTextOld = CLR_INVALID;

	BOOL bOnlyCalcPoint = FALSE;

	if (0 == _stricmp(pElemChild->Value(), "br"))
	{
		pt.x = m_rcWindow.left + m_style.m_nMarginX;
		pt.y += m_style.m_nLineSpacing;
	}
	else if (0 == _stricmp(pElemChild->Value(), "b"))
	{
		wNewFont = wFont | DUIF_BOLD;
	}
	else if (0 == _stricmp(pElemChild->Value(), "i"))
	{
		wNewFont = wFont | DUIF_ITALIC;
	}
	else if (0 == _stricmp(pElemChild->Value(), "u"))
	{
		wNewFont = wFont | DUIF_UNDERLINE;
	}
	else if (0 == _stricmp(pElemChild->Value(), "c"))
	{
		COLORREF clrText = CDuiObject::HexStringToColor(pElemChild->Attribute("color"));
		crTextOld = dc.SetTextColor( clrText );
		if( crTextOld == CLR_INVALID )
		{
			crTextOld = 0;
		}
	}
	else if (0 == _stricmp(pElemChild->Value(), "a"))
	{
		if (!m_bLinkLoaded)
		{
			_AddLink(dc, pElemChild, pt);

			return;
		}

		bOnlyCalcPoint = TRUE;
	}

	dc.SelectFont(DuiFontPool::getSingleton().GetFont(wNewFont));

	while (pNodeChild = pElemChild->IterateChildren(pNodeChild))
	{
		_DrawNode(dc, pNodeChild, wNewFont, pt, bOnlyCalcPoint);
	}

	dc.SelectFont(DuiFontPool::getSingleton().GetFont(wFont));

	if (CLR_INVALID != crTextOld)
		dc.SetTextColor(crTextOld);
}

void CDuiRichText::_DrawLinks(CDCHandle &dc)
{
	BOOL bDisabled = IsDisabled(TRUE);
	BOOL bHover = FALSE;
	POSITION pos = m_lstLink.GetHeadPosition();

	if (NULL != m_styleLink.m_ftText)
		dc.SelectFont(m_styleLink.m_ftText);

	if (bDisabled)
	{
		if (CLR_INVALID != m_styleLink.m_crDisabledText)
			dc.SetTextColor(m_styleLink.m_crDisabledText);
	}
	else
	{
		if (CLR_INVALID != m_styleLink.m_crText)
			dc.SetTextColor(m_styleLink.m_crText);
	}

	while (pos)
	{
		if (pos == m_posHover)
		{
			if (NULL != m_styleLink.m_ftText)
				dc.SelectFont(m_styleLink.m_ftHover);

			if (CLR_INVALID != m_styleLink.m_crText)
				dc.SetTextColor(m_styleLink.m_crHoverText);

			bHover = TRUE;
		}

		const _LinkInfo& link = m_lstLink.GetNext(pos);

		CGdiAlpha::TextOut(dc,link.rcLink.left, link.rcLink.top, link.strText);

		if (bHover)
		{
			if (NULL != m_styleLink.m_ftText)
				dc.SelectFont(m_styleLink.m_ftText);

			if (CLR_INVALID != m_styleLink.m_crText)
				dc.SetTextColor(m_styleLink.m_crText);

			bHover = FALSE;
		}
	}
}

void CDuiRichText::_DrawNode(CDCHandle &dc, TiXmlNode *pNodeChild, WORD wFont, POINT &pt, BOOL bOnlyCalcPoint/* = FALSE*/)
{
	switch (pNodeChild->Type())
	{
	case TiXmlNode::TINYXML_ELEMENT:
		{
			TiXmlElement *pElemChild = pNodeChild->ToElement();

			_DrawElement(dc, pElemChild, wFont, pt);
		}
		break;

	case TiXmlNode::TINYXML_TEXT:
		{
			CString strText = CA2T(pNodeChild->Value(), CP_UTF8);
			LPCTSTR lpszDraw = strText;
			int nFullLength = strText.GetLength(), nLength = 0;

			while (TRUE)
			{
				nLength = nFullLength - nLength;
				nFullLength = nLength;
				SIZE sz = {0, 0};

				while (nLength > 0)
				{
					dc.GetTextExtent(lpszDraw, nLength, &sz);
					if (pt.x + sz.cx <= m_rcWindow.right - m_style.m_nMarginX)
						break;

					nLength --;
				}

				if (!bOnlyCalcPoint)
					CGdiAlpha::TextOut(dc,pt.x, pt.y, lpszDraw, nLength);

				if (nFullLength == nLength)
				{
					pt.x += sz.cx;
					break;
				}

				pt.x = m_rcWindow.left + m_style.m_nMarginX;
				pt.y += m_style.m_nLineSpacing;
				lpszDraw += nLength;
			}

			pt.x += m_style.m_nSpacing;
		}
		break;
	}
}

}//namespace DuiEngine