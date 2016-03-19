// IODlg.cpp : implementation file
//

#include "stdafx.h"
#include "IO.h"
#include "IODlg.h"
#include "COutput.h"
#include "..\qth9054fun.h"
#include "Controller.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWinThread	*Thread_Comd;	//要创建的两个线程
#define START_UNLOCK 0
#define IDENTIFY_PWD 1
#define SET_NEW_PWD 2
#define INIT_STATE 3
#define ADMIN_PWD 4

#define		LS244    	0
#define		LS273    	0x20
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

void CIODlg::completeInput()
{
	if (state == START_UNLOCK)
		checkPassword();
	else if (state == IDENTIFY_PWD)
	{
		if (password == realPassword)
		{
			setStateText("原密码正确，请输入新密码");
			password = "";
			state = SET_NEW_PWD;
		}
		else
		{
			// 进入初始状态
			initState();
		}
	}
	else if (state == SET_NEW_PWD)
	{
		realPassword = password;
		initState();
	}
	else if (state == ADMIN_PWD)
	{
		if (password == realPassword)
		{
			realPassword = "123456";
			initState();
		}
		else
		{
			// 退出程序
			OnCancel();
		}
	}
}

void CIODlg::setStateText(string msg)
{
	CWnd *pWnd = GetDlgItem(IDC_STATE);
	pWnd->SetWindowText(s.c_str());
	UpdateData(false);
}

void CIODlg::displayPassword()
{
	CWnd *pWnd = GetDlgItem(IDC_PWD);
	string s;
	for (int i = 0; i < password.length(); i++)
		s += '*';
	pWnd->SetWindowText(s.c_str());
	UpdateData(false);
}

void CIODlg::initState()
{
	numError = 0;
	password = "";
	setStateText("选择对应的操作  M:修改密码， O:解锁");
	state = INIT_STATE;
}

//多线程
UINT CIODlg::Comd(LPVOID pParam)
{

	controller = new CController;
	initState();
	//controller->alarm();
	BYTE m_data;
	while (ISSTART)
	{
		Sleep(10);
		char c = controller->getKeyCode();
		CCOutput::outputChar("key=", c);
		if (c == 'O')
		{
			// 开锁操作
			startUnlock();
		}
		else if (c == '#')
		{
			completeInput();
		}
		else if (c == '*')
		{
			del();
		}
		else if (c == 'A')
		{
			setStateText("请输入管理员密码");
			password = "";
			state = ADMIN_PWD;
		}
		else if (c == 'M')
		{
			setStateText("请输入原密码");
			password = "";
			state = IDENTIFY_PWD;
		}
		else if (state != INIT_STATE)
		{
			password += c;
			TRACE(password.c_str());
			TRACE("\n");
		}

		displayPassword();
	}

	return 0;
}

void CIODlg::del()
{
	if (password.length() > 0)
	{
		password = password.substr(0, password.length() - 1);
		TRACE(password.c_str());
	}
}

void CIODlg::checkPassword()
{
	if (password == realPassword)
	{
		setStateText("密码正确，绿灯亮十秒");
		controller->successUnlock();
	}
	else
	{
		numError++;
		if (numError >= 3 && numError % 3 == 0)
		{
			setStateText("报警，绿灯亮5秒");
			//报警
			controller->alarm();
		}
	}
	initState();
}

void CIODlg::startUnlock()
{
	password = "";
	state = START_UNLOCK;
	setStateText("请输入密码");
}

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
// CIODlg dialog

CIODlg::CIODlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIODlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIODlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIODlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIODlg, CDialog)
	//{{AFX_MSG_MAP(CIODlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIODlg message handlers

BOOL CIODlg::OnInitDialog()
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

	if (!Init9054())
	{
		return 0;
	}
	//Thread_Comd=AfxBeginThread(Comd,NULL,THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED);	//创建KEYDOWN线程

	//CController controller;
	//controller.getKeyCode();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIODlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CIODlg::OnPaint()
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
HCURSOR CIODlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CIODlg::OnOK()
{
	// TODO: Add extra validation here
//	if (!ISSTART) {
//		ISSTART=true;
//		Thread_Comd->ResumeThread();
//	}
	ISSTART = true;
	realPassword = "123456";
	adminPassword = "12345678";
	numError = 0;
	Comd(NULL);
	//CDialog::OnOK();
}

void CIODlg::OnCancel()
{
	// TODO: Add extra cleanup here
	ISSTART = false;
	Cleanup();
	CDialog::OnCancel();
}
