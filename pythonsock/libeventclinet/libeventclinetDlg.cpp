
// libeventclinetDlg.cpp : ʵ���ļ�
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


// ClibeventclinetDlg �Ի���


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


// ClibeventclinetDlg ��Ϣ�������

BOOL ClibeventclinetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
	_base = event_base_new();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void ClibeventclinetDlg::OnPaint()
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char buf[] = "sasass";
	int i = send(_sock, buf, strlen(buf) + 1, 0);
}
