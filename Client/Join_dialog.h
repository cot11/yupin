#pragma once
#include "afxwin.h"


// Join_dialog ��ȭ �����Դϴ�.

class Join_dialog : public CDialog
{
	DECLARE_DYNAMIC(Join_dialog)

public:
	Join_dialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Join_dialog();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_JOIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
