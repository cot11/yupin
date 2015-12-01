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
	, m_Name(_T(""))
	, m_NewID(_T(""))
	, m_NewPWD(_T(""))
{
	//{{AFX_DATA_INIT(CAddressDlg)
	m_address = _T("");
	m_strName = _T("");
	m_strPwd = _T("");
	//}}AFX_DATA_INIT
}

CAddressDlg::~CAddressDlg()
{

}

void CAddressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddressDlg)
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPwd);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_INUSER, m_Name);
	DDX_Text(pDX, IDC_EDIT_INID, m_NewID);
	DDX_Text(pDX, IDC_EDIT_INPWD, m_NewPWD);
}


BEGIN_MESSAGE_MAP(CAddressDlg, CDialog)
	//{{AFX_MSG_MAP(CAddressDlg)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CAddressDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_JOIN, &CAddressDlg::OnBnClickedButtonJoin)
	ON_BN_CLICKED(IDC_BUTTON_GUEST, &CAddressDlg::OnBnClickedButtonGuest)
	ON_BN_CLICKED(IDC_BUTTON_JOINOK, &CAddressDlg::OnBnClickedButtonJoinok)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CAddressDlg::OnBnClickedButtonCancel)
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
		UpdateData(FALSE);
		return;
	}

	UpdateData(FALSE);

	CDialog::OnOK();
}

void CAddressDlg::OnBnClickedButtonJoin() // 회원가입 버튼 누를 시 이벤트 발생 처리
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		
	GetDlgItem(IDC_STATIC_INID)->ShowWindow(FALSE); // ID 텍스트 숨김
	GetDlgItem(IDC_STATIC_INPWD)->ShowWindow(FALSE); // PWD 텍스트 숨김
	GetDlgItem(IDC_EDIT_NAME)->ShowWindow(FALSE); // ID 입력 칸 숨김
	GetDlgItem(IDC_EDIT_PWD)->ShowWindow(FALSE); // PWD 입력 칸 숨김
	GetDlgItem(IDOK)->ShowWindow(FALSE); // 로그인 버튼 숨김
	GetDlgItem(IDC_BUTTON_GUEST)->ShowWindow(FALSE); // 게스트 버튼 숨김
	GetDlgItem(IDC_BUTTON_JOIN)->ShowWindow(FALSE); // 회원가입 상태 버튼 숨김

	///////////////////////////////////////////////////////////////////////////// 활성화 되는 부분
	GetDlgItem(IDC_STATIC_USER)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT_INUSER)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_ID)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT_INID)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_PWD)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT_INPWD)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON_JOINOK)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CANCEL)->ShowWindow(TRUE);
}


void CAddressDlg::OnBnClickedButtonGuest() // Guest 버튼 누를 시 이벤트 발생 처리
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	isGuest = TRUE;
	CDialog::OnOK();
}

void CAddressDlg::OnBnClickedButtonJoinok() // 회원 가입서 안의 가입 버튼
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString Join_info = "";

	UpdateData(TRUE);
				
	if (strcmp(m_Name, "") == 0)
	{
		AfxMessageBox("이름을 입력하셈.");
		UpdateData(FALSE);
		return;
	}

	else if (strcmp(m_NewID, "") == 0)
	{
		AfxMessageBox("ID를 입력하셈.");
		UpdateData(FALSE);
		return;
	}

	// 이 부분에서 m_NewID(사용자가 사용할려고 하는 ID) 부분 중복체크해서 중복되면 리턴시켜버리면 될듯
	/*else if( m_NewID를 서버로 보내는 소스 작성하면 될듯)
	{

	}*/

	else if (strcmp(m_NewPWD, "") == 0)
	{
		AfxMessageBox("비번을 입력하셈.");
		UpdateData(FALSE);
		return;
	}

	Join_info = "J|" + m_Name + "|" + m_NewID + "|" + m_NewPWD + "|";

	AfxMessageBox("가입 축하함. 확인을 누르면 바로 접속을 시도하겠음.");

	GetDlgItem(IDC_STATIC_INID)->ShowWindow(TRUE); // ID 텍스트 숨김
	GetDlgItem(IDC_STATIC_INPWD)->ShowWindow(TRUE); // PWD 텍스트 숨김
	GetDlgItem(IDC_EDIT_NAME)->ShowWindow(TRUE); // ID 입력 칸 숨김
	GetDlgItem(IDC_EDIT_PWD)->ShowWindow(TRUE); // PWD 입력 칸 숨김
	GetDlgItem(IDOK)->ShowWindow(TRUE); // 로그인 버튼 숨김
	GetDlgItem(IDC_BUTTON_GUEST)->ShowWindow(TRUE); // 게스트 버튼 숨김
	GetDlgItem(IDC_BUTTON_JOIN)->ShowWindow(TRUE); // 회원가입 상태 버튼 숨김

	///////////////////////////////////////////////////////////////////////////// 비활성화 되는 부분
	GetDlgItem(IDC_STATIC_USER)->ShowWindow(FALSE); // 이름 텍스트 숨김
	GetDlgItem(IDC_EDIT_INUSER)->ShowWindow(FALSE); // 이름 입력 칸 숨김
	GetDlgItem(IDC_STATIC_ID)->ShowWindow(FALSE); // ID 텍스트 숨김
	GetDlgItem(IDC_EDIT_INID)->ShowWindow(FALSE); // ID 입력 칸 숨김
	GetDlgItem(IDC_STATIC_PWD)->ShowWindow(FALSE); // 비밀번호 텍스트 숨김
	GetDlgItem(IDC_EDIT_INPWD)->ShowWindow(FALSE); // 비밀번호 입력 칸 숨김
	GetDlgItem(IDC_BUTTON_JOINOK)->ShowWindow(FALSE); // 가입 버튼 숨김
	GetDlgItem(IDC_BUTTON_CANCEL)->ShowWindow(FALSE); // 취소 버튼 숨김

	m_Name = "";
	m_NewID = "";
	m_NewPWD = "";

	UpdateData(FALSE);

	CAddressDlg::OnOK();
}

void CAddressDlg::OnBnClickedButtonCancel() // 회원 가입서 안의 가입 가입 취소 버튼
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_Name = "";
	m_NewID = "";
	m_NewPWD = "";

	UpdateData(FALSE);

	AfxMessageBox("취소되었습니다.");

	GetDlgItem(IDC_STATIC_INID)->ShowWindow(TRUE); // ID 텍스트 숨김
	GetDlgItem(IDC_STATIC_INPWD)->ShowWindow(TRUE); // PWD 텍스트 숨김
	GetDlgItem(IDC_EDIT_NAME)->ShowWindow(TRUE); // ID 입력 칸 숨김
	GetDlgItem(IDC_EDIT_PWD)->ShowWindow(TRUE); // PWD 입력 칸 숨김
	GetDlgItem(IDOK)->ShowWindow(TRUE); // 로그인 버튼 숨김
	GetDlgItem(IDC_BUTTON_GUEST)->ShowWindow(TRUE); // 게스트 버튼 숨김
	GetDlgItem(IDC_BUTTON_JOIN)->ShowWindow(TRUE); // 회원가입 상태 버튼 숨김

	///////////////////////////////////////////////////////////////////////////// 비활성화 되는 부분
	GetDlgItem(IDC_STATIC_USER)->ShowWindow(FALSE); // 이름 텍스트 숨김
	GetDlgItem(IDC_EDIT_INUSER)->ShowWindow(FALSE); // 이름 입력 칸 숨김
	GetDlgItem(IDC_STATIC_ID)->ShowWindow(FALSE); // ID 텍스트 숨김
	GetDlgItem(IDC_EDIT_INID)->ShowWindow(FALSE); // ID 입력 칸 숨김
	GetDlgItem(IDC_STATIC_PWD)->ShowWindow(FALSE); // 비밀번호 텍스트 숨김
	GetDlgItem(IDC_EDIT_INPWD)->ShowWindow(FALSE); // 비밀번호 입력 칸 숨김
	GetDlgItem(IDC_BUTTON_JOINOK)->ShowWindow(FALSE); // 가입 버튼 숨김
	GetDlgItem(IDC_BUTTON_CANCEL)->ShowWindow(FALSE); // 취소 버튼 숨김
}