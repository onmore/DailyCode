
// socketclientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "socketclient.h"
#include "socketclientDlg.h"
#include "afxdialogex.h"
#include <wchar.h>
#include <locale.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CsocketclientDlg �Ի���

#include<winsock2.h>




CsocketclientDlg::CsocketclientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SOCKETCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_sock  = INVALID_SOCKET;
}

void CsocketclientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CsocketclientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_SOCK , OnSock)
	ON_BN_CLICKED(IDC_CON, &CsocketclientDlg::OnBnClickedCon)
	ON_BN_CLICKED(IDC_SEND, &CsocketclientDlg::OnBnClickedSend)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_LINKTEST, &CsocketclientDlg::OnBnClickedLinktest)
END_MESSAGE_MAP()


// CsocketclientDlg ��Ϣ�������

BOOL CsocketclientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
	{
		return -1;
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CsocketclientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CsocketclientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CsocketclientDlg::OnBnClickedCon()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_sock = socket(AF_INET , SOCK_STREAM , 0);
	if (m_sock == INVALID_SOCKET)
	{
		MessageBox(_T("��Ч��sock!\n"));
	}
	
	sockaddr_in addr;
	memset(&addr, 0, sizeof(sockaddr_in));
	addr.sin_port = htons(12345);
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.99.119");

	if(connect(m_sock, (sockaddr*)&addr, sizeof(sockaddr)) == SOCKET_ERROR)
	{
		MessageBox(_T("�������ӵ������!\n"));
	}

	WSAAsyncSelect(m_sock , GetSafeHwnd() , WM_SOCK , FD_READ|FD_CLOSE);
}


void CsocketclientDlg::OnBnClickedSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//if (m_sock == INVALID_SOCKET)
	//{
	//	MessageBox(_T("��Ч��socket!\n"));
	//	return;
	//}
	//CString str;
	//GetDlgItem(IDC_SENDTEXT)->GetWindowText(str);
	//setlocale(LC_ALL, "");
	//wchar_t* sz;
	//sz = str.GetBuffer(0);
	//wchar_t* p = new wchar_t[1024];
	//memset(p, 0, 1024);
	//wmemcpy(p , sz , wcslen(sz));
	//mbstate_t mbs;
	//char buff[1024];
	//memset(buff , 0 , 1024);
	//mbrlen(NULL, 0, &mbs);
	//wcsrtombs(buff, (const wchar_t**)&p, 1024-1, &mbs);
	char buff[] = "dasdasdsadd \n\t dasdasdasd \n \t  dasdjaslkdjaskldj\n";
	send(m_sock , buff , strlen(buff)+1  , 0);
}


void CsocketclientDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnClose();
}


LRESULT CsocketclientDlg::OnSock(WPARAM wParam, LPARAM lParam)
{
	switch (WSAGETSELECTEVENT(lParam))
	{
		// ����пͻ���connect����
	case FD_CLOSE:
	{
		closesocket(m_sock);
		m_sock = INVALID_SOCKET;
		CString str;
		GetDlgItem(IDC_RESVTEXT)->GetWindowText(str);
		str = str + _T("\n����˹ر���socket\n");
		GetDlgItem(IDC_RESVTEXT)->SetWindowText(str);
		break;
	}
	case FD_READ:
	{
		char szBuf[1024] = { 0 };
		if (recv(m_sock, (char *)szBuf, MAX_PATH, 0) > 0)
		{
			CString str;
			GetDlgItem(IDC_RESVTEXT)->GetWindowText(str);
			str = str + CStringW(szBuf);
			GetDlgItem(IDC_RESVTEXT)->SetWindowText(str);
		}	
		break;
	}
	default:
		break;
	}

	return 0;

}


void CsocketclientDlg::OnBnClickedLinktest()
{
	int ncount = 2000;
	while (ncount--)
	{
		SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock == INVALID_SOCKET)
		{
			MessageBox(_T("��Ч��sock!\n"));
		}

		sockaddr_in addr;
		memset(&addr, 0, sizeof(sockaddr_in));
		addr.sin_port = htons(12345);
		addr.sin_family = AF_INET;
		addr.sin_addr.S_un.S_addr = inet_addr("192.168.99.119");

		if (connect(sock, (sockaddr*)&addr, sizeof(sockaddr)) == SOCKET_ERROR)
		{
			MessageBox(_T("�������ӵ������!\n"));
		}

		char buff[] = "afkasl;dfl;sdk;flklsdkflksd;fksdkfkl;;sdlkfsdkl;fklsdl;f;lsdkf;ksdl;fk;sdlkf;sdlkf;sdlkf;lksd";
		send(m_sock, buff, strlen(buff) + 1, 0);
	}


}
