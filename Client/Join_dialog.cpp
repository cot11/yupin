// Join_dialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Client.h"
#include "Join_dialog.h"
#include "afxdialogex.h"
#include "ClientDlg.h"
#include "AddressDlg.h"

// Join_dialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Join_dialog, CDialog)

Join_dialog::Join_dialog(CWnd* pParent /*=NULL*/)
	: CDialog(Join_dialog::IDD, pParent)
	, new_Name(_T(""))
	, new_ID(_T(""))
	, new_PWD(_T(""))
{

}

Join_dialog::~Join_dialog()
{
}

void Join_dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME, new_Name);
	DDV_MaxChars(pDX, new_Name, 20);
	DDX_Text(pDX, IDC_ID, new_ID);
	DDV_MaxChars(pDX, new_ID, 20);
	DDX_Text(pDX, IDC_PWD, new_PWD);
	DDV_MaxChars(pDX, new_PWD, 20);
}


BEGIN_MESSAGE_MAP(Join_dialog, CDialog)
	ON_BN_CLICKED(IDOK, &Join_dialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Join_dialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// Join_dialog �޽��� ó�����Դϴ�.

void Join_dialog::OnBnClickedOk()//Ȯ��
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString Join_info = "";
	CAddressDlg addr;
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	if (strcmp(new_Name, "") == 0) {
		AfxMessageBox("�̸��� �Է��ϼ�.");

		return;
	}

	else if (strcmp(new_ID, "") == 0) {
		AfxMessageBox("ID�� �Է��ϼ�.");

		return;
	}

	else if (strcmp(new_PWD, "") == 0) {
		AfxMessageBox("����� �Է��ϼ�.");
		return;
	}

	ShowWindow(FALSE);
	Join_info = "J|" + new_Name + "|" + new_ID + "|" + new_PWD + "|";
	addr.DeleGate_str(Join_info);
	Join_dialog::OnOK();
}


void Join_dialog::OnBnClickedCancel()
{
	AfxMessageBox("��ҵǾ����ϴ�.");
	CDialog::OnCancel();
}
