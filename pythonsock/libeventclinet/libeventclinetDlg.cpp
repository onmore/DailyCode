
// libeventclinetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "libeventclinet.h"
#include "libeventclinetDlg.h"
#include "afxdialogex.h"
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#ifndef WIN32
#include <netinet/in.h>
# ifdef _XOPEN_SOURCE_EXTENDED
#  include <arpa/inet.h>
# endif
#include <sys/socket.h>
#endif

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ClibeventclinetDlg 对话框


 UINT WINAPI threadproc(void* data)
{	
	struct event_base* base = (struct event_base*)data;
	int i = event_base_dispatch(base);
	return 0;
}


ClibeventclinetDlg::ClibeventclinetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LIBEVENTCLINET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void ClibeventclinetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(ClibeventclinetDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &ClibeventclinetDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ClibeventclinetDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// ClibeventclinetDlg 消息处理程序

BOOL ClibeventclinetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
	_base = event_base_new();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void ClibeventclinetDlg::OnPaint()
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
HCURSOR ClibeventclinetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


static void
signal_cb(evutil_socket_t sig, short events, void *user_data)
{
	struct event_base *base = (event_base *)user_data;
}
void ClibeventclinetDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	_sock = socket(AF_INET , SOCK_STREAM , 0 );
	
	_connevent = event_new(_base , _sock , EV_WRITE , signal_cb , NULL);
	event_add(_connevent , NULL);
	_beginthreadex(NULL , 0 , threadproc , _base , 0 , 0);
	Sleep(1000 * 5);
	sockaddr_in addr;
	memset(& addr , 0 , sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.99.119");


	connect(_sock , (sockaddr*)&addr , sizeof(sockaddr));

}


void ClibeventclinetDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	char buf[] = "sasass";
	int i = send(_sock, buf, strlen(buf) + 1, 0);
}
