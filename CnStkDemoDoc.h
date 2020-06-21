// CnStkDemoDoc.h : interface of the CCnStkDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTKDEMODOC_H__127C92E3_4712_4D8C_ABBD_E9F04F22CC10__INCLUDED_)
#define AFX_CNSTKDEMODOC_H__127C92E3_4712_4D8C_ABBD_E9F04F22CC10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCnStkDemoDoc : public CDocument
{
protected: // create from serialization only
	CCnStkDemoDoc();
	DECLARE_DYNCREATE(CCnStkDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCnStkDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCnStkDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCnStkDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNSTKDEMODOC_H__127C92E3_4712_4D8C_ABBD_E9F04F22CC10__INCLUDED_)
