// IODlg.h : header file
//
#include <string>
using namespace std;
#if !defined(AFX_IODLG_H__9B6A508D_F4EC_47B9_9C90_22579A6395B4__INCLUDED_)
#define AFX_IODLG_H__9B6A508D_F4EC_47B9_9C90_22579A6395B4__INCLUDED_
#include "Controller.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CIODlg dialog

class CIODlg : public CDialog
{
// Construction
public:
	CIODlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIODlg)
	enum { IDD = IDD_IO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIODlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL ISSTART;
	string password;
	string realPassword;
	string adminPassword;
	int state;
	int numError;
	CController *controller;
	
	void startUnlock();
	void checkPassword();
	void del();
	UINT Comd(LPVOID pParam);

	// 设置状态提示的文本
	void setStateText(string msg);

	// 设置密码锁的初始状态
	void initState();

	// 设置密码的显示
	void displayPassword();

	// 完成密码的输入
	void completeInput();

	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIODlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IODLG_H__9B6A508D_F4EC_47B9_9C90_22579A6395B4__INCLUDED_)
