// huanhuanDlg.h : header file
//

#if !defined(AFX_HUANHUANDLG_H__DE6528DD_61D9_4C5B_B255_56C9BCBE2DF1__INCLUDED_)
#define AFX_HUANHUANDLG_H__DE6528DD_61D9_4C5B_B255_56C9BCBE2DF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHuanhuanDlg dialog

class CHuanhuanDlg : public CDialog
{
// Construction
public:
	CHuanhuanDlg(CWnd* pParent = NULL);	// standard constructor



// Dialog Data
	//{{AFX_DATA(CHuanhuanDlg)
	enum { IDD = IDD_HUANHUAN_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHuanhuanDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHuanhuanDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSearch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HUANHUANDLG_H__DE6528DD_61D9_4C5B_B255_56C9BCBE2DF1__INCLUDED_)
