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

	if (strcmp(m_strName, "") == 0 || strcmp(m_strPwd, "") == 0) { // ID �Ǵ� PW�� �������� �α��� �� ���� ó��
		AfxMessageBox("���̵� �Ǵ� ��й�ȣ�� �ٽ� Ȯ���ϼ���.");
		UpdateData(FALSE);
		return;
	}

	UpdateData(FALSE);

	CDialog::OnOK();
}

void CAddressDlg::OnBnClickedButtonJoin() // ȸ������ ��ư ���� �� �̺�Ʈ �߻� ó��
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
		
	GetDlgItem(IDC_STATIC_INID)->ShowWindow(FALSE); // ID �ؽ�Ʈ ����
	GetDlgItem(IDC_STATIC_INPWD)->ShowWindow(FALSE); // PWD �ؽ�Ʈ ����
	GetDlgItem(IDC_EDIT_NAME)->ShowWindow(FALSE); // ID �Է� ĭ ����
	GetDlgItem(IDC_EDIT_PWD)->ShowWindow(FALSE); // PWD �Է� ĭ ����
	GetDlgItem(IDOK)->ShowWindow(FALSE); // �α��� ��ư ����
	GetDlgItem(IDC_BUTTON_GUEST)->ShowWindow(FALSE); // �Խ�Ʈ ��ư ����
	GetDlgItem(IDC_BUTTON_JOIN)->ShowWindow(FALSE); // ȸ������ ���� ��ư ����

	///////////////////////////////////////////////////////////////////////////// Ȱ��ȭ �Ǵ� �κ�
	GetDlgItem(IDC_STATIC_USER)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT_INUSER)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_ID)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT_INID)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_PWD)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT_INPWD)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON_JOINOK)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CANCEL)->ShowWindow(TRUE);
}


void CAddressDlg::OnBnClickedButtonGuest() // Guest ��ư ���� �� �̺�Ʈ �߻� ó��
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	isGuest = TRUE;
	CDialog::OnOK();
}

void CAddressDlg::OnBnClickedButtonJoinok() // ȸ�� ���Լ� ���� ���� ��ư
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CString Join_info = "";

	UpdateData(TRUE);
				
	if (strcmp(m_Name, "") == 0)
	{
		AfxMessageBox("�̸��� �Է��ϼ�.");
		UpdateData(FALSE);
		return;
	}

	else if (strcmp(m_NewID, "") == 0)
	{
		AfxMessageBox("ID�� �Է��ϼ�.");
		UpdateData(FALSE);
		return;
	}

	// �� �κп��� m_NewID(����ڰ� ����ҷ��� �ϴ� ID) �κ� �ߺ�üũ�ؼ� �ߺ��Ǹ� ���Ͻ��ѹ����� �ɵ�
	/*else if( m_NewID�� ������ ������ �ҽ� �ۼ��ϸ� �ɵ�)
	{

	}*/

	else if (strcmp(m_NewPWD, "") == 0)
	{
		AfxMessageBox("����� �Է��ϼ�.");
		UpdateData(FALSE);
		return;
	}

	Join_info = "J|" + m_Name + "|" + m_NewID + "|" + m_NewPWD + "|";

	AfxMessageBox("���� ������. Ȯ���� ������ �ٷ� ������ �õ��ϰ���.");

	GetDlgItem(IDC_STATIC_INID)->ShowWindow(TRUE); // ID �ؽ�Ʈ ����
	GetDlgItem(IDC_STATIC_INPWD)->ShowWindow(TRUE); // PWD �ؽ�Ʈ ����
	GetDlgItem(IDC_EDIT_NAME)->ShowWindow(TRUE); // ID �Է� ĭ ����
	GetDlgItem(IDC_EDIT_PWD)->ShowWindow(TRUE); // PWD �Է� ĭ ����
	GetDlgItem(IDOK)->ShowWindow(TRUE); // �α��� ��ư ����
	GetDlgItem(IDC_BUTTON_GUEST)->ShowWindow(TRUE); // �Խ�Ʈ ��ư ����
	GetDlgItem(IDC_BUTTON_JOIN)->ShowWindow(TRUE); // ȸ������ ���� ��ư ����

	///////////////////////////////////////////////////////////////////////////// ��Ȱ��ȭ �Ǵ� �κ�
	GetDlgItem(IDC_STATIC_USER)->ShowWindow(FALSE); // �̸� �ؽ�Ʈ ����
	GetDlgItem(IDC_EDIT_INUSER)->ShowWindow(FALSE); // �̸� �Է� ĭ ����
	GetDlgItem(IDC_STATIC_ID)->ShowWindow(FALSE); // ID �ؽ�Ʈ ����
	GetDlgItem(IDC_EDIT_INID)->ShowWindow(FALSE); // ID �Է� ĭ ����
	GetDlgItem(IDC_STATIC_PWD)->ShowWindow(FALSE); // ��й�ȣ �ؽ�Ʈ ����
	GetDlgItem(IDC_EDIT_INPWD)->ShowWindow(FALSE); // ��й�ȣ �Է� ĭ ����
	GetDlgItem(IDC_BUTTON_JOINOK)->ShowWindow(FALSE); // ���� ��ư ����
	GetDlgItem(IDC_BUTTON_CANCEL)->ShowWindow(FALSE); // ��� ��ư ����

	m_Name = "";
	m_NewID = "";
	m_NewPWD = "";

	UpdateData(FALSE);

	CAddressDlg::OnOK();
}

void CAddressDlg::OnBnClickedButtonCancel() // ȸ�� ���Լ� ���� ���� ���� ��� ��ư
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	m_Name = "";
	m_NewID = "";
	m_NewPWD = "";

	UpdateData(FALSE);

	AfxMessageBox("��ҵǾ����ϴ�.");

	GetDlgItem(IDC_STATIC_INID)->ShowWindow(TRUE); // ID �ؽ�Ʈ ����
	GetDlgItem(IDC_STATIC_INPWD)->ShowWindow(TRUE); // PWD �ؽ�Ʈ ����
	GetDlgItem(IDC_EDIT_NAME)->ShowWindow(TRUE); // ID �Է� ĭ ����
	GetDlgItem(IDC_EDIT_PWD)->ShowWindow(TRUE); // PWD �Է� ĭ ����
	GetDlgItem(IDOK)->ShowWindow(TRUE); // �α��� ��ư ����
	GetDlgItem(IDC_BUTTON_GUEST)->ShowWindow(TRUE); // �Խ�Ʈ ��ư ����
	GetDlgItem(IDC_BUTTON_JOIN)->ShowWindow(TRUE); // ȸ������ ���� ��ư ����

	///////////////////////////////////////////////////////////////////////////// ��Ȱ��ȭ �Ǵ� �κ�
	GetDlgItem(IDC_STATIC_USER)->ShowWindow(FALSE); // �̸� �ؽ�Ʈ ����
	GetDlgItem(IDC_EDIT_INUSER)->ShowWindow(FALSE); // �̸� �Է� ĭ ����
	GetDlgItem(IDC_STATIC_ID)->ShowWindow(FALSE); // ID �ؽ�Ʈ ����
	GetDlgItem(IDC_EDIT_INID)->ShowWindow(FALSE); // ID �Է� ĭ ����
	GetDlgItem(IDC_STATIC_PWD)->ShowWindow(FALSE); // ��й�ȣ �ؽ�Ʈ ����
	GetDlgItem(IDC_EDIT_INPWD)->ShowWindow(FALSE); // ��й�ȣ �Է� ĭ ����
	GetDlgItem(IDC_BUTTON_JOINOK)->ShowWindow(FALSE); // ���� ��ư ����
	GetDlgItem(IDC_BUTTON_CANCEL)->ShowWindow(FALSE); // ��� ��ư ����
}