
// libeventclinetDlg.h : ͷ�ļ�
//

#pragma once
#include <event2/util.h>
#include <event2/event.h>
#include <WinSock2.h>



class ClibeventclinetDlg : public CDialogEx
{
// ����
public:
	ClibeventclinetDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIBEVENTCLINET_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	struct event_base*  _base;
	struct event*	   _connevent;
	SOCKET _sock;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
