// Join_dialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Client.h"
#include "Join_dialog.h"
#include "afxdialogex.h"
#include "ClientDlg.h"
#include "AddressDlg.h"

// Join_dialog 대화 상자입니다.

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


// Join_dialog 메시지 처리기입니다.

void Join_dialog::OnBnClickedOk()//확인
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString Join_info = "";
	CAddressDlg addr;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	if (strcmp(new_Name, "") == 0) {
		AfxMessageBox("이름을 입력하셈.");

		return;
	}

	else if (strcmp(new_ID, "") == 0) {
		AfxMessageBox("ID를 입력하셈.");

		return;
	}

	else if (strcmp(new_PWD, "") == 0) {
		AfxMessageBox("비번을 입력하셈.");
		return;
	}

	ShowWindow(FALSE);
	Join_info = "J|" + new_Name + "|" + new_ID + "|" + new_PWD + "|";
	addr.DeleGate_str(Join_info);
	Join_dialog::OnOK();
}


void Join_dialog::OnBnClickedCancel()
{
	AfxMessageBox("취소되었습니다.");
	CDialog::OnCancel();
}
