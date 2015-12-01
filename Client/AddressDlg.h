#if !defined(AFX_ADDRESSDLG_H__4F863337_17EA_4376_87F4_131762FA6119__INCLUDED_)
#define AFX_ADDRESSDLG_H__4F863337_17EA_4376_87F4_131762FA6119__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddressDlg.h : header file
//

#include "ClientSock.h"
#include "Join_dialog.h"

/////////////////////////////////////////////////////////////////////////////
// CAddressDlg dialog

class CAddressDlg : public CDialog
{
// Construction
public:
	CAddressDlg(CWnd* pParent = NULL);   // standard constructor
	Join_dialog* m_pJoin;
	void OnReceive();

// Dialog Data
	//{{AFX_DATA(CAddressDlg)
	enum { IDD = IDD_DIALOG_DIALOG_ADDRESS };
	CListBox	m_listReceive;
	CString	m_address; // ip_주소
	CString	m_strName; // login 입력 때 아이디
	CString	m_strPwd; // login 입력 때 pw
	bool isGuest; // Guest 확인
	CClientSock* m_LogintSock;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddressDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void CAddressDlg::DeleGate_str(CString str);
	void CAddressDlg::DeleGate_OK();
	afx_msg void OnBnClickedOk(); // login
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEditName();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDRESSDLG_H__4F863337_17EA_4376_87F4_131762FA6119__INCLUDED_)
