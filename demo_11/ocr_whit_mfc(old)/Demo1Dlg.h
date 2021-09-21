// Demo1Dlg.h : header file
//

#if !defined(AFX_DEMO1DLG_H__E0B9CF87_3B0B_4520_8276_8EFC80D8E8BC__INCLUDED_)
#define AFX_DEMO1DLG_H__E0B9CF87_3B0B_4520_8276_8EFC80D8E8BC__INCLUDED_

#include "CDIB.H"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDemo1Dlg dialog

class CDemo1Dlg : public CDialog
{
// Construction
public:
	CDemo1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDemo1Dlg)
	enum { IDD = IDD_DEMO1_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemo1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CDib m_dib;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDemo1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnLoad();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnProcess();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMO1DLG_H__E0B9CF87_3B0B_4520_8276_8EFC80D8E8BC__INCLUDED_)
