
// socketclientDlg.h : ͷ�ļ�
//

#pragma once


// CsocketclientDlg �Ի���
class CsocketclientDlg : public CDialogEx
{
// ����
public:
	CsocketclientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SOCKETCLIENT_DIALOG };
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
	afx_msg void OnBnClickedCon();
	afx_msg void OnBnClickedSend();
	afx_msg LRESULT OnSock(WPARAM wParam, LPARAM lParam);

private:
	SOCKET m_sock;
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedLinktest();
};
