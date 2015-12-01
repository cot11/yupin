#pragma once


// Cdialog_Address 대화 상자입니다.

class Cdialog_Address : public CDialog
{
	DECLARE_DYNAMIC(Cdialog_Address)

public:
	Cdialog_Address(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Cdialog_Address();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_DIALOG_ADDRESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
