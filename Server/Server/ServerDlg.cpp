
// ServerDlg.cpp : 구현 파일
//
#define WIN32_LEAN_AND_MEAN
#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"
#include "Login.h"
#include <atlstr.h>
#include<Windows.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

MYSQL_ROW row;
MYSQL_RES *m_res;
MYSQL *connection = NULL, *connection2 = NULL, *connection3, mysql, mysql2, mysql3, mysql4;

int user_Count = 0;
int Keyword_count = 0;

int Socket_Status = 100;
int Keyword_Status = 100;

CClientSock *pT = new CClientSock[Socket_Status]; // 유저의 소켓 정보
CString *uT = new CString[Socket_Status];		  // 유저 아이티 정보
CString *uK = new CString[Keyword_Status];		  // 유저 키워드 정보
CString *uid = new CString[Keyword_Status];		  // 게스트 아이디 정보

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
using namespace std;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();


// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CServerDlg 대화 상자



CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/) : CDialogEx(CServerDlg::IDD, pParent),  m_Show_Data(_T(""))
{
	m_strSend = _T("");
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//AFX Data List
	DDX_Text(pDX, IDC_EDIT1, m_Show_Data);
	//End of AFX Data List
	DDX_Control(pDX, IDC_LIST1, userKeyword);
	DDX_Control(pDX, IDC_LIST3, UserIP);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(Collertion_Bot, &CServerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CServerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CServerDlg::OnBnClickedCancel)
	ON_MESSAGE(WM_TRAYICON, OnTrayIcon)
	ON_COMMAND(WM_APP_EXIT, OnAppExit)
	ON_COMMAND(WM_DIALOG_SHOW, OnDialogShow)
	ON_BN_CLICKED(IDC_SEND, &CServerDlg::OnBnClickedSend)
END_MESSAGE_MAP()


// CServerDlg 메시지 처리기

BOOL CServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	userKeyword.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	userKeyword.InsertColumn(0, "ID", LVCFMT_LEFT, 100);
	userKeyword.InsertColumn(1, "Keyword", LVCFMT_LEFT, 250);

	UserIP.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	UserIP.InsertColumn(0, "ID", LVCFMT_LEFT, 100);
	UserIP.InsertColumn(1, "IP", LVCFMT_LEFT, 250);
	m_Show_Data += "서버 구동\r\n";
	UpdateData(false);
	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_myTray.m_bHide = m_bHide;
	m_myTray.AddTrayIcon(GetSafeHwnd());
	m_pServerSock = new CServerSock();
	m_pServerSock->Create(700);
	m_pServerSock->Listen();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	/*  상단에 x 버튼을 눌렀을때
	else if(nID == SC_CLOSE)
	{

	}
	*/
	// 최소화 버튼을 눌렀을때
	else if (nID == SC_MINIMIZE)
	{
		ShowWindow(SW_SHOWMINIMIZED);
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CServerDlg::OnPaint()
{


	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CServerDlg::OnBnClickedButton1()
{
	//Play Bot;
}


void CServerDlg::OnBnClickedOk()
{
	CWinThread *p = NULL, *p2 = NULL;

	//MFC는사용자가따로delete p; 할필요없게자동으로삭제해준다.
	p = AfxBeginThread(Y_Thread, this);
	p2 = AfxBeginThread(Y2_Thread, this);

	if (p == NULL)
	{
		m_Show_Data += "thread 2 Error\r\n";
	}
	else if (p2 == NULL)
	{
		m_Show_Data += "thread 2 Error\r\n";
	}
	else
		m_Show_Data += "Collect BOT thread Success\r\n";

	UpdateData(false);

	if (p != NULL)
	{
		CloseHandle(p->m_hThread);
	}
		
	if (p2 != NULL)
	{
		CloseHandle(p2->m_hThread);
	}
}


void CServerDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}
void CServerDlg::OnSendUrl(int num)
{
	
}

UINT MyThreadProc(LPVOID pParam)
{
	CServerDlg* pObject = (CServerDlg*)pParam;

	if (pObject == NULL ||
		!pObject->IsKindOf(RUNTIME_CLASS(CServerDlg)))
		return 1;   // if pObject is not valid

	// do something with 'pObject'

	return 0;   // thread completed successfully
}
long CServerDlg::OnTrayIcon(WPARAM wParam, LPARAM lParam)
{
	m_myTray.ProcTrayMsg(GetSafeHwnd(), wParam, lParam);
	return 0;
}
void CServerDlg::OnAppExit(void)
{
	m_myTray.DelTrayIcon(GetSafeHwnd());
	CDialog::OnCancel();
}
void CServerDlg::OnDialogShow(void)
{
	if (!m_bHide) ShowWindow(false);       //보이는상태라면숨기고
	else ShowWindow(true);                //숨겨진상태라면보이게
	m_bHide = !m_bHide;
	m_myTray.m_bHide = m_bHide;
}

void CServerDlg::OnAccept()
{

	CClientSock *p = new CClientSock;

	if(m_pServerSock->Listen())
	{
		m_Show_Data += "Message : 누군가 서버에 접속을 요청합니다. \r\n";
		m_pServerSock->Accept(*p);  //접속을 요청하는 Clinet를 받아들인다.
		m_clientSocks.AddTail(p);	//Clinet의 Socket을 보관하는 Class에게 Client의 정보를 Store
		m_Show_Data += "Message : 요청을 정상적으로 처리합니다. \r\n";
		UpdateData(false);
	}
	else
	{
		m_Show_Data += "Message : 요청수락을 실패했습니다. \r\n";
		UpdateData(false);
	}
	//p->Send("연결되었습니다.",16);


}


void CServerDlg::OnReceive(CClientSock* pSock)
{

	CString query = "";
	CString str;
	CString Sum[4];
	CString result_num_str;
	CString Alarm_str;
	my_ulonglong result_num;
	char buf[2000];
	SOCKADDR_IN clientaddr;
	char * addr;
	CString addrstring = "";
	int addrlen;

	pSock->Receive(buf, 2000);

	addrlen = sizeof(clientaddr);
	getpeername(*pSock, (struct sockaddr*)&clientaddr, &addrlen);
	addr = (char*)inet_ntoa((struct in_addr)clientaddr.sin_addr);
	addrstring.Format(_T(addr));


	mysql_init(&mysql3);
	if (connection2 = mysql_real_connect(&mysql3, DB_ADDRESS, DB_IDD, DB_PASS, DB_NAME, 3306, 0, 0))
	{
		mysql_set_character_set(&mysql3, "euckr");
		//AfxMessageBox("OK", MB_OK);
	}
	else
	{
		AfxMessageBox("fail", MB_OK);
	}

	AfxExtractSubString(str, buf, 0, '|'); 

	if (str == 'L')
	{
		CString id, pwd;
		AfxExtractSubString(id, buf, 1, '|'); 
		AfxExtractSubString(pwd, buf, 2, '|'); 

		query.Format("select * from userinfo where id = \"%s\" and password = \"%s\"",id,pwd);

		if (mysql_query(&mysql3, query))
		{
			AfxMessageBox("Fail", MB_OK);
		}

		if ((m_res = mysql_store_result(&mysql3)) == NULL)
		{ // 결과를 m_Res에 저장
			return;
		}
		if ((row = mysql_fetch_row(m_res)) != NULL)
		{

			UserIP.InsertItem(0, id);
			UserIP.SetItemText(0, 1, addrstring);
			memcpy(&pT[user_Count], pSock, sizeof(CClientSock));
			uT[user_Count] = id;
			pT[user_Count].Send("O|", 2);
			m_Show_Data += "Message : " + id + "님이 로그인했습니다.\r\n";
			UpdateData(false);
			query.Format("select Keyword from Keywordt where id = \"%s\"",id);

			if (mysql_query(&mysql3, query))
			{
				AfxMessageBox("Fail", MB_OK);
			}

			if ((m_res = mysql_store_result(&mysql3)) == NULL)
			{ 
				return;
			}
			while ((row = mysql_fetch_row(m_res)) != NULL)
			{
				Alarm_str = row[0];
				Alarm_str = "SA|" + Alarm_str + "|";
				pT[user_Count].Send(Alarm_str, strlen(Alarm_str)+4);
				Alarm_str = "";
				m_Show_Data += "Message : " + id + "님이 등록하신 키워드 -> " + row[0] + "을 전송합니다.\r\n";
				UpdateData(false);

				for (int i = 0; i < 2000; i++)
				{
					for (int j = 0; j < 2000; j++)
					{

					}
				}

			}

			user_Count++;

			if (user_Count >= Socket_Status)
			{
				int Dep = Socket_Status;
				Socket_Status += 100;
				CClientSock *pTemp = new CClientSock[Socket_Status];
				CString *uTemp = new CString[Socket_Status];
				memcpy(pTemp, pT, sizeof(CClientSock)*Dep);
				memcpy(uTemp, uT, sizeof(CString)*Dep);
				delete[] pT;
				delete[] uT;
				pT = pTemp;
				uT = uTemp;
			}

		}
		else
		{
			pSock->Send("F|",4);
		}	
		return;

	}
	else if (str == 'J')
	{
		AfxMessageBox(buf);
		pSock->Send("J|회원가입이 완료되었습니다.", 14);


	}
	else if (str == 'S')
	{
		
		CString send;
		AfxExtractSubString(send, buf, 1, '|');

		query.Format("select Date,Title,Writer,Link from notice where Keyword  like '%s' order by Date",send);
		//AfxMessageBox(query);

		if (mysql_query(&mysql3, query))
		{
			AfxMessageBox("Fail", MB_OK);
		}

		if ((m_res = mysql_store_result(&mysql3)) == NULL)
		{ // 결과를 m_Res에 저장
			return;
		}
		result_num = mysql_num_rows(m_res);
		result_num_str.Format(_T("%d"), result_num);
		pSock->Send("Z|" + result_num_str + "|",5);

		Sleep(100);

		m_Show_Data += "Message : 누군가 단어를 검색합니다.\r\n";
		UpdateData(false);
		int result_num_k = 0;
		while ((row = mysql_fetch_row(m_res)) != NULL)
		{
			Sum[0] = row[0];
			Sum[1] = row[1];
			Sum[2] = row[2];
			Sum[3] = row[3];
			Sum[0] = "S|" + Sum[0] + "|" + Sum[1] + "|" + Sum[2] + "|" + Sum[3] + "|";
			pSock->Send(Sum[0], 400);

			for (int i = 0; i < 600; i++)
			{
				for (int j = 0; j < 600; j++)
				{

				}
			}
			
			result_num_k++;
			if (result_num_k == result_num)
			{
				m_Show_Data += "Message : 검색결과 전송완료.\r\n";
				UpdateData(false);
				mysql_close(connection2);
				return;
			}
		}		

		if ((row = mysql_fetch_row(m_res)) == NULL)
		{
			m_Show_Data += "Message : 검색결과가 없습니다.\r\n";
			UpdateData(false);
			pSock->Send("SF|검색 결과가 없습니다.", 12);
			mysql_close(connection2);
			return;
		}
	}
	else if (str == "AA")
	{
		CString Keyword, id;
		AfxMessageBox("알람 추가");
		AfxExtractSubString(id, buf, 1, '|');
		AfxExtractSubString(Keyword, buf, 2, '|');
		userKeyword.InsertItem(0, id);
		userKeyword.SetItemText(0, 1,Keyword);
		query.Format("insert into keywordt values(\"%s\",\"%s\")",Keyword,id);
		mysql_query(connection2, query);
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		mysql_close(connection2);

		m_Show_Data += "Message : " + id + "님이 알람키워드 -> " + Keyword + "를 추가하셨습니다. \r\n";
		m_Show_Data += "Message : 키워드 쓰레드를 활성화 합니다. \r\n";
		UpdateData(false);

		CWinThread *Kthread = NULL; //알람 키워드를 추출하고 등록하는 쓰레드
		Kthread = AfxBeginThread(Keyword_Store, this);
	}
	else if (str == "AD")
	{

	}
	else if (str == 'G')
	{

	}
	else
	{

	}

}
void CServerDlg::Send(char *buf)
{
	POSITION pos = m_clientSocks.GetHeadPosition();
	while (pos != NULL)
	{
		CClientSock *p = m_clientSocks.GetNext(pos);
		p->Send(buf, strlen(buf) + 1);
	}
}

UINT CServerDlg::Y_Thread(LPVOID pParam)
{
	int num = 1;
	while (true)
	{
		CString m_Show_Data2 = "";
		CString m_Absol_URL = "";
		CString m_Html_Tag = "";
		CString m_Url_Begi = "";
		CString m_values;
		CString str = "";
		BOOL first = TRUE;

		m_Absol_URL = _T("http://www.yu.ac.kr/_korean/about/index.php?c=about_08_a_list&page=");
		int resentNumber = 0, pagenum = m_Absol_URL.GetLength();
		str.Format("%d", num);
		m_Absol_URL.Insert(pagenum, str);

		CInternetSession m_Isession;
		CInternetFile* p_File = NULL;
		CStringArray Number;
		CStringArray Title;
		CStringArray Title_Phashing;
		CStringArray Link;
		CStringArray Create;
		CStringArray Writer;
		CString query = "";
		CString Web = _T("http://www.yu.ac.kr");
		CString m_Url_Buff = "";
		int m_Pos = 0, m_Pos2 = 0, m_Pos_Next = 0;
		int Total = 0, Page = 0, MaxNum, maxtmp;

 		mysql_init(&mysql);
		if (connection = mysql_real_connect(&mysql, DB_ADDRESS, DB_ID, DB_PASS, DB_NAME, 3306, 0, 0))
		{
			mysql_set_character_set(&mysql, "euckr");
			//AfxMessageBox("OK", MB_OK);
		}
		else
		{
			AfxMessageBox("fail", MB_OK);
			return 0;
		}

		query.Format("select PageNum, Num, resentNum from notice_info where name = 'notice'");

		if (mysql_query(&mysql, query))
		{ // 쿼리 요청
			AfxMessageBox("Error");
			return 0;
		}

		if ((m_res = mysql_store_result(&mysql)) == NULL)
		{ // 결과를 m_Res에 저장
			return 0;
		}

		if ((row = mysql_fetch_row(m_res)) != NULL)
		{
			// 출력창에 디버깅 용으로 
			Page = _ttoi(row[0]);
			Total = _ttoi(row[1]);
			MaxNum = _ttoi(row[2]);
			maxtmp = MaxNum;
		}

		try{
			p_File = (CInternetFile *)m_Isession.OpenURL(m_Absol_URL);
		}
		catch (CInternetException *p_Ex)
		{
			p_File = NULL;
			p_Ex = NULL;
			AfxMessageBox(_T("Error!!"));
		}

		bool a = false;
		CString data, realdata;
		p_File->SetReadBufferSize(4096);
		int i = 0, j = 0, k = 0;

		if (p_File)
		{
			while (true)
			{
				if (p_File->ReadString(data))
				{
					if (i = data.Find(_T("영대 소식 게시물 목록")) != -1)
					{
						while (true)
						{
							if (p_File->ReadString(realdata))
							{
								if (j = realdata.Find(_T("boardListBottom")) != -1) break;
								else if (k = realdata.Find(_T("tbody")) != -1)
								{
									a = true;
								}
								else if (a == true)
								{
									k++;
									realdata += "\r\n";
									m_Show_Data2 += realdata;
								}
							}
							else break;
						}
					}
				}
				else break;
			}

		}
		else AfxMessageBox(_T("p_File is NULL!!"), MB_OK);


		// 정말로 파싱하는 구간 

		m_Html_Tag = m_Show_Data2;
		m_Url_Begi = m_Html_Tag;
		m_Url_Buff = m_Html_Tag;
		m_values = m_Html_Tag;
		m_Url_Buff.MakeLower();
		m_Show_Data2.Empty();

		for (int i = 0; i < 15; i++)
		{
			m_Pos = m_Url_Buff.Find("a href=", m_Pos_Next);
			if (m_Pos == -1)
			{
				break;
			}
			m_Pos2 = m_Url_Buff.Find("title", m_Pos);
			m_Pos_Next = m_Pos2;

			m_Url_Begi = m_Url_Buff.Mid(m_Pos + 1, (m_Pos2 - m_Pos) - 2);
			if ((m_Pos = m_Url_Begi.Find("\"")) != -1)
			{
				if ((m_Pos2 = m_Url_Begi.Find("\"", m_Pos + 1)) != -1)
					m_Url_Begi = m_Url_Begi.Mid(m_Pos + 1, m_Pos2 - m_Pos - 1);
			}
			if ((m_Pos = m_Url_Begi.Find("amp;")) != -1)
			{
				m_Url_Begi.Delete(m_Pos, 4);
			}
			if ((m_Pos = m_Url_Begi.Find("amp;")) != -1)
			{
				m_Url_Begi.Delete(m_Pos, 4);
			}
			m_Url_Begi = Web + m_Url_Begi;
			Link.Add(m_Url_Begi);

		}

		CString strTmp;
		CString strTmptmp;
		int phasingnum[15];
		int nStart = 0, nEnd = 0, nCnt = 0, phasing_count = 0;
		m_Show_Data2 = "";

		for (int i = 0; i < 15; i++)
		{
			if (m_Pos == -1)
			{
				break;
			}
			nStart = m_Url_Buff.Find(_T("<td>"), nCnt);
			nEnd = m_Url_Buff.Find(_T("</td>"), nStart);
			nStart += strlen(("<td>"));
			nCnt = nEnd;
			strTmp = m_Url_Buff.Mid(nStart, nEnd - nStart);
			Number.Add(strTmp);
			resentNumber = _ttoi(strTmp);
			if (maxtmp == _ttoi(strTmp))
			{
				first = false;
				break;
			}
			else
			{
				if (resentNumber > MaxNum)
				{
					MaxNum = resentNumber;
					CString strtmp222;
					strtmp222.Format("%d", MaxNum);
					query.Format("update notice_info set resentNum = \"%s\" where name = 'notice'", strtmp222);
					mysql_query(connection, query);
				}
				nStart = m_Url_Buff.Find(_T("title="), nCnt);
				nEnd = m_Url_Buff.Find(_T("\">"), nStart);
				nStart += strlen("title=");
				nCnt = nEnd;


				strTmp = m_Url_Buff.Mid(nStart + 1, nEnd - nStart - 1);
				strTmptmp = m_Url_Buff.Mid(nStart + 1, nEnd - nStart - 1);
				Title.Add(strTmp);

				int k = 0;
				char *ps;
				char str2[] = " ,\t\n@#!$%^&*(){}[]|\';:''<>?,./~`★■□◈♬";
				char ch[200] = { 0, };

				char* ss = LPSTR(LPCTSTR(strTmptmp));


				ps = strtok(ss, str2);

				while (ps != NULL)
				{
					Title_Phashing.Add(ps);
					phasing_count++;
					for (int i = 0; i < Keyword_count; i++)
					{
						if (!strcmp(ps, uK[i]))
						{
							for (int j = 0; j < user_Count; j++)
							{
								if (!strcmp(uT[user_Count], uid[i]))
								{
									pT[user_Count].Send("A|" + uK[i] + "새로운 알람이 왔습니다.|", strlen(uK[i]) + 20);
								}
							}
						}
					}
					ps = strtok(NULL, str2);
				}
				phasingnum[i] = phasing_count;
				phasing_count = 0;

				//
				//Title을 파싱하여 키워드를 생성하고 여기서 Query문을 통해 키워드들을 다 저장
				//

				nStart = m_Url_Buff.Find(_T("<td>"), nCnt);
				nEnd = m_Url_Buff.Find(_T("</td>"), nStart);
				nStart += strlen("<td>");
				nCnt = nEnd;
				strTmp = m_Url_Buff.Mid(nStart, nEnd - nStart);
				Writer.Add(strTmp);

				nStart = m_Url_Buff.Find(_T("<td>"), nCnt);
				nEnd = m_Url_Buff.Find(_T("</td>"), nStart);
				nStart += strlen("<td>");
				nCnt = nEnd;
				strTmp = m_Url_Buff.Mid(nStart, nEnd - nStart);
				Create.Add(strTmp);

				nStart = m_Url_Buff.Find(_T("<td>"), nCnt);
				nEnd = m_Url_Buff.Find(_T("</td>"), nStart);
				nStart += strlen("<td>");
				nCnt = nEnd;


				for (int q = 0; q < phasingnum[i]; q++)
				{
					query.Format("insert into notice values(\"%d\",\"%s\",\"%s\",\"%s\", \"%s\", \"%s\" )", _ttoi(Number.GetAt(i)), Title_Phashing.GetAt(q), Title.GetAt(i), Link.GetAt(i), Writer.GetAt(i), Create.GetAt(i));
					mysql_query(connection, query);
				}
				Title_Phashing.RemoveAll();
			}
		}
		num++;
		mysql_close(connection);
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		if (num == Page || first == false)
		{
			num = 1;

		} 
	}	
}

UINT CServerDlg::Y2_Thread(LPVOID pParam)
{
	int num = 1;

	while (true)
	{
		CString m_Show_Data2 = "";
		CString m_Absol_URL = "";
		CString m_Html_Tag = "";
		CString m_Url_Begi = "";
		CString m_values;
		CString str;
		int resentNumber = 0;
		BOOL first = TRUE;

		m_Absol_URL = _T("http://www.yu.ac.kr/_korean/community/index.php?c=plaza_01_list&page=");
		int pagenum = m_Absol_URL.GetLength();
		str.Format("%d", num);
		m_Absol_URL.Insert(pagenum, str);

		SetCursor(LoadCursor(NULL, IDC_WAIT));
		CInternetSession m_Isession;
		CInternetFile* p_File = NULL;
		CStringArray Number;
		CStringArray Title;
		CStringArray Title_Phashing;
		CStringArray Link;
		CStringArray Create;
		CStringArray Writer;
		CString query = "";
		CString Web = _T("http://www.yu.ac.kr");
		CString m_Url_Buff = "";
		int m_Pos = 0, m_Pos2 = 0, m_Pos_Next = 0;
		int Total = 0, Page = 0, MaxNum, maxtmp;

		for (int i = 0; i < 100; i++)
		{
			for (int alal = 0; alal < 150; alal++)
			{

			}
		}

		mysql_init(&mysql4);
		if (connection3 = mysql_real_connect(&mysql4, DB_ADDRESS, DB_IDDDD, DB_PASS, DB_NAME, 3306, 0, 0))
		{
			mysql_set_character_set(&mysql4, "euckr");
			//AfxMessageBox("OK", MB_OK);
		}
		else
		{
			AfxMessageBox("fail", MB_OK);
			return 0;
		}

		query.Format("select PageNum, Num, resentNum from notice_info where name = 'notice2'");

		if (mysql_query(&mysql4, query))
		{ // 쿼리 요청
			AfxMessageBox("Error");
			return 0;
		}

		if ((m_res = mysql_store_result(&mysql4)) == NULL)
		{ // 결과를 m_Res에 저장
			return 0;
		}

		if ((row = mysql_fetch_row(m_res)) != NULL)
		{
			// 출력창에 디버깅 용으로
			Page = _ttoi(row[0]);
			Total = _ttoi(row[1]);
			MaxNum = _ttoi(row[2]);
			maxtmp = MaxNum;

		}

		try{
			p_File = (CInternetFile *)m_Isession.OpenURL(m_Absol_URL);
		}
		catch (CInternetException *p_Ex)
		{
			p_File = NULL;
			p_Ex = NULL;
			AfxMessageBox(_T("Error!!"));
		}

		bool a = false;
		CString data, realdata;
		p_File->SetReadBufferSize(4096);
		int i = 0, j = 0, k = 0;

		if (p_File)
		{
			while (true)
			{
				if (p_File->ReadString(data))
				{
					if (i = data.Find(_T("대자보 게시판 목록")) != -1)
					{
						while (true)
						{
							if (p_File->ReadString(realdata))
							{
								if (j = realdata.Find(_T("boardListBottom")) != -1) break;
								else if (k = realdata.Find(_T("<!-- <td >&nbsp;</td> -->")) != -1)
								{
									a = true;
								}
								else if (a == true)
								{
									k++;
									realdata += "\r\n";
									m_Show_Data2 += realdata;
								}
							}
							else break;
						}
					}
				}
				else break;
			}

		}
		else AfxMessageBox(_T("p_File is NULL!!"), MB_OK);


		// 정말로 파싱하는 구간 

		m_Html_Tag = m_Show_Data2;
		m_Url_Begi = m_Html_Tag;
		m_Url_Buff = m_Html_Tag;
		m_values = m_Html_Tag;
		m_Url_Buff.MakeLower();
		m_Show_Data2.Empty();

		for (int i = 0; i < 15; i++)
		{
			m_Pos = m_Url_Buff.Find("a href=", m_Pos_Next);
			if (m_Pos == -1)
			{
				break;
			}
			m_Pos2 = m_Url_Buff.Find("title", m_Pos);
			m_Pos_Next = m_Pos2;



			m_Url_Begi = m_Url_Buff.Mid(m_Pos + 1, (m_Pos2 - m_Pos) - 2);
			if ((m_Pos = m_Url_Begi.Find("\"")) != -1)
			{
				if ((m_Pos2 = m_Url_Begi.Find("\"", m_Pos + 1)) != -1)
					m_Url_Begi = m_Url_Begi.Mid(m_Pos + 1, m_Pos2 - m_Pos - 1);
			}
			if ((m_Pos = m_Url_Begi.Find("amp;")) != -1)
			{
				m_Url_Begi.Delete(m_Pos, 4);
			}
			if ((m_Pos = m_Url_Begi.Find("amp;")) != -1)
			{
				m_Url_Begi.Delete(m_Pos, 4);
			}
			m_Url_Begi = Web + m_Url_Begi;
			Link.Add(m_Url_Begi);

		}

		CString strTmp;
		CString strTmptmp;
		int phasingnum[15];
		int nStart = 0, nEnd = 0, nCnt = 0, phasing_count = 0;
		m_Show_Data2 = "";

		for (int i = 0; i < 15; i++)
		{
			if (m_Pos == -1)
			{
				break;
			}
			nStart = m_Url_Buff.Find(_T("<td>"), nCnt);
			nEnd = m_Url_Buff.Find(_T("</td>"), nStart);
			nStart += strlen(("<td>"));
			nCnt = nEnd;
			strTmp = m_Url_Buff.Mid(nStart, nEnd - nStart);
			Number.Add(strTmp);
			resentNumber = _ttoi(strTmp);
			if (maxtmp == _ttoi(strTmp))
			{
				first = false;
				break;
			}
			else
			{
				if (resentNumber > MaxNum)
				{
					MaxNum = resentNumber;
					CString strtmp222;
					strtmp222.Format("%d", MaxNum);
					query.Format("update notice_info set resentNum = \"%s\" where name = 'notice2'", strtmp222);
					if (mysql_query(connection3, query))
					{ // 쿼리 요청
						AfxMessageBox("Error");
					}
				}
				nStart = m_Url_Buff.Find(_T("title="), nCnt);
				nEnd = m_Url_Buff.Find(_T("\">"), nStart);
				nStart += strlen("title=");
				nCnt = nEnd;


				strTmp = m_Url_Buff.Mid(nStart + 1, nEnd - nStart - 1);
				strTmptmp = m_Url_Buff.Mid(nStart + 1, nEnd - nStart - 1);
				Title.Add(strTmp);

				int k = 0;
				char *ps;
				char str2[] = " ,\t\n@#!$%^&*(){}[]|\';:''<>?,./~`★■□◈♬";
				char ch[200] = { 0, };

				char* ss = LPSTR(LPCTSTR(strTmptmp));


				ps = strtok(ss, str2);

				while (ps != NULL)
				{
					Title_Phashing.Add(ps);
					phasing_count++;
					for (int i = 0; i < Keyword_count; i++)
					{
						if (!strcmp(ps, uK[i]))
						{
							for (int j = 0; j < user_Count; j++)
							{
								if (!strcmp(uT[user_Count], uid[i]))
								{
									pT[user_Count].Send("A|" + uK[i] + "새로운 알람이 왔습니다.|", strlen(uK[i]) + 20);
								}
							}
						}
					}
					ps = strtok(NULL, str2);
				}
				phasingnum[i] = phasing_count;
				phasing_count = 0;

				//
				//Title을 파싱하여 키워드를 생성하고 여기서 Query문을 통해 키워드들을 다 저장
				//

				nStart = m_Url_Buff.Find(_T("<td>"), nCnt);
				nEnd = m_Url_Buff.Find(_T("</td>"), nStart);
				nStart += strlen("<td>");
				nCnt = nEnd;
				strTmp = m_Url_Buff.Mid(nStart, nEnd - nStart);
				Writer.Add(strTmp);

				nStart = m_Url_Buff.Find(_T("<td>"), nCnt);
				nEnd = m_Url_Buff.Find(_T("</td>"), nStart);
				nStart += strlen("<td>");
				nCnt = nEnd;
				strTmp = m_Url_Buff.Mid(nStart, nEnd - nStart);
				Create.Add(strTmp);

				nStart = m_Url_Buff.Find(_T("<td>"), nCnt);
				nEnd = m_Url_Buff.Find(_T("</td>"), nStart);
				nStart += strlen("<td>");
				nCnt = nEnd;


				for (int q = 0; q < phasingnum[i]; q++)
				{
					query.Format("insert into notice values(\"%d\",\"%s\",\"%s\",\"%s\", \"%s\", \"%s\" )", _ttoi(Number.GetAt(i)), Title_Phashing.GetAt(q), Title.GetAt(i), Link.GetAt(i), Writer.GetAt(i), Create.GetAt(i));
					mysql_query(connection3, query);
				}
				Title_Phashing.RemoveAll();
			}
		}
		num++;
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		mysql_close(connection3);
		if (num == Page || first == false)
		{
			num = 1;
		}
	}
}

void CServerDlg::OnBnClickedSend()
{
	UpdateData(TRUE);
	char buf[2000];
	lstrcpy(buf, "BC|");
	lstrcat(buf, (const char*)m_strSend);
	Send(buf);
}

UINT CServerDlg::Keyword_Store(LPVOID pParam) //keyword 저장
{
	CString query;
	SetCursor(LoadCursor(NULL, IDC_WAIT));
	mysql_init(&mysql2);
	CString kKeyword, kid;
	Keyword_count = 0;

	if (connection = mysql_real_connect(&mysql2, DB_ADDRESS, DB_IDDD, DB_PASS, DB_NAME, 3306, 0, 0))
		{
			mysql_set_character_set(&mysql2, "euckr");
			//AfxMessageBox("OK", MB_OK);
		}
		else
		{
			AfxMessageBox("fail", MB_OK);
			return 0;
		}

		query.Format("select * from Keywordt");

		if (mysql_query(&mysql2, query))
		{ // 쿼리 요청
			AfxMessageBox("Error");
			return 0;
		}

		if ((m_res = mysql_store_result(&mysql2)) == NULL)
		{ // 결과를 m_Res에 저장
			return 0;
		}

		while ((row = mysql_fetch_row(m_res)) != NULL)
		{
			// 출력창에 디버깅 용으로 
			uK[Keyword_count] = row[0];
			uid[Keyword_count] = row[1];
			Keyword_count++;
			if (Keyword_count > Keyword_Status)
			{
				int Dep = Keyword_Status;
				Keyword_Status += 100;
				CString *kTemp = new CString[Keyword_Status];
				CString *uiTemp = new CString[Keyword_Status];
				memcpy(&kTemp, uK, sizeof(CString)*Dep);
				memcpy(&uiTemp, uid, sizeof(CString)*Dep);
				delete[] uK;
				delete[] uid;
				uK = kTemp;
				uid = uiTemp;
			}
		}
	
	return 0;
}
