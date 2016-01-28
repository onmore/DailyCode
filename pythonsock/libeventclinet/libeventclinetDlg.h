
// libeventclinetDlg.h : 头文件
//

#pragma once
#include <event2/util.h>
#include <event2/event.h>
#include <WinSock2.h>



class ClibeventclinetDlg : public CDialogEx
{
// 构造
public:
	ClibeventclinetDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIBEVENTCLINET_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
