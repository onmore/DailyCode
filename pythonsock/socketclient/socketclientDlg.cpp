
// socketclientDlg.cpp : 实现文件
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


// CsocketclientDlg 对话框

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


// CsocketclientDlg 消息处理程序

BOOL CsocketclientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
	{
		return -1;
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CsocketclientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CsocketclientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CsocketclientDlg::OnBnClickedCon()
{
	// TODO: 在此添加控件通知处理程序代码
	m_sock = socket(AF_INET , SOCK_STREAM , 0);
	if (m_sock == INVALID_SOCKET)
	{
		MessageBox(_T("无效的sock!\n"));
	}
	
	sockaddr_in addr;
	memset(&addr, 0, sizeof(sockaddr_in));
	addr.sin_port = htons(12345);
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.99.119");

	if(connect(m_sock, (sockaddr*)&addr, sizeof(sockaddr)) == SOCKET_ERROR)
	{
		MessageBox(_T("不能连接到服务端!\n"));
	}

	WSAAsyncSelect(m_sock , GetSafeHwnd() , WM_SOCK , FD_READ|FD_CLOSE);
}


void CsocketclientDlg::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码
	//if (m_sock == INVALID_SOCKET)
	//{
	//	MessageBox(_T("无效的socket!\n"));
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();
}


LRESULT CsocketclientDlg::OnSock(WPARAM wParam, LPARAM lParam)
{
	switch (WSAGETSELECTEVENT(lParam))
	{
		// 如果有客户端connect连接
	case FD_CLOSE:
	{
		closesocket(m_sock);
		m_sock = INVALID_SOCKET;
		CString str;
		GetDlgItem(IDC_RESVTEXT)->GetWindowText(str);
		str = str + _T("\n服务端关闭了socket\n");
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
			MessageBox(_T("无效的sock!\n"));
		}

		sockaddr_in addr;
		memset(&addr, 0, sizeof(sockaddr_in));
		addr.sin_port = htons(12345);
		addr.sin_family = AF_INET;
		addr.sin_addr.S_un.S_addr = inet_addr("192.168.99.119");

		if (connect(sock, (sockaddr*)&addr, sizeof(sockaddr)) == SOCKET_ERROR)
		{
			MessageBox(_T("不能连接到服务端!\n"));
		}

		char buff[] = "afkasl;dfl;sdk;flklsdkflksd;fksdkfkl;;sdlkfsdkl;fklsdl;f;lsdkf;ksdl;fk;sdlkf;sdlkf;sdlkf;lksd";
		send(m_sock, buff, strlen(buff) + 1, 0);
	}


}
