#pragma once


// Cdialog_Address ��ȭ �����Դϴ�.

class Cdialog_Address : public CDialog
{
	DECLARE_DYNAMIC(Cdialog_Address)

public:
	Cdialog_Address(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Cdialog_Address();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_DIALOG_ADDRESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
