// ClientDlg.h : header file
//

#if !defined(AFX_CLIENTDLG_H__B58492EE_19F2_439C_8ED1_01B716E2F356__INCLUDED_)
#define AFX_CLIENTDLG_H__B58492EE_19F2_439C_8ED1_01B716E2F356__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ClientSock.h"
#include "afxwin.h"
#include "afxcmn.h"
/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

class CClientDlg : public CDialog
{
// Construction
public:
	CString m_name;
	int Check;
	void OnReceive();
	CClientDlg(CWnd* pParent = NULL);	// standard constructor
	~CClientDlg();
	CClientSock* m_pClientSock;
// Dialog Data
	//{{AFX_DATA(CClientDlg)
	enum { IDD = IDD_CLIENT_DIALOG };

	CListCtrl m_LIST_RECEIVE;
	CString	m_strSend;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void DeleGate_Send(CString Join_info);
	afx_msg void OnSend();
	afx_msg void OnBnClickedMfclink1();
	afx_msg void OnBnClickedButtonInsert();
	afx_msg void OnBnClickedButtonDel();
	CString m_Show_Data;
	CEdit m_KeywordInsert;
	CListCtrl m_List_Ctrl;
	afx_msg void OnBnClickedClean();
	afx_msg void OnNMDblclkListReceive(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_resultNumber;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDLG_H__B58492EE_19F2_439C_8ED1_01B716E2F356__INCLUDED_)
