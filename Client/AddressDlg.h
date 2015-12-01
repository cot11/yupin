// AddressDlg.h : header file
//

#if !defined(AFX_ADDRESSDLG_H__4F863337_17EA_4376_87F4_131762FA6119__INCLUDED_)
#define AFX_ADDRESSDLG_H__4F863337_17EA_4376_87F4_131762FA6119__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ClientSock.h"
//#include "Join_dialog.h"

/////////////////////////////////////////////////////////////////////////////
// CAddressDlg dialog

class CAddressDlg : public CDialog
{
// Construction
public:
	CAddressDlg(CWnd* pParent = NULL);   // standard constructor
	~CAddressDlg();

// Dialog Data
	//{{AFX_DATA(CAddressDlg)
	enum { IDD = IDD_DIALOG_ADDRESS };	
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
	//// ���� ����
	bool isGuest; // Guest Ȯ��
	CString	m_address; // ip_�ּ�
	CString	m_strName; // login �Է� �� ���̵�
	CString	m_strPwd; // login �Է� �� pw
//	CClientSock* m_LogintSock;
	CString m_Name;
	CString m_NewID;
	CString m_NewPWD;

	//// �Լ� ����
	//void CAddressDlg::DeleGate_str(CString str);
	//void CAddressDlg::DeleGate_OK();
	void OnReceive();
	afx_msg void OnBnClickedOk(); // �α��� ��ư
	afx_msg void OnBnClickedButtonJoin(); // ȸ������ ��ư
	afx_msg void OnBnClickedButtonGuest(); // �Խ�Ʈ ��ư
	afx_msg void OnBnClickedButtonJoinok(); // ȸ�� ���Խ�û�� ���� ���� ��ư
	afx_msg void OnBnClickedButtonCancel(); // ȸ�� ���Խ�û�� ���� ��� ��ư
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDRESSDLG_H__4F863337_17EA_4376_87F4_131762FA6119__INCLUDED_)
