#pragma once
#include "afxwin.h"


// Join_dialog 대화 상자입니다.

class Join_dialog : public CDialog
{
	DECLARE_DYNAMIC(Join_dialog)

public:
	Join_dialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Join_dialog();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_JOIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
