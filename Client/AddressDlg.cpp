// AddressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "AddressDlg.h"
#include "ClientDlg.h"
#include "Join_dialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString Join_info;
BOOL OK = false;
/////////////////////////////////////////////////////////////////////////////
// CAddressDlg dialog


CAddressDlg::CAddressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddressDlg)
	m_address = _T("");
	m_strName = _T("");
	m_strPwd = _T("");
	//}}AFX_DATA_INIT
}


void CAddressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddressDlg)
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT2, m_strPwd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddressDlg, CDialog)
	//{{AFX_MSG_MAP(CAddressDlg)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CAddressDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CAddressDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CAddressDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddressDlg message handlers

BOOL CAddressDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CAddressDlg::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}

void CAddressDlg::OnBnClickedOk() //login
{
	UpdateData(TRUE);

	if (strcmp(m_strName, "") == 0 || strcmp(m_strPwd, "") == 0) { // ID 또는 PW가 공백으로 로그인 시 오류 처리
		AfxMessageBox("아이디 또는 비밀번호를 다시 확인하세요.");
		return;
	}

	CDialog::OnOK();
}

void CAddressDlg::OnBnClickedButton2() // join 버튼
{
	GetDlgItem(IDC_BUTTON2)->ShowWindow(false); // 상태 버튼 비활성화

}


void CAddressDlg::OnBnClickedButton1() // guest 버튼
{
	isGuest = TRUE;
	CDialog::OnOK();
}

void CAddressDlg::DeleGate_str(CString str)
{
	OK = TRUE;
	Join_info = str;
	AfxMessageBox(Join_info);
}
void CAddressDlg::DeleGate_OK()
{
	CAddressDlg::OnOK();
}

