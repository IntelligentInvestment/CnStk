// CnStkDemoView.cpp : implementation of the CCnStkDemoView class
//

#include "stdafx.h"
#include "CnStkDemo.h"

#include "CnStkDemoDoc.h"
#include "CnStkDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCnStkDemoView

IMPLEMENT_DYNCREATE(CCnStkDemoView, CView)

BEGIN_MESSAGE_MAP(CCnStkDemoView, CView)
	//{{AFX_MSG_MAP(CCnStkDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCnStkDemoView construction/destruction

CCnStkDemoView::CCnStkDemoView()
{
	// TODO: add construction code here

}

CCnStkDemoView::~CCnStkDemoView()
{
}

BOOL CCnStkDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCnStkDemoView drawing

void CCnStkDemoView::OnDraw(CDC* pDC)
{
	CCnStkDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCnStkDemoView printing

BOOL CCnStkDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCnStkDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCnStkDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCnStkDemoView diagnostics

#ifdef _DEBUG
void CCnStkDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CCnStkDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCnStkDemoDoc* CCnStkDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCnStkDemoDoc)));
	return (CCnStkDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCnStkDemoView message handlers
