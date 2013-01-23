// huanhuanDlg.cpp : implementation file
//

#include "stdafx.h"
#include "huanhuan.h"
#include "huanhuanDlg.h"
#include "json.h"
#include "get_json.h"
#include "print_book.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BUFSIZE (1024*1024)

CButton* g_Search;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHuanhuanDlg dialog

CHuanhuanDlg::CHuanhuanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHuanhuanDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHuanhuanDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHuanhuanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHuanhuanDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHuanhuanDlg, CDialog)
	//{{AFX_MSG_MAP(CHuanhuanDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEARCH, OnSearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHuanhuanDlg message handlers

BOOL CHuanhuanDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHuanhuanDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHuanhuanDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHuanhuanDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHuanhuanDlg::OnSearch() 
{
	// TODO: Add your control notification handler code here

	CString key = _T("");
	GetDlgItem(IDC_SEARCH_EDIT)->GetWindowText(key);
	if (key.IsEmpty())
	{
		AfxMessageBox("input error\n");
		return;
	}
//	key = _T("driver");

	struct obj * p_obj;
	char * recv_buf = (char *)malloc(sizeof(char) * BUFSIZE);
	if (recv_buf == 0)
	{
		AfxMessageBox("malloc");
		exit(1);
	}
	memset(recv_buf, 0, BUFSIZE);// 把它置为0


	get_json(recv_buf, key.GetBuffer(0));//search book:key = driver

	ana_json(recv_buf, sizeof recv_buf, &p_obj);

	free(recv_buf);

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_SHOW);
	pEdit->SetSel(-1);

//	print_book(p_obj, 0, pEdit);
//	AfxMessageBox("你好\n");
	CButton* g_Search = (CButton*)GetDlgItem(IDC_SEARCH);
	g_Search->EnableWindow(FALSE);

	struct print* p = new struct print;
	memset(p, 0, sizeof(struct print));
	p->p_obj = p_obj;
	p->len = 0;
	p->pEdit = pEdit;

	CreateThread(0, 0, print_book, p, 0, 0);
}
