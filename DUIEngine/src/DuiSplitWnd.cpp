#include "duistd.h"
#include "DuiSplitWnd.h"

namespace DuiEngine
{

#define DEF_SEPSIZE	5


CDuiSplitPane::CDuiSplitPane():m_nPriority(0),m_nSizeIdeal(20),m_nSizeMin(0)
{

}


//////////////////////////////////////////////////////////////////////////
CDuiSplitWnd::CDuiSplitWnd(void)
    :m_bColMode(TRUE)
    ,m_bAdjustable(TRUE)
    ,m_nSepSize(DEF_SEPSIZE)
    ,m_pSkinSep(NULL)
    ,m_iDragBeam(-1)
{
}

CDuiSplitWnd::~CDuiSplitWnd(void)
{
}


BOOL CDuiSplitWnd::SetPaneInfo( int iPane,int nIdealSize,int nMinSize,int nPriority )
{
    if(iPane>m_arrPane.GetCount()-1) return FALSE;
    if(nIdealSize!=-1) m_arrPane[iPane]->m_nSizeIdeal=nIdealSize;
    if(nMinSize!=-1) m_arrPane[iPane]->m_nSizeMin=nMinSize;
    if(nPriority!=-1) m_arrPane[iPane]->m_nPriority=nPriority;
    Relayout();
    return TRUE;
}

BOOL CDuiSplitWnd::GetPaneInfo( int iPane,int *pnIdealSize,int *pnMinSize,int *pnPriority )
{
    if(iPane>m_arrPane.GetCount()-1) return FALSE;
    if(pnIdealSize) *pnIdealSize=m_arrPane[iPane]->m_nSizeIdeal;
    if(pnMinSize) *pnMinSize=m_arrPane[iPane]->m_nSizeMin;
    if(pnPriority) *pnPriority=m_arrPane[iPane]->m_nPriority;
    return TRUE;
}

BOOL CDuiSplitWnd::ShowPanel(int iPane)
{
    if (iPane < 0 || iPane >= m_arrPane.GetCount()) return FALSE;

    m_arrPane[iPane]->SetVisible(TRUE);
    Relayout();
    NotifyInvalidate();
    return TRUE;
}

BOOL CDuiSplitWnd::HidePanel(int iPane)
{
    if (iPane < 0 || iPane >= m_arrPane.GetCount()) return FALSE;

    m_arrPane[iPane]->SetVisible(FALSE);
    Relayout();
    NotifyInvalidate();
    return TRUE;
}

int CDuiSplitWnd::GetVisiblePanelCount()
{
    int nCount = 0;
    for(int i=0; i<m_arrPane.GetCount(); i++)
    {
        if (m_arrPane[i]->IsVisible())
            nCount++;
    }
    return nCount;
}

int CDuiSplitWnd::GetNextVisiblePanel(int iPanel)
{
    if (iPanel < 0 || iPanel + 1 >=  m_arrPane.GetCount())
        return -1;

    for(int i = iPanel + 1; i < m_arrPane.GetCount(); i++)
    {
        if (m_arrPane[i]->IsVisible())
            return i;
    }
    return -1;
}

BOOL CDuiSplitWnd::LoadChildren( TiXmlElement* pTiXmlChildElem )
{
    if(!pTiXmlChildElem) return FALSE;
    TiXmlElement *pTiXmlParent=pTiXmlChildElem->Parent()->ToElement();
    DUIASSERT(pTiXmlParent);
    TiXmlElement *pTiXmlPane=pTiXmlParent->FirstChildElement("pane");
    while(pTiXmlPane)
    {
        CDuiSplitPane *pPane=new CDuiSplitPane();
        InsertChild(pPane);
        if(pPane->Load(pTiXmlPane))
        {
            pPane->AddRef();
            m_arrPane.Add(pPane);
        }
        pTiXmlPane=pTiXmlPane->NextSiblingElement("pane");
    }
    return TRUE;
}


BOOL CDuiSplitWnd::OnDuiSetCursor(const CPoint &pt)
{
    if (!m_bAdjustable) return FALSE;

    SetCursor(LoadCursor(NULL,MAKEINTRESOURCE(m_bColMode?IDC_SIZEWE:IDC_SIZENS)));
    return TRUE;
}

void CDuiSplitWnd::OnDestroy()
{
    __super::OnDestroy();
    for(int i=0; i<m_arrPane.GetCount(); i++)
    {
        m_arrPane[i]->Release();
    }
    m_arrPane.RemoveAll();
}

void CDuiSplitWnd::OnPaint( CDCHandle dc )
{
    CRect rcClient;
    GetClient(&rcClient);

    if(m_pSkinSep)
    {
        CRect rcSep=rcClient;
        if(m_bColMode)
            rcSep.right=rcClient.left;
        else
            rcSep.bottom=rcSep.top;
        long &RB= m_bColMode?rcSep.right:rcSep.bottom;
        long &LT= m_bColMode?rcSep.left:rcSep.top;

        for(int i=0; i<m_arrPane.GetCount()-1; i++)
        {
            CRect rcPane;
            if (!m_arrPane[i]->IsVisible()) continue;
            m_arrPane[i]->GetRect(&rcPane);
            RB+=m_bColMode?rcPane.Width():rcPane.Height();
            LT=RB;
            RB+=m_nSepSize;
            m_pSkinSep->Draw(dc,rcSep,0);
        }
    }
}

int CDuiSplitWnd::FunComp( const void * p1,const void * p2 )
{
    const PANEORDER *pPane1=(PANEORDER*)p1;
    const PANEORDER *pPane2=(PANEORDER*)p2;
    return pPane1->pPane->m_nPriority-pPane2->pPane->m_nPriority;
}

void CDuiSplitWnd::OnWindowPosChanged( LPRECT lpWndPos )
{
    __super::OnWindowPosChanged(lpWndPos);

    Relayout();
}

void CDuiSplitWnd::OnLButtonDown( UINT nFlags,CPoint pt )
{
    __super::OnLButtonDown(nFlags,pt);

    if (!m_bAdjustable) return;

    CRect rcClient;
    GetClient(&rcClient);

    CRect rcBeam=rcClient;
    if(m_bColMode) rcBeam.right=rcBeam.left;
    else rcBeam.bottom=rcBeam.top;

    long & nLT= m_bColMode?rcBeam.left:rcBeam.top;
    long & nRB= m_bColMode?rcBeam.right:rcBeam.bottom;

    //find the clicked beam
    for(int i=0; i<m_arrPane.GetCount(); i++)
    {
        CRect rcPane;
        if (!m_arrPane[i]->IsVisible()) continue;
        m_arrPane[i]->GetRect(&rcPane);
        nLT=m_bColMode?rcPane.right:rcPane.bottom;
        nRB=nLT+m_nSepSize;
        if(rcBeam.PtInRect(pt))
        {
            m_iDragBeam=i;
            break;
        }
    }
    m_ptClick=pt;
}

void CDuiSplitWnd::OnLButtonUp( UINT nFlags,CPoint pt )
{
    m_iDragBeam=-1;
    __super::OnLButtonUp(nFlags,pt);
}

void CDuiSplitWnd::OnMouseMove( UINT nFlags,CPoint pt )
{
    if(-1==m_iDragBeam) return;

    LockUpdate();
    CRect rcPane1,rcPane2;
    int nNextPanel = GetNextVisiblePanel(m_iDragBeam);
    if (nNextPanel == -1) return;

    m_arrPane[m_iDragBeam]->GetRect(&rcPane1);
    m_arrPane[nNextPanel]->GetRect(&rcPane2);

    CPoint ptMove=pt-m_ptClick;

    if(m_bColMode)
    {
        rcPane1.right+=ptMove.x;
        rcPane2.left+=ptMove.x;
        if(ptMove.x<0)
        {
            //decrease left pane
            int iTest=rcPane1.Width()-m_arrPane[m_iDragBeam]->m_nSizeMin;
            if(iTest<0)
            {
                rcPane1.right-=iTest;
                rcPane2.left-=iTest;
            }
        }
        else
        {
            //decrease right pane
            int iTest=rcPane2.Width()-m_arrPane[m_iDragBeam+1]->m_nSizeMin;
            if(iTest<0)
            {
                rcPane1.right+=iTest;
                rcPane2.left+=iTest;
            }
        }
    }
    else
    {
        rcPane1.bottom+=ptMove.y;
        rcPane2.top+=ptMove.y;
        if(ptMove.y<0)
        {
            //decrease top pane
            int iTest=rcPane1.Height()-m_arrPane[m_iDragBeam]->m_nSizeMin;
            if(iTest<0)
            {
                rcPane1.bottom-=iTest;
                rcPane2.top-=iTest;
            }
        }
        else
        {
            //decrease bottom pane
            int iTest=rcPane2.Height()-m_arrPane[m_iDragBeam+1]->m_nSizeMin;
            if(iTest<0)
            {
                rcPane1.bottom+=iTest;
                rcPane2.top+=iTest;
            }
        }
    }
    m_arrPane[m_iDragBeam]->Move(rcPane1);
    m_arrPane[m_iDragBeam+1]->Move(rcPane2);

    if(m_arrPane[m_iDragBeam]->m_nPriority<=m_arrPane[m_iDragBeam+1]->m_nPriority)
    {
        m_arrPane[m_iDragBeam]->m_nSizeIdeal=m_bColMode?rcPane1.Width():rcPane1.Height();
    }
    else
    {
        m_arrPane[m_iDragBeam+1]->m_nSizeIdeal=m_bColMode?rcPane2.Width():rcPane2.Height();
    }
    UnlockUpdate();
    NotifyInvalidate();
    m_ptClick=pt;
}

void CDuiSplitWnd::Relayout()
{
    int nTotalIdeal=0,nTotalMin=0;
    for(int i=0; i<m_arrPane.GetCount(); i++)
    {
        if (!m_arrPane[i]->IsVisible()) continue;
        nTotalIdeal+=m_arrPane[i]->m_nSizeIdeal;
        nTotalMin+=m_arrPane[i]->m_nSizeMin;
    }

    CRect rcClient;
    GetClient(&rcClient);
    int nInter=(GetVisiblePanelCount()-1)*m_nSepSize;
    int nSize=m_bColMode?rcClient.Width():rcClient.Height();

    CRect rcPane=rcClient;
    if(m_bColMode) rcPane.right=rcPane.left;
    else rcPane.bottom=rcPane.top;

    long & nLT= m_bColMode?rcPane.left:rcPane.top;
    long & nRB= m_bColMode?rcPane.right:rcPane.bottom;

    if(nTotalMin+nInter > nSize)
    {
        //set all pane to minimize size
        for(int i=0; i<m_arrPane.GetCount(); i++)
        {
            if (!m_arrPane[i]->IsVisible()) continue;
            nRB+=m_arrPane[i]->m_nSizeMin;
            m_arrPane[i]->Move(&rcPane);
            nLT=nRB+m_nSepSize;
            nRB=nLT;
        }
    }
    else if(nTotalIdeal+nInter<nSize)
    {
        //set all pane to nIdealSize except the lowest priority one, which will be extent to fill all space
        int iLowest=0,nPriority=-1;
        int i;
        for(i=0; i<m_arrPane.GetCount(); i++)
        {
            if (!m_arrPane[i]->IsVisible()) continue;
            if(m_arrPane[i]->m_nPriority>nPriority)
            {
                nPriority=m_arrPane[i]->m_nPriority;
                iLowest=i;
            }
        }
        for(i=0; i<m_arrPane.GetCount(); i++)
        {
            if (!m_arrPane[i]->IsVisible()) continue;
            if(i!=iLowest)
                nRB+=m_arrPane[i]->m_nSizeIdeal;
            else
                nRB+=m_arrPane[i]->m_nSizeIdeal+nSize-(nTotalIdeal+nInter);
            m_arrPane[i]->Move(&rcPane);
            nLT=nRB+m_nSepSize;
            nRB=nLT;
        }
    }
    else
    {
        //set high priority pane size to ideal size and set low pane to remain size
        PANEORDER *pnPriority=new PANEORDER[m_arrPane.GetCount()];
        int *pPaneSize=new int [m_arrPane.GetCount()];

        int i;
        for(i=0; i<m_arrPane.GetCount(); i++)
        {
            pnPriority[i].idx=i;
            pnPriority[i].pPane=m_arrPane[i];
        }
        qsort(pnPriority,m_arrPane.GetCount(),sizeof(PANEORDER),FunComp);

        //为每一个格子分配空间
        int nRemainSize=nSize-nInter;
        BOOL bMinimize=FALSE;
        for(i=0; i<m_arrPane.GetCount(); i++)
        {
            if (!m_arrPane[i]->IsVisible()) continue;
            if(!bMinimize)
            {
                int nRequiredMin=0;
                for(int j=i+1; j<m_arrPane.GetCount(); j++)
                {
                    if (!m_arrPane[j]->IsVisible()) continue;
                    nRequiredMin+=pnPriority[j].pPane->m_nSizeMin;
                }
                if(nRequiredMin<nRemainSize-pnPriority[i].pPane->m_nSizeIdeal)
                    pPaneSize[pnPriority[i].idx]=pnPriority[i].pPane->m_nSizeIdeal;
                else
                {
                    pPaneSize[pnPriority[i].idx]=nRemainSize-nRequiredMin;
                    bMinimize=TRUE;
                }
            }
            else
            {
                pPaneSize[pnPriority[i].idx]=pnPriority[i].pPane->m_nSizeMin;
            }
            nRemainSize-=pPaneSize[pnPriority[i].idx];
        }

        //设置格子位置
        for(i=0; i<m_arrPane.GetCount(); i++)
        {
            if (!m_arrPane[i]->IsVisible()) continue;
            nRB+=pPaneSize[i];
            m_arrPane[i]->Move(&rcPane);
            nLT=nRB+m_nSepSize;
            nRB=nLT;
        }

        delete [] pPaneSize;
        delete [] pnPriority;
    }
}

}//namespace DuiEngine