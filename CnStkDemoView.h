// CnStkDemoView.h : interface of the CCnStkDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTKDEMOVIEW_H__7FF3DD79_021A_42A4_8BBD_C8550C94D780__INCLUDED_)
#define AFX_CNSTKDEMOVIEW_H__7FF3DD79_021A_42A4_8BBD_C8550C94D780__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCnStkDemoView : public CView
{
protected: // create from serialization only
	CCnStkDemoView();
	DECLARE_DYNCREATE(CCnStkDemoView)

// Attributes
public:
	CCnStkDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCnStkDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCnStkDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCnStkDemoView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CnStkDemoView.cpp
inline CCnStkDemoDoc* CCnStkDemoView::GetDocument()
   { return (CCnStkDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNSTKDEMOVIEW_H__7FF3DD79_021A_42A4_8BBD_C8550C94D780__INCLUDED_)
