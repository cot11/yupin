// ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "Addressdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString User_id;
CString User_info_join;
CAddressDlg dlg;
CString Link_buffer[400];
int confirm_a = 0;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/) : CDialog(CClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDlg)
	m_strSend = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

CClientDlg::~CClientDlg()
{
	delete m_pClientSock;
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDlg)
	DDX_Text(pDX, IDC_EDIT_SEND, m_strSend);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_LIST_RECEIVE, m_LIST_RECEIVE);
	DDX_Control(pDX, IDC_KEYWORD_IN, m_KeywordInsert);
	DDX_Control(pDX, IDC_LIST1, m_List_Ctrl);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	//{{AFX_MSG_MAP(CClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, OnSend)
	//}}AFX_MSG_MAP
	//	ON_BN_CLICKED(IDC_MFCLINK1, &CClientDlg::OnBnClickedMfclink1)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CClientDlg::OnBnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CClientDlg::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_CLEAN, &CClientDlg::OnBnClickedClean)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_RECEIVE, &CClientDlg::OnNMDblclkListReceive)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	confirm_a++;
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	BITMAP bmpInfo;


	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	CString buf;

	if (dlg.DoModal() == IDOK)
	{
		m_pClientSock = new CClientSock();
		m_pClientSock->Create();
		m_pClientSock->Connect("183.106.15.118", 700);	
		m_LIST_RECEIVE.SetExtendedStyle(LVS_EX_FULLROWSELECT);
		m_LIST_RECEIVE.InsertColumn(0, "��¥", LVCFMT_LEFT, 200);
		m_LIST_RECEIVE.InsertColumn(1, "����", LVCFMT_LEFT, 500);
		m_LIST_RECEIVE.InsertColumn(2, "�ۼ���", LVCFMT_LEFT, 150);
		m_LIST_RECEIVE.InsertColumn(3, "��ư", LVCFMT_LEFT, 150);

		m_List_Ctrl.InsertColumn(0, "Ű����", LVCFMT_LEFT, 100);
		m_List_Ctrl.InsertColumn(1, "���� ��¥", LVCFMT_LEFT, 100);


		CString strText;
		int nColumnCount = m_LIST_RECEIVE.GetHeaderCtrl()->GetItemCount();

		if (dlg.isGuest == TRUE) 	// �Խ�Ʈ ����
		{
			GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE); // ���� ��ư ��Ȱ��ȭ
			GetDlgItem(IDC_LIST1)->EnableWindow(FALSE); // �˶� Ű���� ����Ʈ ��Ȱ��ȭ
			GetDlgItem(IDC_KEYWORD_IN)->EnableWindow(FALSE); // Ű���� �Է� ĭ ��Ȱ��ȭ
			GetDlgItem(IDC_BUTTON_INSERT)->EnableWindow(FALSE); // �߰� ��ư ��Ȱ��ȭ
			GetDlgItem(IDC_BUTTON_DEL)->EnableWindow(FALSE); // ���� ��ư ��Ȱ��ȭ

			buf = "G|";
			m_pClientSock->Send(buf, strlen(buf) + 1);
		}

		else
		{
			buf = "L|" + dlg.m_strName + "|" + dlg.m_strPwd;
			m_pClientSock->Send(buf, strlen(buf) + 1);
		}
	}

	else {
		Check = AfxMessageBox("�����ұ��?", MB_YESNO); // Ȯ�� = 6, ��� = 7

		if (Check == 7) {
			OnClose();
			this->DoModal();
		}

		else {
			exit(1);
			//::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL); // ���� ����??
		}
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}

	else if (nID == SC_CLOSE) {
		Check = AfxMessageBox("�����ұ��?", MB_YESNO); // Ȯ�� = 6

		if (Check == 6) {
			exit(1);
			//::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL); // ���� ����?? 
		}
	}

	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}

	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}

void CClientDlg::OnReceive()
{

	char buf[400];
	static CString Title_buffer[400];
	static CString Data_buffer[400];
	static CString Writer_buffer[400];
	static CString search_buf[400];
	CString str, str2;
	m_pClientSock->Receive(buf, 400);
	static int count_i, count_j = 0;

	AfxExtractSubString(str, buf, 0, '|');


	if (str == 'O')
	{
		AfxMessageBox("�α��� ����");
		User_id = dlg.m_strName;
	}
	else if (str == 'F')
	{
		AfxMessageBox("�α��� ����");
	}
	else if (str == 'S')
	{
		search_buf[count_i - 1] = buf;
		count_i--;

		if (!count_i)
		{
			for (int k = 0; k < count_j; k++)
			{
				AfxExtractSubString(Data_buffer[k], search_buf[k], 1, '|');
				AfxExtractSubString(Title_buffer[k], search_buf[k], 2, '|');
				AfxExtractSubString(Writer_buffer[k], search_buf[k], 3, '|');
				AfxExtractSubString(Link_buffer[k], search_buf[k], 4, '|');
				m_LIST_RECEIVE.InsertItem(0, Data_buffer[k]);
				m_LIST_RECEIVE.SetItemText(0, 1, Title_buffer[k]);
				m_LIST_RECEIVE.SetItemText(0, 2, Writer_buffer[k]);
			}
			
		}
	}
	else if (str == 'Z')
	{
		AfxExtractSubString(str2, buf, 1, '|');
		count_i = _ttoi(str2);
		count_j = count_i;
	}
	else if (str == "SF")
	{
		AfxMessageBox("�˻������ �����ϴ�.");
	}
	else if (str == "AR")
	{
		AfxMessageBox("�˶� �︲.");
	}
	else if (str == "SA")
	{
		AfxExtractSubString(str2, buf, 1, '|');
		m_List_Ctrl.InsertItem(0, str2);
	}
	else if (str == "J")
	{
		AfxMessageBox(buf);
	}

	return;
}

void CClientDlg::OnSend()
{
	// TODO: Add your control notification handler code here
	m_LIST_RECEIVE.DeleteAllItems(); // ��� ���� ����
	UpdateData(TRUE);
	m_strSend = "S|" + m_strSend;
	m_pClientSock->Send(m_strSend, strlen(m_strSend) + 1);
}

/*
void CClientDlg::OnBnClickedMfclink1()
{
// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
*/

void CClientDlg::OnBnClickedButtonInsert() // �˶� Ű���� �߰� = AA, �˶� Ű���� ���� = AD
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strEdit, str;
	CString time_string;
	CTime t = CTime::GetCurrentTime();

	time_string.Format("%d�� %d�� %d�� %d�� %d��", t.GetMonth(),
		t.GetDay(), t.GetHour(), t.GetMinute(), t.GetSecond());

	m_KeywordInsert.GetWindowTextA(strEdit);
	int nCount = m_List_Ctrl.GetItemCount();

	for (int i = 0; i < nCount; i++)
	{
		str = m_List_Ctrl.GetItemText(i,0);
		if (!strcmp(str, strEdit))
		{
			AfxMessageBox(str + "�� �̹� ��ϵǾ��ֽ��ϴ�.");
			return;
		}
		str = "";
	}
	if (strEdit.IsEmpty() == FALSE)
	{
		m_List_Ctrl.InsertItem(0, strEdit);
		m_List_Ctrl.SetItemText(0, 1, time_string);
		m_pClientSock->Send("AA|" + User_id + "|" + strEdit + "|", strlen(User_id) + strlen(strEdit) + 5);
	}

	//back
	/*
	m_KeywordInsert.GetWindowTextA(strEdit);

	if (strEdit.IsEmpty() == FALSE)
	{
	m_List.AddString(strEdit);	//���� �׸��� ������ ��� �ͼ�, add�ϰ� ���� ī��Ʈ
	int count = m_List.GetCount();	//������(�߰���) �׸��� ���õǵ��� ��
	m_List.SetCurSel(count - 1);		//ù��° ��Ҵ� 0���� ������
	}
	*/
}

void CClientDlg::OnBnClickedButtonDel() //�˶� ���� ����
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int nCount = m_List_Ctrl.GetSelectedCount();
	CString str;
	for (int i = nCount; i >= 0; --i)
	{
		POSITION pos = m_List_Ctrl.GetFirstSelectedItemPosition();
		int nItem = m_List_Ctrl.GetNextSelectedItem(pos);
		str = m_List_Ctrl.GetItemText(nItem, 0);
		m_List_Ctrl.DeleteItem(nItem);
		if (str != "")
		{
			AfxMessageBox(str);
		}
	}

	//back
	/*
	int nIndex = m_List.GetCurSel();

	if (nIndex != LB_ERR) // �׸��� ��� ���� �ʴٸ�,
	{
	m_List.DeleteString(nIndex); // �ش� �׸� ����
	}
	*/
}

void CClientDlg::OnBnClickedClean() // �˻� ���� ��� ����
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	m_LIST_RECEIVE.DeleteAllItems(); // ��� ���� ����
}


void CClientDlg::OnNMDblclkListReceive(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	int nCount = m_LIST_RECEIVE.GetSelectedCount();
	CString str;
	for (int i = 0; i < nCount; i++)
	{
		POSITION pos = m_LIST_RECEIVE.GetFirstSelectedItemPosition();
		int nItem = m_LIST_RECEIVE.GetNextSelectedItem(pos);
		str = m_LIST_RECEIVE.GetItemText(nItem, 0);
		::ShellExecute(NULL, "open", "chrome.exe", Link_buffer[i], NULL, SW_SHOW);
		break;
	}
	

	*pResult = 0;
}

void CClientDlg::DeleGate_Send(CString Join_info)
{
	User_info_join = Join_info;
}