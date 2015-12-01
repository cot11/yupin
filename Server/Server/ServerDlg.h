// ServerDlg.h : 헤더 파일
//

#pragma once
#include <string.h>
#include "mysql.h"
#include <WinSock2.h>
#include "trayiconmng.h"
#include "ServerSock.h"
#include "ClientSock.h"
#include "afxwin.h"
#include "afxcmn.h"
#pragma comment(lib, "libmysql.lib")
#pragma comment(lib, "ws2_32.lib")


#define DB_ADDRESS "localhost"
#define DB_ID "root"
#define DB_PASS "dl156156"
#define DB_NAME "yupin"
#define DB_IDD "search5"
#define DB_IDDD "search4"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CServerDlg 대화 상자
class CServerDlg : public CDialogEx
{
// 생성입니다.
public:
	void Send(char* buf);
	void OnAccept();
	void OnReceive(CClientSock* pSock);
	CServerSock* m_pServerSock;
	CTypedPtrList<CObList, CClientSock*> m_clientSocks;
	CServerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	CListBox	m_Url_List;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SERVER_DIALOG };
	CString	m_strSend;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnSendUrl(int num);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTrayIconMng m_myTray;
	bool m_bHide;
	long OnTrayIcon(WPARAM wParam, LPARAM lParam);
	void OnAppExit(void);
	void OnDialogShow(void);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	static UINT Y_Thread(LPVOID pParam);
	static UINT Keyword_Store(LPVOID pParam);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	CString m_Show_Data;
	CString m_Absol_URL;
	CString m_Html_Tag;
	CString m_Url_Begi;
	CString m_values;
	int CTotal;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedSend();
	CListCtrl userKeyword;
	CListCtrl UserIP;
};
