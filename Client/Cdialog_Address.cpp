// Cdialog_Address.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Client.h"
#include "Cdialog_Address.h"
#include "afxdialogex.h"


// Cdialog_Address 대화 상자입니다.

IMPLEMENT_DYNAMIC(Cdialog_Address, CDialog)

Cdialog_Address::Cdialog_Address(CWnd* pParent /*=NULL*/)
	: CDialog(Cdialog_Address::IDD, pParent)
{

}

Cdialog_Address::~Cdialog_Address()
{
}

void Cdialog_Address::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Cdialog_Address, CDialog)
END_MESSAGE_MAP()


// Cdialog_Address 메시지 처리기입니다.
