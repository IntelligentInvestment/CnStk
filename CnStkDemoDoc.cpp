// CnStkDemoDoc.cpp : implementation of the CCnStkDemoDoc class
//

#include "stdafx.h"
#include "CnStkDemo.h"

#include "CnStkDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCnStkDemoDoc

IMPLEMENT_DYNCREATE(CCnStkDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CCnStkDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CCnStkDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCnStkDemoDoc construction/destruction

CCnStkDemoDoc::CCnStkDemoDoc()
{
	// TODO: add one-time construction code here

}

CCnStkDemoDoc::~CCnStkDemoDoc()
{
}

BOOL CCnStkDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCnStkDemoDoc serialization

void CCnStkDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCnStkDemoDoc diagnostics

#ifdef _DEBUG
void CCnStkDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCnStkDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCnStkDemoDoc commands
